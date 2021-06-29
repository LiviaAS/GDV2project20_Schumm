#pragma once
#include "yoshix.h"
using namespace gfx;

// SIND DAS MEMBER VARIABLEN?

struct SEntity
{
	BHandle* m_pBMesh;
	float m_aPosition[3];
	float m_aScale[3];
	float m_aRotation[3];
	float m_aWorldMatrix[16];
};

struct S3VectorMatrix
{
	float m_aXVector[3];
	float m_aYVector[3];
	float m_aZVector[3];
};

struct SCamera 
{
	float m_FieldOfViewY;					// Vertical view angle of the camera
	float m_NearDist;						// Near distance of the view frustum
	float m_FarDist;						// Far distance of the view frustum
	float m_aViewMatrix[16];				// The view matrix to transform a mesh from world space into view space.
	float m_aProjectionMatrix[16];			// The projection matrix to transform a mesh from view space into clip space.
	//	float perspectiveMatrix[16];

	// camera perspective variables
	float m_aCameraPosition[3];
	float m_aCameraTarget[3];
	float m_aCameraUp[3];
};
