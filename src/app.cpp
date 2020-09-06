#include "app.h"

CApplication::CApplication()
	: m_FieldOfViewY(60.0f)        // Set the vertical view angle of the camera to 60 degrees.
{
}

// -----------------------------------------------------------------------------

CApplication::~CApplication()
{
}

// -----------------------------------------------------------------------------

bool CApplication::InternOnCreateTextures()
{
	// -----------------------------------------------------------------------------
	// Path is "..\\data\\images\\texture.dds"
	// -----------------------------------------------------------------------------
	return true;
}

// -----------------------------------------------------------------------------

bool CApplication::InternOnReleaseTextures()
{
	return true;
}

// -----------------------------------------------------------------------------

bool CApplication::InternOnCreateConstantBuffers()
{
	return true; 
}

// -----------------------------------------------------------------------------

bool CApplication::InternOnReleaseConstantBuffers()
{
	return true;
}

// -----------------------------------------------------------------------------

bool CApplication::InternOnCreateShader()
{
	return true;
}

// -----------------------------------------------------------------------------

bool CApplication::InternOnReleaseShader()
{
	return true;
}

// -----------------------------------------------------------------------------

bool CApplication::InternOnCreateMaterials()
{
	return true;
}

// -----------------------------------------------------------------------------

bool CApplication::InternOnReleaseMaterials()
{
	return true;
}

// -----------------------------------------------------------------------------

bool CApplication::InternOnCreateMeshes()
{
	return true;
}

// -----------------------------------------------------------------------------

bool CApplication::InternOnReleaseMeshes()
{
	return true;
}

// -----------------------------------------------------------------------------

bool CApplication::InternOnResize(int _Width, int _Height)
{
	return true;
}

// -----------------------------------------------------------------------------

bool CApplication::InternOnUpdate()
{
	return true;
}

// -----------------------------------------------------------------------------

bool CApplication::InternOnFrame()
{
	return true;
}