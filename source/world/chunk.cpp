#include "chunk.h"

/// W_ChunkVertex, the vertex making up a W_Chunk mesh
W_ChunkVertex::W_ChunkVertex()
{
    return;
}

W_ChunkVertex::W_ChunkVertex(glm::u8vec3 pPos, U8 pNormal, glm::vec2 pTexCoord)
{
    pos = pPos;
    normal = pNormal;
    texCoord = pTexCoord;
}

/// W_ChunkMesh, a specifically optimized Mesh for the W_Chunk
void W_ChunkMesh::Face(glm::u8vec3 pos, U8 normal, U8 blockId)
{
    glm::vec2 texCoord(blockId * 0.0625, (blockId + 1) * 0.0625);

    switch (normal)
    {
    case BlockNormal_Top:
        vertices.push_back(W_ChunkVertex(glm::u8vec3(pos.x + 1, pos.y + 1, pos.z + 1), BlockNormal_Top, texCoord + glm::vec2(0.0625f, 0.0625f)));
        vertices.push_back(W_ChunkVertex(glm::u8vec3(pos.x + 1, pos.y + 1, pos.z + 0), BlockNormal_Top, texCoord + glm::vec2(0.0625f, 0.0f)));
        vertices.push_back(W_ChunkVertex(glm::u8vec3(pos.x + 0, pos.y + 1, pos.z + 0), BlockNormal_Top, texCoord + glm::vec2(0.0f, 0.0f)));
        vertices.push_back(W_ChunkVertex(glm::u8vec3(pos.x + 0, pos.y + 1, pos.z + 1), BlockNormal_Top, texCoord + glm::vec2(0.0f, 0.0625f)));
        break;

    case BlockNormal_Bottom:
        vertices.push_back(W_ChunkVertex(glm::u8vec3(pos.x + 0, pos.y + 0, pos.z + 1), BlockNormal_Bottom, texCoord + glm::vec2(0.0625f, 0.0625f)));
        vertices.push_back(W_ChunkVertex(glm::u8vec3(pos.x + 0, pos.y + 0, pos.z + 0), BlockNormal_Bottom, texCoord + glm::vec2(0.0625f, 0.0f)));
        vertices.push_back(W_ChunkVertex(glm::u8vec3(pos.x + 1, pos.y + 0, pos.z + 0), BlockNormal_Bottom, texCoord + glm::vec2(0.0f, 0.0f)));
        vertices.push_back(W_ChunkVertex(glm::u8vec3(pos.x + 1, pos.y + 0, pos.z + 1), BlockNormal_Bottom, texCoord + glm::vec2(0.0f, 0.0625f)));
        break;

    case BlockNormal_Front:
        vertices.push_back(W_ChunkVertex(glm::u8vec3(pos.x + 0, pos.y + 1, pos.z + 1), BlockNormal_Front, texCoord + glm::vec2(0.0625f, 0.0625f)));
        vertices.push_back(W_ChunkVertex(glm::u8vec3(pos.x + 0, pos.y + 0, pos.z + 1), BlockNormal_Front, texCoord + glm::vec2(0.0625f, 0.0f)));
        vertices.push_back(W_ChunkVertex(glm::u8vec3(pos.x + 1, pos.y + 0, pos.z + 1), BlockNormal_Front, texCoord + glm::vec2(0.0f, 0.0f)));
        vertices.push_back(W_ChunkVertex(glm::u8vec3(pos.x + 1, pos.y + 1, pos.z + 1), BlockNormal_Front, texCoord + glm::vec2(0.0f, 0.0625f)));
        break;

    case BlockNormal_Back:
        vertices.push_back(W_ChunkVertex(glm::u8vec3(pos.x + 1, pos.y + 1, pos.z + 0), BlockNormal_Back, texCoord + glm::vec2(0.0625f, 0.0625f)));
        vertices.push_back(W_ChunkVertex(glm::u8vec3(pos.x + 1, pos.y + 0, pos.z + 0), BlockNormal_Back, texCoord + glm::vec2(0.0625f, 0.0f)));
        vertices.push_back(W_ChunkVertex(glm::u8vec3(pos.x + 0, pos.y + 0, pos.z + 0), BlockNormal_Back, texCoord + glm::vec2(0.0f, 0.0f)));
        vertices.push_back(W_ChunkVertex(glm::u8vec3(pos.x + 0, pos.y + 1, pos.z + 0), BlockNormal_Back, texCoord + glm::vec2(0.0f, 0.0625f)));
        break;

    case BlockNormal_Right:
        vertices.push_back(W_ChunkVertex(glm::u8vec3(pos.x + 1, pos.y + 1, pos.z + 1), BlockNormal_Right, texCoord + glm::vec2(0.0625f, 0.0625f)));
        vertices.push_back(W_ChunkVertex(glm::u8vec3(pos.x + 1, pos.y + 0, pos.z + 1), BlockNormal_Right, texCoord + glm::vec2(0.0625f, 0.0f)));
        vertices.push_back(W_ChunkVertex(glm::u8vec3(pos.x + 1, pos.y + 0, pos.z + 0), BlockNormal_Right, texCoord + glm::vec2(0.0f, 0.0f)));
        vertices.push_back(W_ChunkVertex(glm::u8vec3(pos.x + 1, pos.y + 1, pos.z + 0), BlockNormal_Right, texCoord + glm::vec2(0.0f, 0.0625f)));
        break;

    case BlockNormal_Left:
        vertices.push_back(W_ChunkVertex(glm::u8vec3(pos.x + 0, pos.y + 1, pos.z + 0), BlockNormal_Left, texCoord + glm::vec2(0.0625f, 0.0625f)));
        vertices.push_back(W_ChunkVertex(glm::u8vec3(pos.x + 0, pos.y + 0, pos.z + 0), BlockNormal_Left, texCoord + glm::vec2(0.0625f, 0.0f)));
        vertices.push_back(W_ChunkVertex(glm::u8vec3(pos.x + 0, pos.y + 0, pos.z + 1), BlockNormal_Left, texCoord + glm::vec2(0.0f, 0.0f)));
        vertices.push_back(W_ChunkVertex(glm::u8vec3(pos.x + 0, pos.y + 1, pos.z + 1), BlockNormal_Left, texCoord + glm::vec2(0.0f, 0.0625f)));
        break;

    default:
        printf("Invalid block direction: %d\n", normal);
        assert(0);
        break;
    }

    U32 n[] = {
        currIndex + 0, currIndex + 1, currIndex + 3,
        currIndex + 1, currIndex + 2, currIndex + 3
    };

    currIndex += 4;

    for (U8 i = 0; i < 6; ++i)
        indices.push_back(n[i]);
}

void W_ChunkMesh::SetupMesh()
{
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(W_ChunkVertex), &vertices[0], GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(W_ChunkVertex), NULL);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, sizeof(W_ChunkVertex), (void*)(sizeof(F32) * 3));

    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(W_ChunkVertex), (void*)(sizeof(F32) * 3 + sizeof(I32)));
}

void W_ChunkMesh::Draw()
{
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, (U32)indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

/// W_Chunk, the Voxel chunk
function const I32 Noise2D(glm::vec2 pos, glm::vec2 offset)
{
    const siv::PerlinNoise::seed_type seed = 12345u;
    const siv::PerlinNoise perlin{ seed };

    const I32 result = perlin.normalizedOctave2D_01((pos.x + offset.x) / 50, (pos.y + offset.y) / 50, 3) * (CHUNK_HEIGHT - 1);
    return result;
}

void W_Chunk::GenerateVoxels()
{
    memset(&voxels[0][0][0], BlockID_Air, sizeof(voxels));

    for (int z = 0; z < CHUNK_WIDTH; ++z)
    for (int x = 0; x < CHUNK_WIDTH; ++x)
    {
        const I32 noise = Noise2D(glm::vec2(pos.x, pos.z), glm::vec2(x, z));
        
        for (U8 i = 0; i < (U8)noise; ++i)
        {
            U8 blockID = BlockID_Dirt;
            
            if (i >= 3)
                blockID = BlockID_Grass;
            if (i >= 5)
                blockID = BlockID_Stone;

            voxels[x][z][i] = blockID;
        }
    }
}

void W_Chunk::GenerateMesh()
{
    mesh.vertices.clear();
    mesh.indices.clear();
    mesh.currIndex = 0;

    for (U8 x = 0; x < CHUNK_WIDTH; ++x)
    for (U8 z = 0; z < CHUNK_WIDTH; ++z)
    for (U8 y = 0; y < CHUNK_HEIGHT; ++y)
    {
        U16 v = voxels[x][z][y];
        if (v == BlockID_Air)
            continue;

        if (x == CHUNK_WIDTH - 1)
        {
            const I32 noise = Noise2D(glm::vec2(pos.x, pos.z), glm::vec2(x + 1, z));
            if (y + 1 > noise)
                mesh.Face(glm::u8vec3(x, y, z), BlockNormal_Right, v);
        }
        if (x == 0)
        {
            const I32 noise = Noise2D(glm::vec2(pos.x, pos.z), glm::vec2(x - 1, z));
            if (y + 1 > noise)
                mesh.Face(glm::u8vec3(x, y, z), BlockNormal_Left, v);
        }

        if (z == CHUNK_WIDTH - 1)
        {
            const I32 noise = Noise2D(glm::vec2(pos.x, pos.z), glm::vec2(x, z + 1));
            if (y + 1 > noise)
                mesh.Face(glm::u8vec3(x, y, z), BlockNormal_Front, v);
        }
        if (z == 0)
        {
            const I32 noise = Noise2D(glm::vec2(pos.x, pos.z), glm::vec2(x, z - 1));
            if (y + 1 > noise)
                mesh.Face(glm::u8vec3(x, y, z), BlockNormal_Back, v);
        }


        if (y == CHUNK_HEIGHT - 1 || voxels[x][z][y + 1] == BlockID_Air)
            mesh.Face(glm::u8vec3(x, y, z), BlockNormal_Top, v);
        if (y == 0 || voxels[x][z][y - 1] == BlockID_Air)
            mesh.Face(glm::u8vec3(x, y, z), BlockNormal_Bottom, v);


        if (x != CHUNK_WIDTH - 1 && voxels[x + 1][z][y] == BlockID_Air)
            mesh.Face(glm::u8vec3(x, y, z), BlockNormal_Right, v);
        if (x != 0 && voxels[x - 1][z][y] == BlockID_Air)
            mesh.Face(glm::u8vec3(x, y, z), BlockNormal_Left, v);


        if (z != CHUNK_WIDTH - 1 && voxels[x][z + 1][y] == BlockID_Air)
            mesh.Face(glm::u8vec3(x, y, z), BlockNormal_Front, v);
        if (z != 0 && voxels[x][z - 1][y] == BlockID_Air)
            mesh.Face(glm::u8vec3(x, y, z), BlockNormal_Back, v);
    }

    mesh.SetupMesh();
}