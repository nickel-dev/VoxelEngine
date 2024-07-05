// TODO: Add Perspective Rendering

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <time.h>
#include <vector>
#include <glad/glad.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_image.h>
#include <PerlinNoise.h>
#include "base/base_inc.h"
#include "render/shader.h"
#include "render/camera.h"
#include "world/chunk.h"

#define Data(p) STRADD("data/", p)

struct WindowState
{
    I32 width, height;
    B8 fullscreen;
    B8 running;
    SDL_Window* window;
    B8 inGame;
} windowState;

local std::vector<W_Chunk> chunks;
local U32 terrainTexture;
local U32 wireframeMode;
local F32* projectionMatrix;
local I32 frameCount;
local U64 lastTime, lastFrameTime;
local F32 deltaTime;
local glm::mat4 projection;
local B8 keyboard[256] = { false };
local FILE* logFile;
local U8 renderDistance = 6;
local R_Camera camera;

function U32 WindowFlags()
{
    const U32 f = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;
    return (windowState.fullscreen) ? f | SDL_WINDOW_FULLSCREEN_DESKTOP : f;
}

function void KeyPressCallback(U8 keycode)
{
    switch (keycode)
    {
    case SDL_SCANCODE_ESCAPE:
        windowState.inGame = !windowState.inGame;
        //windowState.running = 0;
        break;

    case SDL_SCANCODE_F11:
        windowState.fullscreen = !windowState.fullscreen;
        SDL_SetWindowFullscreen(windowState.window, WindowFlags());
        break;

    case SDL_SCANCODE_COMMA:
        wireframeMode = !wireframeMode;
        if (wireframeMode)
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        else
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        break;

    case SDL_SCANCODE_Q:
        if (chunks[0].voxels[0][0][31] != W_BlockID::BlockID_Air)
            chunks[0].voxels[0][0][31] = W_BlockID::BlockID_Air;
        else
            chunks[0].voxels[0][0][31] = W_BlockID::BlockID_Dirt;
        chunks[0].GenerateMesh();
        break;

    default:
        keyboard[keycode] = true;
        break;
    }
}

function void KeyReleaseCallback(U8 keycode)
{
    switch (keycode)
    {
    default:
        keyboard[keycode] = false;
        break;
    }
}

int main(int argc, char** argv)
{
    windowState = {
        .width = 1280,
        .height = 720,
        .fullscreen = false,
        .running = true,
        .inGame = true
    };

    wireframeMode = false;

    // Init Log file
    errno_t returnValue = fopen_s(&logFile, Data("logs/latest.txt"), "w+");

    if (SDL_Init(SDL_INIT_EVENTS | SDL_INIT_TIMER | SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
        throw("Failed to initialize SDL2: %s", SDL_GetError());

    // OpenGL Attributes
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, SDL_TRUE);

    windowState.window = SDL_CreateWindow("Unventure", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowState.width, windowState.height, WindowFlags());
    assert(windowState.window);

    SDL_WarpMouseInWindow(windowState.window, windowState.width / 2, windowState.height / 2);
    //SDL_SetRelativeMouseMode(SDL_TRUE);

    {
        SDL_Surface* iconSurface = IMG_Load(Data("os/Dungeons.png"));
        SDL_SetWindowIcon(windowState.window, iconSurface);
        SDL_FreeSurface(iconSurface);
    }

    SDL_GLContext glContext = SDL_GL_CreateContext(windowState.window);
    if (!glContext)
        throw("Failed to create OpenGL context");

    // Check OpenGL properties
    {
        if (!gladLoadGLLoader(SDL_GL_GetProcAddress))
            throw("Failed to initialize GLAD!");

        LOG("Vendor:   %s\n", glGetString(GL_VENDOR));
        LOG("Renderer: %s\n", glGetString(GL_RENDERER));
        LOG("Version:  %s\n", glGetString(GL_VERSION));
    }

    // VSYNC
    SDL_GL_SetSwapInterval(SDL_FALSE);

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    {
        SDL_Surface* img = IMG_Load(Data("textures/terrain-textured.png"));

        glGenTextures(1, &terrainTexture);
        glBindTexture(GL_TEXTURE_2D, terrainTexture);

        I32 mode = GL_RGB;
        if (img->format->BytesPerPixel == 4)
            mode = GL_RGBA;

        glTexImage2D(GL_TEXTURE_2D, 0, mode, img->w, img->h, 0, mode, GL_UNSIGNED_BYTE, img->pixels);

        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        SDL_FreeSurface(img);
    }

    
    R_Shader shader;
    shader.LoadShaders(Data("shaders/block.vert"), Data("shaders/block.frag"));

    //Chunk
    for (U8 y = 0; y < renderDistance; ++y)
    {
        for (U8 x = 0; x < renderDistance; ++x)
        {
            W_Chunk chunk;
            chunk.pos = glm::vec3((x - renderDistance / 2) * CHUNK_WIDTH, 0.0f, (y - renderDistance / 2) * CHUNK_WIDTH);
            chunk.GenerateVoxels();
            chunk.GenerateMesh();

            chunks.push_back(chunk);
        }
    }
    while (windowState.running)
    {
        {
            U64 currentTime = SDL_GetTicks64();
            deltaTime = (F32)(currentTime - lastTime) / 1000.0f;
            lastTime = currentTime;

            if (lastFrameTime < time(0))
            {
                SDL_SetWindowTitle(windowState.window, (std::to_string(frameCount) + " FPS - Dungeons").c_str());
                frameCount = 0;
                lastFrameTime = time(0);
            }
            ++frameCount;
        }

        SDL_Event e;
        while (SDL_PollEvent(&e))
        {
            switch (e.type)
            {
            case SDL_KEYDOWN:
                KeyPressCallback(e.key.keysym.scancode);
                break;

            case SDL_KEYUP:
                KeyReleaseCallback(e.key.keysym.scancode);
                break;

            case SDL_QUIT:
                windowState.running = 0;
                break;

            case SDL_WINDOWEVENT:
                SDL_GetWindowSize(windowState.window, &windowState.width, &windowState.height);
                projection = glm::perspective(glm::radians(60.0f), (F32)windowState.width / windowState.height, 0.1f, 1000.0f);
                break;

            default:
                break;
            }
        }

        if (windowState.inGame)
        {
            // Camera move
            F32 cameraSpeed = 20.0f * deltaTime;
            if (keyboard[SDL_SCANCODE_W])
                camera.pos += cameraSpeed * camera.front;
            if (keyboard[SDL_SCANCODE_S])
                camera.pos -= cameraSpeed * camera.front;
            if (keyboard[SDL_SCANCODE_A])
                camera.pos -= glm::normalize(glm::cross(camera.front, DIRECTION_UP)) * cameraSpeed;
            if (keyboard[SDL_SCANCODE_D])
                camera.pos += glm::normalize(glm::cross(camera.front, DIRECTION_UP)) * cameraSpeed;

            // Camera rotate
            {
                //SDL_ShowCursor(SDL_DISABLE);
                I32 midX = windowState.width / 2;
                I32 midY = windowState.height / 2;
                F32 sensitivity = 0.25f * deltaTime;

                I32 tmpX, tmpY;
                SDL_GetMouseState(&tmpX, &tmpY);
                //SDL_WarpMouseInWindow(windowState.window, midX, midY);

                camera.rotation.y -= sensitivity * (F32)(midX - tmpX);
                camera.rotation.x += sensitivity * (F32)(midY - tmpY);

                if (camera.rotation.x > 89.0f)
                    camera.rotation.x = 89.0f;
                if (camera.rotation.x < -89.0f)
                    camera.rotation.x = -89.0f;

                camera.direction.x = cos(glm::radians(camera.rotation.y)) * cos(glm::radians(camera.rotation.x));
                camera.direction.y = sin(glm::radians(camera.rotation.x));
                camera.direction.z = sin(glm::radians(camera.rotation.y)) * cos(glm::radians(camera.rotation.x));
                camera.front = glm::normalize(camera.direction);
            }
        }
        else
        {
            SDL_ShowCursor(SDL_ENABLE);
        }

        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = glm::lookAt(camera.pos, camera.pos + camera.front, DIRECTION_UP);
        
        // Render init
        SDL_GL_SwapWindow(windowState.window);
        glViewport(0, 0, windowState.width, windowState.height);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        glBindTexture(GL_TEXTURE_2D, terrainTexture);

        shader.Use();
        shader.SetUniform("uTexture", 0);
        shader.SetUniform("uProjection", glm::value_ptr(projection));
        shader.SetUniform("uView", glm::value_ptr(view));

        for (U8 i = 0; i < chunks.size(); ++i)
        {
            model = glm::translate(glm::vec3(chunks[i].pos.x, chunks[i].pos.y, chunks[i].pos.z));
            shader.SetUniform("uModel", glm::value_ptr(model));
            chunks[i].mesh.Draw();
        }
    }

    // Deinitialize
    fclose(logFile);
    SDL_Quit();
    
    return 0;
}