#include "meshes.h"

const float TEX_MIN = 0.0f;
const float TEX_MAX = 1.0f;

const int INDICES_PER_TRIANGLE = 3;

void CreateMeshObj(int numOfVertices, float* vertices, int numOfTriangles, int* triangles, BHandle& material, BHandle& mesh)
{
    SMeshInfo meshInfo;

    meshInfo.m_NumberOfVertices = numOfVertices;
    meshInfo.m_pVertices = vertices;

    meshInfo.m_NumberOfIndices = numOfTriangles * INDICES_PER_TRIANGLE;
    meshInfo.m_pIndices = triangles;

    meshInfo.m_pMaterial = material;

    CreateMesh(meshInfo, &mesh);
}

void CreateCubeMesh(BHandle& mesh, BHandle& material)
{
    float e = 0.5f; // half-edge length

    float vertices[][8] = {
        // front
        { -e, e,-e,  TEX_MIN, TEX_MIN,  0.0f, 0.0f,-1.0f },
        { -e,-e,-e,  TEX_MIN, TEX_MAX,  0.0f, 0.0f,-1.0f },
        {  e,-e,-e,  TEX_MAX, TEX_MAX,  0.0f, 0.0f,-1.0f },
        {  e, e,-e,  TEX_MAX, TEX_MIN,  0.0f, 0.0f,-1.0f },
        // back
        { -e,-e, e,  TEX_MIN, TEX_MIN,  0.0f, 0.0f, 1.0f },
        { -e, e, e,  TEX_MIN, TEX_MAX,  0.0f, 0.0f, 1.0f },
        {  e, e, e,  TEX_MAX, TEX_MAX,  0.0f, 0.0f, 1.0f },
        {  e,-e, e,  TEX_MAX, TEX_MIN,  0.0f, 0.0f, 1.0f },
        // top
        { -e, e, e,  TEX_MIN, TEX_MIN,  0.0f, 1.0f, 0.0f },
        { -e, e,-e,  TEX_MIN, TEX_MAX,  0.0f, 1.0f, 0.0f },
        {  e, e,-e,  TEX_MAX, TEX_MAX,  0.0f, 1.0f, 0.0f },
        {  e, e, e,  TEX_MAX, TEX_MIN,  0.0f, 1.0f, 0.0f },
        // bottom
        { -e,-e,-e,  TEX_MIN, TEX_MIN,  0.0f,-1.0f, 0.0f },
        { -e,-e, e,  TEX_MIN, TEX_MAX,  0.0f,-1.0f, 0.0f },
        {  e,-e, e,  TEX_MAX, TEX_MAX,  0.0f,-1.0f, 0.0f },
        {  e,-e,-e,  TEX_MAX, TEX_MIN,  0.0f,-1.0f, 0.0f },
        // right
        {  e, e,-e,  TEX_MIN, TEX_MIN,  1.0f, 0.0f, 0.0f },
        {  e,-e,-e,  TEX_MIN, TEX_MAX,  1.0f, 0.0f, 0.0f },
        {  e,-e, e,  TEX_MAX, TEX_MAX,  1.0f, 0.0f, 0.0f },
        {  e, e, e,  TEX_MAX, TEX_MIN,  1.0f, 0.0f, 0.0f },
        // left
        { -e, e, e,  TEX_MIN, TEX_MIN, -1.0f, 0.0f, 0.0f },
        { -e,-e, e,  TEX_MIN, TEX_MAX, -1.0f, 0.0f, 0.0f },
        { -e,-e,-e,  TEX_MAX, TEX_MAX, -1.0f, 0.0f, 0.0f },
        { -e, e,-e,  TEX_MAX, TEX_MIN, -1.0f, 0.0f, 0.0f },
    };

    int triangles[][3] = {
        {  0, 1, 2 }, {  0, 2, 3 },
        {  4, 5, 6 }, {  4, 6, 7 },
        {  8, 9,10 }, {  8,10,11 },
        { 12,13,14 }, { 12,14,15 },
        { 16,17,18 }, { 16,18,19 },
        { 20,21,22 }, { 20,22,23 },
    };

    CreateMeshObj(24, &vertices[0][0], 12, &triangles[0][0], material, mesh);
}