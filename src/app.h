#pragma once

#include "yoshix.h"

using namespace gfx;

class CApplication : public IApplication
{
public:

	CApplication();
	virtual ~CApplication();

private:

	float m_FieldOfViewY;            

private:

	virtual bool InternOnCreateTextures();
	virtual bool InternOnReleaseTextures();
	virtual bool InternOnCreateConstantBuffers();
	virtual bool InternOnReleaseConstantBuffers();
	virtual bool InternOnCreateShader();
	virtual bool InternOnReleaseShader();
	virtual bool InternOnCreateMaterials();
	virtual bool InternOnReleaseMaterials();
	virtual bool InternOnCreateMeshes();
	virtual bool InternOnReleaseMeshes();
	virtual bool InternOnResize(int _Width, int _Height);
	virtual bool InternOnUpdate();
	virtual bool InternOnFrame();
};