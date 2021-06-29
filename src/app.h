#pragma once
//#include "yoshix.h"
#include "stdlib.h"
#include "keys.h"
#include "helper_structs.h"
#include <vector>
#include <string>
using namespace gfx;

/*
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

*/

class CApplication : public IApplication
{
public:

	CApplication();
	virtual ~CApplication();

private:

	// float m_FieldOfViewY;					// Vertical view angle of the camera
	// float m_NearDist;						// Near distance of the view frustum
	// float m_FarDist;						// Far distance of the view frustum
	// float m_aViewMatrix[16];				// The view matrix to transform a mesh from world space into view space.
	// float m_aProjectionMatrix[16];			// The projection matrix to transform a mesh from view space into clip space.
//	// float perspectiveMatrix[16];
	// 
	// // camera perspective variables
	// float m_aCameraPosition[3];
	// float m_aCameraTarget[3];
	// float m_aCameraUp[3];

	SCamera m_SCamera;

	// textures
	BHandle m_apCubeTextures[9];
	BHandle m_pAreaTexture;

	// materials
	BHandle m_paCubeMaterials[9];
	BHandle m_pAreaMaterial;

	// constant buffers
	BHandle m_pConstantBufferWorldMatrix;
	BHandle m_pConstantBufferViewProjectionMatrix;

	// shaders
	BHandle m_pVertexShader;
	BHandle m_pPixelShader;

	// meshes
	BHandle m_paCubeMeshes[9];
	BHandle m_pAreaMesh;

	// entities
	SEntity m_SCurrentCubeEntity;				// cube entity as current curser
	std::vector<SEntity> m_VCubeEntities;		// for dynamic saving of cube entities 
	SEntity m_SArea;

	// Members !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	// check variables
	int ColorsIterator;					
	static bool s_DRAW_KEY_PRESSED;
	int WindowHeight;
	int WindowWidth;

	// variables for user interaction
	const float AREA_SIZE = 100.0f;
	const float DIST_CUBE_CAM = 6.0f;
	const float CUBE_MAX_SCALE = 1.5f;
	const float CUBE_MIN_SCALE = 0.1f;
	const float SCALE_FACTOR = 0.05f;
	const float MOVE_FACTOR = 0.025f;
	const float ROT_FACTOR = 0.1f;
	const int AMOUNT_COLORS = 8;
	const char* cubeColors[8] = { "..\\data\\images\\color_weiﬂ.jpg",
									"..\\data\\images\\color_grau.png",
									"..\\data\\images\\rgb_blue.png",
									"..\\data\\images\\rgb_cyan.png",
									"..\\data\\images\\rgb_green.png",
									"..\\data\\images\\rgb_yellow.png",
									"..\\data\\images\\rgb_red.png",
									"..\\data\\images\\rgb_magenta.jpg" };

	
	/*
		NOTE:
		global rotMatrix anlegen, in yoshix GetXYZRoation geben und so anpassen
	// rotation calculation variables
	S3VectorMatrix rotationVectors;
	float perspectiveVektor[3];
	*/

private:
	// -----------------------------------------------------------------------------
	/*
		individual functions for this application
	*/
	bool AddCube();
	bool DrawEntity(SEntity _Entity, float _WorldMatrix[16]);
	bool CompareFloats(float A, float B, float epsilon = 0.005f);
	//S3VectorMatrix CalcRotAxis();
	//bool EditYZVectors(float _Alpha);		// for up and down rotation	
	//bool EditXZVectors(float _Alpha);		// for left and right rotation

	// -----------------------------------------------------------------------------
	/* 
		yoshix functions
	*/
	virtual bool CreateMaterial(BHandle& texture, BHandle& material);
	virtual bool InternOnStartup();
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
	virtual bool InternOnKeyEvent(unsigned _Key, bool _IsKeyDown, bool _IsAltDown);
	virtual bool InternOnMouseEvent(int _X, int	_Y, int _Button, bool _IsButtonDown, bool _IsDoubleClick, int _WheelDelta);
};