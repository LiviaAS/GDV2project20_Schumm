#pragma once
#include "yoshix.h"
#include "stdlib.h"
#include <vector>
#include <string>
using namespace gfx;

struct SEntity
{
	BHandle* mesh;
	float position[3];
	float scale[3];
	float rotation[3];
	float worldMatrix[16];
};

struct S3VectorMatrix
{
	float xVector[3];
	float yVector[3];
	float zVector[3];
};

class CApplication : public IApplication
{
public:

	CApplication();
	virtual ~CApplication();

private:

	float fieldOfViewY;					// Vertical view angle of the camera
	float nearDist;						// Near distance of the view frustum
	float farDist;						// Far distance of the view frustum
	float viewMatrix[16];				// The view matrix to transform a mesh from world space into view space.
	float projectionMatrix[16];			// The projection matrix to transform a mesh from view space into clip space.
//	float perspectiveMatrix[16];

	// camera perspective variables
	float cameraPosition[3];
	float cameraTarget[3];
	float cameraUp[3];

	// textures
	BHandle cubeTextures[9];
	BHandle areaTexture;

	// materials
	BHandle cubeMaterials[9];
	BHandle areaMaterial;

	// constant buffers
	BHandle cb_worldMatrix;
	BHandle cb_viewProjectionMatrix;

	// shaders
	BHandle vertexShader;
	BHandle pixelShader;

	// meshes
	BHandle cubeMeshes[9];
	BHandle areaMesh;

	// entities
	SEntity cubePtr;					// cube entity as current curser
	std::vector<SEntity> cubeVector;	// for dynamic saving of cube entities 
	SEntity area;

	// check variables
	int colorsIterator;					
	bool DRAW_KEY_PRESSED;
	int wHeight;
	int wWidth;

	// ascii keys
	const unsigned int UP_KEY = 38;
	const unsigned int DOWN_KEY = 40;
	const unsigned int LEFT_KEY = 37;
	const unsigned int RIGHT_KEY = 39;
	const unsigned int SPACE_KEY = 32;
	const unsigned int PLUS_KEY = 187;
	const unsigned int MINUS_KEY = 189;
	const unsigned int W_KEY = 87;
	const unsigned int A_KEY = 65;
	const unsigned int S_KEY = 83;
	const unsigned int D_KEY = 68;
	const unsigned int N1_KEY = 49;
	const unsigned int N2_KEY = 50;
	const unsigned int N3_KEY = 51;
	const unsigned int N4_KEY = 52;
	const unsigned int ESC_KEY = 27;

	// mouse buttons
	const int BTN_LEFT = 0;
	const int BTN_RIGHT = 2;
	const int WHEEL_UP = 120;
	const int WHEEL_DOWN = -120;
	const int WHEEL_CLICK = 1;

	// variables for user interaction
	const float AREA_SIZE = 50.0f;
	const float DIST_CUBE_CAM = 10.0f;
	const float CUBE_MAX_SCALE = 2.0f;
	const float CUBE_MIN_SCALE = 0.2f;
	const float SCALE_VAR = 0.05f;
	const float MOVE_VAR = 0.1f;
	const float ROT_VAR = 0.1f;
	const char* cubeColors[9] = {	"..\\data\\images\\color_weiﬂ.jpg",
									"..\\data\\images\\color_grau.png",
									"..\\data\\images\\color_schwarz.jpg",
									"..\\data\\images\\rgb_blue.png",
									"..\\data\\images\\rgb_cyan.png",
									"..\\data\\images\\rgb_green.png", 
									"..\\data\\images\\rgb_yellow.png",
									"..\\data\\images\\rgb_red.png",
									"..\\data\\images\\rgb_magenta.jpg"	};

	/*
		NOTE:
		global rotMatrix anlegen, in yoshix GetXYZRoation geben und so anpassen
	// rotation calculation variables
	S3VectorMatrix rotationVectors;
	float perspectiveVektor[3];
	*/

private:
	// -----------------------------------------------------------------------------
	//	individual functions for this application
	bool AddCube();
	bool DrawEntity(SEntity _Entity, float _WorldMatrix[16]);
	bool CompareFloats(float A, float B, float epsilon = 0.005f);
	//S3VectorMatrix CalcRotAxis();
	//bool EditYZVectors(float _Alpha);		// for up and down rotation	
	//bool EditXZVectors(float _Alpha);		// for left and right rotation

	// -----------------------------------------------------------------------------
	// yoshix functions
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