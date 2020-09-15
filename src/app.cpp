#include "app.h"
#include "meshes.h"
#include "math.h"
#include <iostream>

CApplication::CApplication()
	: fieldOfViewY(60.0f)
	, nearDist(0.1f)
	, farDist(100.0f)
	, colorsIterator(0)

	, cb_viewProjectionMatrix(nullptr)
	, cb_worldMatrix(nullptr)
	, vertexShader(nullptr)
	, pixelShader(nullptr)

	, areaTexture(nullptr)
	, areaMaterial(nullptr)
	, areaMesh(nullptr)

	, DRAW_KEY_PRESSED(false)
	, wHeight(0)
	, wWidth(0)
	, MOVE_VAR(0.025)
{
	for (int i = 0; i < amountColors; i++)
	{
		this->cubePtr = {
			&this->cubeMeshes[colorsIterator],
			  AREA_SIZE / 2,   CUBE_MAX_SCALE / 2,	AREA_SIZE / 2,		// coordinates in the world
					0.1f,					0.1f,			0.1f,		// coordinates for scaling
					0.0f,					0.0f,			0.0f		// rotation
		};
	}; 

	this->area = {
		&this->areaMesh,
		(AREA_SIZE / 2),   -0.5f, (AREA_SIZE / 2),				// coordinates in the world
			AREA_SIZE,    0.1f,		AREA_SIZE,				// coordinates for scaling
				 0.0f,    0.0f,			0.0f				// rotation
	};

	// camera perspective variables
	this->cameraPosition[0] = this->cubePtr.position[0];
	this->cameraPosition[1] = this->cubePtr.position[1];	
	this->cameraPosition[2] = this->cubePtr.position[2] - DIST_CUBE_CAM;

	this->cameraTarget[0]	= this->cubePtr.position[0];
	this->cameraTarget[1]	= this->cubePtr.position[1];	
	this->cameraTarget[2]	= this->cubePtr.position[2];

	this->cameraUp[0]		= 0.0f;		
	this->cameraUp[1]		= 1.0f;							
	this->cameraUp[2]		= 0.0f;

/*	// direction(?) vectors for rotation and camera perspektive
	// initial x-axis vector							// initial y-axis vector							// initial z-axis vector == camera perspektive
	this->rotationVectors.xVector[0] = DIST_CUBE_CAM;	this->rotationVectors.yVector[0] = 0.0f;			this->rotationVectors.zVector[0] = 0.0f;
	this->rotationVectors.xVector[1] = 0.0f;			this->rotationVectors.yVector[1] = DIST_CUBE_CAM;	this->rotationVectors.zVector[1] = 0.0f;
	this->rotationVectors.xVector[2] = 0.0f;			this->rotationVectors.yVector[2] = 0.0f;			this->rotationVectors.zVector[2] = DIST_CUBE_CAM;
*/
}

// -----------------------------------------------------------------------------

CApplication::~CApplication()
{
}

// -----------------------------------------------------------------------------

bool CApplication::AddCube()
{
	// save current cube in vector to be drawn
	SEntity drawedCube = {
		&this->cubeMeshes[colorsIterator],	
		this->cubePtr.position[0], this->cubePtr.position[1], this->cubePtr.position[2],
		this->cubePtr.scale[0], this->cubePtr.scale[1], this->cubePtr.scale[2],
		this->cubePtr.rotation[0], this->cubePtr.rotation[1], this->cubePtr.rotation[2]
	};

	this->cubeVector.push_back(drawedCube);

	return true;
}

bool CApplication::DrawEntity(SEntity _Entity, float _WorldMatrix[16])
{
	GetIdentityMatrix(_WorldMatrix);
	GetIdentityMatrix(_Entity.worldMatrix);

	float tmpMatrix[16];

	GetScaleMatrix(_Entity.scale[0], _Entity.scale[1], _Entity.scale[2], tmpMatrix);
	MulMatrix(_Entity.worldMatrix, tmpMatrix, _Entity.worldMatrix);

	GetTranslationMatrix(_Entity.position[0], _Entity.position[1], _Entity.position[2], tmpMatrix);
	MulMatrix(_Entity.worldMatrix, tmpMatrix, _Entity.worldMatrix);
	
	if (!CompareFloats(0.0f, _Entity.rotation[0]))
	{
		GetRotationXMatrix(_Entity.rotation[0], tmpMatrix);
		MulMatrix(_Entity.worldMatrix, tmpMatrix, _Entity.worldMatrix);
	};

	if (!CompareFloats(0.0f, _Entity.rotation[1]))
	{
		GetRotationYMatrix(_Entity.rotation[1], tmpMatrix);
		MulMatrix(_Entity.worldMatrix, tmpMatrix, _Entity.worldMatrix);
	};

	if (!CompareFloats(0.0f, _Entity.rotation[2]))
	{
		GetRotationZMatrix(_Entity.rotation[2], tmpMatrix);
		MulMatrix(_Entity.worldMatrix, tmpMatrix, _Entity.worldMatrix);
	};

	MulMatrix(_WorldMatrix, _Entity.worldMatrix, _WorldMatrix);
	UploadConstantBuffer(_WorldMatrix, this->cb_worldMatrix);
	DrawMesh(*_Entity.mesh);

	return true;
}

// -----------------------------------------------------------------------------

bool CApplication::CompareFloats(float A, float B, float epsilon)
{
	return (fabs(A - B) < epsilon);
}

// -----------------------------------------------------------------------------
/*
// x-rotation
bool CApplication::EditYZVectors(float _Alpha)
{
	// new direction vector y-axis
	this->rotationVectors.yVector[1] = cameraPosition[1] - sin(_Alpha);
	this->rotationVectors.yVector[2] = cameraPosition[2] + cos(_Alpha);
	/*
	this->rotationVectors.yVector[0] = this->cameraPosition[0];
	this->rotationVectors.yVector[1] = this->cameraPosition[1] - sin(_Alpha);
	this->rotationVectors.yVector[2] = this->cameraPosition[2] + cos(_Alpha);
	

	// new direction vector z-axis		
	this->rotationVectors.zVector[1] = cameraPosition[1] + cos(_Alpha);
	this->rotationVectors.zVector[2] = cameraPosition[2] + sin(_Alpha);
	/*
	this->rotationVectors.zVector[0] = this->cameraPosition[0];					
	this->rotationVectors.zVector[1] = this->cameraPosition[1] + cos(_Alpha);
	this->rotationVectors.zVector[2] = this->cameraPosition[2] + sin(_Alpha);
	*
	return false;
}

// -----------------------------------------------------------------------------
// y-rotation
bool CApplication::EditXZVectors(float _Alpha)
{
	// new vector x-axis
	this->rotationVectors.xVector[0] += cameraPosition[0] + (cos(_Alpha) * DIST_CUBE_CAM);
	this->rotationVectors.xVector[2] += cameraPosition[2] + (sin(_Alpha) * DIST_CUBE_CAM);
	/*
	this->rotationVectors.xVector[0] = this->cameraPosition[0];
	this->rotationVectors.xVector[1] = this->cameraPosition[1] + cos(_Alpha);
	this->rotationVectors.xVector[2] = this->cameraPosition[2] + sin(_Alpha);
	*

	// new vector z-axis
	this->rotationVectors.zVector[0] += cameraPosition[0] - (sin(_Alpha) * DIST_CUBE_CAM);
	this->rotationVectors.zVector[2] += cameraPosition[2] + (cos(_Alpha) * DIST_CUBE_CAM);
	/*
	this->rotationVectors.zVector[0] = this->cameraPosition[0];
	this->rotationVectors.zVector[1] = this->cameraPosition[1] - sin(_Alpha);
	this->rotationVectors.zVector[2] = this->cameraPosition[2] + cos(_Alpha);
	*
	return true;
} */

// -----------------------------------------------------------------------------

bool CApplication::InternOnStartup()
{
	return true;
}

// -----------------------------------------------------------------------------

bool CApplication::InternOnCreateTextures()
{
	// create textures and save in array
	for (int i = 0; i < amountColors; i++)
	{
		CreateTexture(this->cubeColors[i], &this->cubeTextures[i]);
	};
	// create constant texture for the area
	CreateTexture("..\\data\\images\\map_dark.jpg", &this->areaTexture);

	return true;
}

// -----------------------------------------------------------------------------

bool CApplication::InternOnReleaseTextures()
{
	for (int i = 0; i < amountColors; i++)
	{
		ReleaseTexture(this->cubeTextures[i]);
	};
	ReleaseTexture(this->areaTexture);

	return true;
}

// -----------------------------------------------------------------------------

bool CApplication::InternOnCreateConstantBuffers()
{
	float tmp[16];

	// create constant buffer
	CreateConstantBuffer(sizeof(tmp), &this->cb_worldMatrix);
	CreateConstantBuffer(sizeof(tmp), &this->cb_viewProjectionMatrix);

	return true; 
}

// -----------------------------------------------------------------------------

bool CApplication::InternOnReleaseConstantBuffers()
{
	// release buffer after application has shut down
	ReleaseConstantBuffer(this->cb_worldMatrix);
	ReleaseConstantBuffer(this->cb_viewProjectionMatrix);

	return true;
}

// -----------------------------------------------------------------------------

bool CApplication::InternOnCreateShader()
{
	// load and compile shaders
	CreateVertexShader("..\\src\\shader.fx", "VShader", &this->vertexShader);
	CreatePixelShader("..\\src\\shader.fx", "PShader", &this->pixelShader);

	return true;
}

// -----------------------------------------------------------------------------

bool CApplication::InternOnReleaseShader()
{
	// release shaders after shutting down application
	ReleaseVertexShader(this->vertexShader);
	ReleasePixelShader(this->pixelShader);

	return true;
}

// -----------------------------------------------------------------------------

bool CApplication::CreateMaterial(BHandle& texture, BHandle& material)
{
	SMaterialInfo MaterialInfo;

	MaterialInfo.m_NumberOfTextures = 1;
	MaterialInfo.m_pTextures[0] = texture;

	MaterialInfo.m_NumberOfVertexConstantBuffers = 2;
	MaterialInfo.m_pVertexConstantBuffers[0] = this->cb_worldMatrix;
	MaterialInfo.m_pVertexConstantBuffers[1] = this->cb_viewProjectionMatrix;

	MaterialInfo.m_NumberOfPixelConstantBuffers = 0;
	MaterialInfo.m_pVertexShader = this->vertexShader;
	MaterialInfo.m_pPixelShader = this->pixelShader;

	MaterialInfo.m_NumberOfInputElements = 3;
	MaterialInfo.m_InputElements[0].m_pName = "POSITION";
	MaterialInfo.m_InputElements[0].m_Type = SInputElement::Float3;
	MaterialInfo.m_InputElements[1].m_pName = "TEXCOORD";
	MaterialInfo.m_InputElements[1].m_Type = SInputElement::Float2;
	MaterialInfo.m_InputElements[2].m_pName = "NORMAL";
	MaterialInfo.m_InputElements[2].m_Type = SInputElement::Float3;

	gfx::CreateMaterial(MaterialInfo, &material);

	return true;
}

// -----------------------------------------------------------------------------

bool CApplication::InternOnCreateMaterials()
{
	for (int i = 0; i < amountColors; i++)
	{
		CreateMaterial(this->cubeTextures[i], this->cubeMaterials[i]);
	};
	CreateMaterial(this->areaTexture, this->areaMaterial);

	return true;
}

// -----------------------------------------------------------------------------

bool CApplication::InternOnReleaseMaterials()
{
	for (int i = 0; i < amountColors; i++)
	{
		ReleaseMaterial(this->cubeMaterials[i]);
	};
	ReleaseMaterial(this->areaMaterial);

	return true;
}

// -----------------------------------------------------------------------------

bool CApplication::InternOnCreateMeshes()
{
	for (int i = 0; i < amountColors; i++)
	{
		CreateCubeMesh(this->cubeMeshes[i], this->cubeMaterials[i]);
	};
	CreateCubeMesh(this->areaMesh, this->areaMaterial);

	return true;
}

// -----------------------------------------------------------------------------

bool CApplication::InternOnReleaseMeshes()
{
	for (int i = 0; i < amountColors; i++)
	{
		ReleaseMesh(this->cubeMeshes[i]);
	};
	ReleaseMesh(this->areaMesh);

	return true;
}

// -----------------------------------------------------------------------------

bool CApplication::InternOnResize(int _Width, int _Height)
{
	GetProjectionMatrix(fieldOfViewY, static_cast<float>(_Width) / static_cast<float>(_Height), nearDist, farDist, projectionMatrix);

	// safe window size information for later use
	this->wWidth = _Width;
	this->wHeight = _Height;

	return true;
}

// -----------------------------------------------------------------------------

bool CApplication::InternOnUpdate()
{
	float viewProjectionMatrix[16];

	GetViewMatrix(this->cameraPosition, this->cameraTarget, this->cameraUp, viewMatrix);
	MulMatrix(viewMatrix, projectionMatrix, viewProjectionMatrix);
	UploadConstantBuffer(viewProjectionMatrix, this->cb_viewProjectionMatrix);

	return true;
}

// -----------------------------------------------------------------------------

bool CApplication::InternOnFrame()
{
	float worldMatrix[16];
	
	DrawEntity(this->area, worldMatrix);
	DrawEntity(this->cubePtr, worldMatrix);

	for (auto& cubeV : this->cubeVector)
	{
		DrawEntity(cubeV, worldMatrix);
	};

	if (DRAW_KEY_PRESSED)
	{
		AddCube();
	};
	
	return true;
}

// -----------------------------------------------------------------------------

bool CApplication::InternOnKeyEvent(unsigned _Key, bool _IsKeyDown, bool _IsAltDown)
{	
	/*
		key-events for drawing
	*/
	if (_Key == this->SPACE_KEY && _IsKeyDown)
	{
		DRAW_KEY_PRESSED = true;
	}
	else if (_Key == this->SPACE_KEY && !_IsKeyDown)
	{
		DRAW_KEY_PRESSED = false;
	};

	/*
		key-events for right and left movement																		
	*/
	if (this->cubePtr.position[0] > (DIST_CUBE_CAM) && _IsKeyDown &&
		((_Key == this->A_KEY && cubePtr.position[2] > cameraPosition[2]) || (_Key == this->D_KEY && cubePtr.position[2] < cameraPosition[2])))
	{
		this->cameraPosition[0] -= MOVE_VAR;				
		this->cubePtr.position[0] -= MOVE_VAR;				// X -
	}
	else if (this->cubePtr.position[0] < (AREA_SIZE - (DIST_CUBE_CAM)) && _IsKeyDown &&
		((_Key == this->D_KEY && cubePtr.position[2] > cameraPosition[2]) || (_Key == this->A_KEY && cubePtr.position[2] < cameraPosition[2])))
	{
		this->cameraPosition[0] += MOVE_VAR; 
		this->cubePtr.position[0] += MOVE_VAR;				// X +
	}
	else if (this->cubePtr.position[2] > DIST_CUBE_CAM && _IsKeyDown &&
		((_Key == this->D_KEY && cubePtr.position[0] > cameraPosition[0]) || (_Key == this->A_KEY && cubePtr.position[0] < cameraPosition[0])))
	{
		this->cameraPosition[2] -= MOVE_VAR; 
		this->cubePtr.position[2] -= MOVE_VAR;				// Z -
	}
	else if (this->cubePtr.position[2] < AREA_SIZE - DIST_CUBE_CAM && _IsKeyDown &&
		((_Key == this->A_KEY && cubePtr.position[0] > cameraPosition[0]) || (_Key == this->D_KEY && cubePtr.position[0] < cameraPosition[0])))
	{
		this->cameraPosition[2] += MOVE_VAR; 
		this->cubePtr.position[2] += MOVE_VAR;				// Z +
	};

	/*
		key-events for forward / backward movement
	*/
	if (this->cubePtr.position[2] < (AREA_SIZE - DIST_CUBE_CAM) && _IsKeyDown &&
		((_Key == this->W_KEY && cubePtr.position[2] > cameraPosition[2]) || (_Key == this->S_KEY && cubePtr.position[2] < cameraPosition[2])))
	{
		this->cameraPosition[2] += MOVE_VAR;
		this->cubePtr.position[2] += MOVE_VAR;				// Z +
	}
	else if (this->cubePtr.position[2] > DIST_CUBE_CAM && _IsKeyDown &&
		((_Key == this->W_KEY && cubePtr.position[2] < cameraPosition[2]) || (_Key == this->S_KEY && cubePtr.position[2] > cameraPosition[2])))
	{
		this->cameraPosition[2] -= MOVE_VAR;
		this->cubePtr.position[2] -= MOVE_VAR;				// Z -
	}
	else if (this->cubePtr.position[0] < (AREA_SIZE - DIST_CUBE_CAM) && _IsKeyDown &&
		((_Key == this->W_KEY && cubePtr.position[0] > cameraPosition[0]) || (_Key == this->S_KEY && cubePtr.position[0] < cameraPosition[0])))
	{
		this->cameraPosition[0] += MOVE_VAR;
		this->cubePtr.position[0] += MOVE_VAR;				// X +
	}
	else if (this->cubePtr.position[0] > DIST_CUBE_CAM && _IsKeyDown &&
		((_Key == this->W_KEY && cubePtr.position[0] < cameraPosition[0]) || (_Key == this->S_KEY && cubePtr.position[0] > cameraPosition[0])))
	{
		this->cameraPosition[0] -= MOVE_VAR;
		this->cubePtr.position[0] -= MOVE_VAR;				// X -
	};
	
	/*
		source rotation formula:
		https://prlbr.de/2018/dreieck-eckpunkte-koordinaten-berechnen/
	if (_Key == this->LEFT_KEY && _IsKeyDown) {
		this->cubePtr.rotation[1] -= ROT_VAR;		// change rotation value
		EditXZVectors(ROT_VAR);
		std::cout << "cube position x before: " << this->cubePtr.position[0] << std::endl;
		std::cout << "cube position Z before: " << this->cubePtr.position[2] << std::endl;
		this->cubePtr.position[0] = rotationVectors.zVector[0];
		this->cubePtr.position[2] = rotationVectors.zVector[2];
		std::cout << "cube position x after: " << this->cubePtr.position[0] << std::endl;
		std::cout << "cube position Z after: " << this->cubePtr.position[2] << std::endl;
		std::cout << std::endl;
		/*
		GetRotationYMatrix(ROT_VAR, perspectiveMatrix);
		MulMatrix(cubePtr.worldMatrix, perspectiveMatrix, cubePtr.worldMatrix);
		
		float a = sqrt(2 * pow(DIST_CUBE_CAM, 2) - 2 * DIST_CUBE_CAM * DIST_CUBE_CAM * cos(ROT_VAR));
		float coordX = (2 * pow(DIST_CUBE_CAM, 2) - pow(a, 2)) / (2 * DIST_CUBE_CAM);
		std::cout << "coordX is: " << coordX << std::endl;
		float coordZ = sqrt(pow(DIST_CUBE_CAM, 2) - pow(coordX, 2));
		std::cout << "coordZ is: " << coordZ << std::endl;
		std::cout << "cube position x before: " << this->cubePtr.position[0] << std::endl;
		std::cout << "cube position Z before: " << this->cubePtr.position[2] << std::endl;
		this->cubePtr.position[0] += coordX;
		this->cubePtr.position[2] += coordZ;
		std::cout << "cube position x after: " << this->cubePtr.position[0] << std::endl;
		std::cout << "cube position Z after: " << this->cubePtr.position[2] << std::endl;
		
		this->cameraTarget[0] = this->cubePtr.position[0];
		this->cameraTarget[2] = this->cubePtr.position[2];
	
	
	else if	(_Key == this->RIGHT_KEY && _IsKeyDown) {
		// edit 
		float a = sqrt(2 * pow(DIST_CUBE_CAM, 2) - 2 * DIST_CUBE_CAM * DIST_CUBE_CAM * -cos(ROT_VAR));
		float coordX = (2 * pow(DIST_CUBE_CAM, 2) - pow(a, 2)) / (2 * DIST_CUBE_CAM);
		std::cout << "coordX is: " << coordX << std::endl;
		float coordZ = sqrt(pow(DIST_CUBE_CAM, 2) - pow(coordX, 2));
		std::cout << "coordZ is: " << coordZ << std::endl;
		std::cout << "cube position x before: " << this->cubePtr.position[0] << std::endl;
		std::cout << "cube position Z before: " << this->cubePtr.position[2] << std::endl;
		this->cubePtr.position[0] += coordX;
		this->cubePtr.position[2] += coordZ;
		std::cout << "cube position x after: " << this->cubePtr.position[0] << std::endl;
		std::cout << "cube position Z after: " << this->cubePtr.position[2] << std::endl;
		
		this->cameraTarget[0] = this->cubePtr.position[0];
		this->cameraTarget[2] = this->cubePtr.position[2];
	}*/

	/*
		key events for 90° rotation
	*/
	if (_Key == this->RIGHT_KEY && _IsKeyDown && cubePtr.position[2] > cameraPosition[2]
		|| _Key == this->LEFT_KEY && _IsKeyDown && cubePtr.position[2] < cameraPosition[2])
	{
		this->cameraPosition[0] = cubePtr.position[0] + DIST_CUBE_CAM;
		this->cameraPosition[2] = cubePtr.position[2];
	}
	else if (_Key == this->LEFT_KEY && _IsKeyDown && cubePtr.position[2] > cameraPosition[2]
		|| _Key == this->RIGHT_KEY && _IsKeyDown && cubePtr.position[2] < cameraPosition[2])
	{
		this->cameraPosition[0] = cubePtr.position[0] - DIST_CUBE_CAM;
		this->cameraPosition[2] = cubePtr.position[2];
	}
	else if (_Key == this->LEFT_KEY && _IsKeyDown && cubePtr.position[0] > cameraPosition[0]
		|| _Key == this->RIGHT_KEY && _IsKeyDown && cubePtr.position[0] < cameraPosition[0])
	{
		this->cameraPosition[0] = cubePtr.position[0];
		this->cameraPosition[2] = cubePtr.position[2] + DIST_CUBE_CAM;
	}
	else if (_Key == this->RIGHT_KEY && _IsKeyDown && cubePtr.position[0] > cameraPosition[0]
		|| _Key == this->LEFT_KEY && _IsKeyDown && cubePtr.position[0] < cameraPosition[0])
	{
		this->cameraPosition[0] = cubePtr.position[0];
		this->cameraPosition[2] = cubePtr.position[2] - DIST_CUBE_CAM;
	};

	/*
		key events to move the cube up and down 
	*/
	if (_Key == this->UP_KEY && _IsKeyDown && this->cubePtr.position[1] < (5 * CUBE_MAX_SCALE))
	{
		this->cubePtr.position[1] += MOVE_VAR;
	}
	else if (_Key == this->DOWN_KEY && _IsKeyDown && this->cubePtr.position[1] > (this->cubePtr.scale[1] / 2))
	{
		this->cubePtr.position[1] -= MOVE_VAR;
	};

	/*
		key-events for cube scaling
	*/
	if (_Key == this->PLUS_KEY && _IsKeyDown && this->cubePtr.scale[0] < CUBE_MAX_SCALE)
	{
		if (this->cubePtr.position[1] < (this->cubePtr.scale[0] / 2))
		{
			this->cubePtr.position[1] += MOVE_VAR;
		}
		this->cubePtr.scale[0] += SCALE_VAR;
		this->cubePtr.scale[1] += SCALE_VAR;
		this->cubePtr.scale[2] += SCALE_VAR;
	}
	else if (_Key == this->MINUS_KEY && _IsKeyDown && this->cubePtr.scale[0] > CUBE_MIN_SCALE)
	{
		this->cubePtr.scale[0] -= SCALE_VAR;
		this->cubePtr.scale[1] -= SCALE_VAR;
		this->cubePtr.scale[2] -= SCALE_VAR;
	};

	// adjust movement steps
	MOVE_VAR = this->cubePtr.scale[0] / 2;

	/*
		key-events for views
	*/
	// reset to start view
	if (_Key == this->ESC_KEY && _IsKeyDown)
	{
		this->cubePtr.position[0] = AREA_SIZE / 2;
		this->cubePtr.position[1] = CUBE_MAX_SCALE / 2;
		this->cubePtr.position[2] = AREA_SIZE / 2;

		this->cameraPosition[0] = this->cubePtr.position[0];
		this->cameraPosition[2] = this->cubePtr.position[2] - DIST_CUBE_CAM;
	}
	// view from left side
	else if (_Key == this->N1_KEY && _IsKeyDown)
	{
		this->cameraPosition[0] = 0.0f;
		this->cameraPosition[2] = AREA_SIZE / 2;

		this->cubePtr.position[0] = this->cameraPosition[0] + DIST_CUBE_CAM;
		this->cubePtr.position[1] = CUBE_MAX_SCALE / 2;
		this->cubePtr.position[2] = this->cameraPosition[2];
	}
	// view from back side
	else if (_Key == this->N2_KEY && _IsKeyDown)
	{
		this->cameraPosition[0] = AREA_SIZE / 2;
		this->cameraPosition[2] = AREA_SIZE;

		this->cubePtr.position[0] = this->cameraPosition[0];
		this->cubePtr.position[1] = CUBE_MAX_SCALE / 2;
		this->cubePtr.position[2] = this->cameraPosition[2] - DIST_CUBE_CAM;
	}
	// view from right side
	else if (_Key == this->N3_KEY && _IsKeyDown)
	{
		this->cameraPosition[0] = AREA_SIZE;
		this->cameraPosition[2] = AREA_SIZE / 2;

		this->cubePtr.position[0] = this->cameraPosition[0] - DIST_CUBE_CAM;
		this->cubePtr.position[1] = CUBE_MAX_SCALE / 2;
		this->cubePtr.position[2] = this->cameraPosition[2];
	}
	// view from front side
	else if (_Key == this->N4_KEY && _IsKeyDown)
	{
		this->cameraPosition[0] = AREA_SIZE / 2;
		this->cameraPosition[2] = 0.0f;

		this->cubePtr.position[0] = this->cameraPosition[0];
		this->cubePtr.position[1] = CUBE_MAX_SCALE / 2;
		this->cubePtr.position[2] = this->cameraPosition[2] + DIST_CUBE_CAM;
	};

	/*
		camera always targeting the cube
	*/
	this->cameraTarget[0] = this->cubePtr.position[0];
	this->cameraTarget[1] = this->cubePtr.position[1];
	this->cameraTarget[2] = this->cubePtr.position[2];

	return false;
}

// -----------------------------------------------------------------------------

bool CApplication::InternOnMouseEvent(int _X, int _Y, int _Button, bool _IsButtonDown, bool _IsDoubleClick, int _WheelDelta)
{
	if (_WheelDelta == this->WHEEL_UP)
	{
		if (this->colorsIterator < (amountColors - 1))
		{
			this->colorsIterator++;
		}
		else
		{
			this->colorsIterator = 0;
		};
	}
	else if (_WheelDelta == this->WHEEL_DOWN)
	{
		if (this->colorsIterator > 0)
		{
			this->colorsIterator--;
		}
		else
		{
			this->colorsIterator = amountColors - 1;
		};
	};

	// giving cube different color-mesh
	this->cubePtr.mesh = &this->cubeMeshes[colorsIterator];

	return false;
}

