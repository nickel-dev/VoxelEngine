#pragma once

#include <vector>
#include <glad/glad.h>
#include <PerlinNoise.h>
#include "../base/base_inc.h"

#define CHUNK_WIDTH         32
#define CHUNK_HEIGHT        32

enum W_BlockID
{
    BlockID_Air         = 0,
    BlockID_Grass       = 1,
    BlockID_Stone       = 2,
    BlockID_Dirt        = 3
};

enum W_BlockNormal
{
    BlockNormal_Bottom  = 0,
    BlockNormal_Right   = 1,
    BlockNormal_Front   = 2,
    BlockNormal_Left    = 3,
    BlockNormal_Back    = 4,
    BlockNormal_Top     = 5
};

struct W_ChunkVertex
{
    glm::vec3 pos;
    F32 normal;
    glm::vec2 texCoord;

    W_ChunkVertex();
    W_ChunkVertex(glm::u8vec3 pPos, U8 pNormal, glm::vec2 pTexCoord);
};

class W_ChunkMesh
{
public:
    std::vector<W_ChunkVertex> vertices;
    std::vector<U32> indices;

    U32 vao, vbo, ebo;
    U32 currIndex = 0;

    void Face(glm::u8vec3 pos, U8 normal, U8 blockId);
    void SetupMesh();
    void Draw();
};

struct W_Chunk
{
    glm::vec3 pos;
    U8 voxels[CHUNK_WIDTH][CHUNK_WIDTH][CHUNK_HEIGHT];
    W_ChunkMesh mesh;

    void GenerateVoxels();
    void GenerateMesh();
};