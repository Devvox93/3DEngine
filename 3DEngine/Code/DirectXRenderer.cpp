#include "DirectXRenderer.h"
#include "Logger.h"
#include <ctime>
#include <sstream>
#include "InputManager.h"

#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ | D3DFVF_TEX1)
struct D3DVERTEX
{
	float x,
	y,
	z,
	u,//texture x
	v;//texture y
};

DirectXRenderer::DirectXRenderer()
{
	g_pD3D = NULL;
	g_pd3dDevice = NULL;

	g_pMesh = NULL; // Our mesh object in sysmem
	g_pMeshMaterials = NULL; // Materials for our mesh
	g_pMeshTextures = NULL; // Textures for our mesh
	g_dwNumMaterials = 0L;   // Number of mesh materials
	camX = 0.0f;
	camY = 0.0f;
	camZ = -5.0f;
};


DirectXRenderer::~DirectXRenderer()
{
	Cleanup();
};

void DirectXRenderer::Initialize(HWND hWnd)
{
	if (g_pd3dDevice == NULL && SUCCEEDED(InitD3D(hWnd)))
	{
		InitGeometry("car.X");
		initHeightmap();
		//SetupMatrices();
	}
};

void DirectXRenderer::useKeyboardInput(std::array<unsigned char, 256> keyboardState)
{
	Logger::getInstance().log(INFO, "DirectXInput gebruikt ofzo");

	if (keyboardState[DIK_UPARROW] & 0x80)
	{
		Logger::getInstance().log(INFO, "Up arrow");
		up = true;

	}
	else
	{
		up = false;
	}
	if (keyboardState[DIK_DOWNARROW] & 0x80)
	{
		Logger::getInstance().log(INFO, "Down arrow");
		down = true;
	}
	else
	{
		down = false;
	}
	if (keyboardState[DIK_LEFTARROW] & 0x80)
	{
		Logger::getInstance().log(INFO, "Left arrow");

		left = true;
	}
	else
	{
		left = false;
	}
	if (keyboardState[DIK_RIGHTARROW] & 0x80)
	{
		Logger::getInstance().log(INFO, "Right arrow");
		right = true;
	}
	else
	{
		right = false;
	}

	if (keyboardState[DIK_PGUP] & 0x80)
	{
		Logger::getInstance().log(INFO, "Page up");
		forward = true;
	}
	else
	{
		forward = false;
	}

	if (keyboardState[DIK_PGDN] & 0x80)
	{
		Logger::getInstance().log(INFO, "Page down");
		back = true;
	}
	else
	{
		back = false;
	}
}

void DirectXRenderer::initHeightmap()
{
	std::string yolo = std::string("test.bmp");
	std::string stemp = std::string(yolo.begin(), yolo.end());
	LPCSTR sw = stemp.c_str();
	// Use D3DX to create a texture from a file based image
	if (FAILED(D3DXCreateTextureFromFile(g_pd3dDevice, sw, &hmrTexture)))
	{
		Logger::getInstance().log(INFO, "well shit!");
	}


	hmr = new HeightmapResource("test.bmp");
	D3DVERTEX* heightmapVertices = new D3DVERTEX[hmr->data->width * hmr->data->height];
	for (int i = 0; i < hmr->data->height; i++)
	{
		for (int j = 0; j < hmr->data->width; j++)
		{
			heightmapVertices[(i*hmr->data->width) + j] = { (float)j, ((float)hmr->data->pixelData[(i*hmr->data->width) + j] / 255.0f), (float)i, (1.0f / (hmr->data->width - 1)) * j, (1.0f / (hmr->data->height - 1)) * i };
			/*std::stringstream ss;
			ss << "x: " << heightmapVertices[(i*hmr->data->width) + j].x 
				<< " y: " << heightmapVertices[(i*hmr->data->width) + j].y 
				<< " z: " << heightmapVertices[(i*hmr->data->width) + j].z 
				<< " u: " << heightmapVertices[(i*hmr->data->width) + j].u 
				<< " v: " << heightmapVertices[(i*hmr->data->width) + j].v;
			Logger::getInstance().log(INFO, ss.str());*/
		}
	}
	
	int amountOfIndices = (hmr->data->width - 1) * (hmr->data->height - 1) * 2 * 3;
	int* aCubeIndices = new int[amountOfIndices];

	std::stringstream ss2;
	ss2 << "amount of planes: " << amountOfIndices / 3;
	Logger::getInstance().log(INFO, ss2.str());

	int offset = 0;
	for (int i = 0; i < amountOfIndices; i+=6)
	{
		if (i != 0 && (i - 0) % ((hmr->data->width - 1) * 6) == 0)
		{
			/*std::stringstream ss;
			ss << "end!: " << i;
			Logger::getInstance().log(INFO, ss.str());*/
			offset+=1;
		}
		aCubeIndices[i + 0] = i / 6 + offset;
		aCubeIndices[i + 1] = i / 6 + 1 + offset;
		aCubeIndices[i + 2] = i / 6 + hmr->data->width + offset;
		aCubeIndices[i + 3] = i / 6 + 1 + offset;
		aCubeIndices[i + 4] = i / 6 + hmr->data->width + offset;
		aCubeIndices[i + 5] = i / 6 + hmr->data->width + 1 + offset;
	}

	/*for (int i = 0; i < amountOfIndices; i ++)
	{
		std::stringstream ss;
		ss << "yolos: " << aCubeIndices[i];
		if ((i+1) % 6 == 0)
		{
			ss << std::endl;
		}
		
		Logger::getInstance().log(INFO, ss.str());
	}*/

	/*std::stringstream ss;
	ss << "sizeof: " << sizeof(heightmapVertices) << ", mewo: " << sizeof(D3DVERTEX) << " beep: " << (hmr->data->width - 1) * (hmr->data->height - 1) * 2;
	Logger::getInstance().log(INFO, ss.str());*/

	g_pd3dDevice->CreateVertexBuffer(hmr->data->width * hmr->data->height * sizeof(D3DVERTEX),
		D3DUSAGE_WRITEONLY,
		D3DFVF_CUSTOMVERTEX,
		D3DPOOL_MANAGED,
		&g_pHeightmapVertexBuffer,
		NULL);
	g_pd3dDevice->CreateIndexBuffer(amountOfIndices * sizeof(int),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX32,
		D3DPOOL_MANAGED,
		&g_pHeightmapIndexBuffer,
		NULL);

	VOID* pVertices;
	g_pHeightmapVertexBuffer->Lock(0, hmr->data->width * hmr->data->height * sizeof(D3DVERTEX), (void**)&pVertices, 0);   //lock buffer
	memcpy(pVertices, heightmapVertices, hmr->data->width * hmr->data->height * sizeof(D3DVERTEX)); //copy data
	g_pHeightmapVertexBuffer->Unlock();                                 //unlock buffer

	g_pHeightmapIndexBuffer->Lock(0, amountOfIndices * sizeof(int), (void**)&pVertices, 0);   //lock buffer
	memcpy(pVertices, aCubeIndices, amountOfIndices * sizeof(int));   //copy data
	g_pHeightmapIndexBuffer->Unlock();                                 //unlock buffer
}

//-----------------------------------------------------------------------------
// Name: InitD3D()
// Desc: Initializes Direct3D
//-----------------------------------------------------------------------------
HRESULT DirectXRenderer::InitD3D(HWND hWnd)
{
	// Create the D3D object.
	if (NULL == (g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
	{
		return E_FAIL;
	}

	// Set up the structure used to create the D3DDevice. Since we are now
	// using more complex geometry, we will create a device with a zbuffer.
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

	// Create the D3DDevice
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp, &g_pd3dDevice)))
	{
		return E_FAIL;
	}

	// Turn off culling, so we see the front and back of the triangle
	g_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	// Turn on the zbuffer
	g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

	// Turn on ambient lighting 
	g_pd3dDevice->SetRenderState(D3DRS_AMBIENT, 0xffffffff);

	return S_OK;
}

HRESULT DirectXRenderer::InitGeometry(std::string filename)
{
	LPD3DXBUFFER pD3DXMtrlBuffer;

	std::string stemp = std::string(filename.begin(), filename.end());
	LPCSTR sw = stemp.c_str();

	// Load the mesh from the specified file
	if (FAILED(D3DXLoadMeshFromX(sw, D3DXMESH_SYSTEMMEM,
		g_pd3dDevice, NULL,
		&pD3DXMtrlBuffer, NULL, &g_dwNumMaterials,
		&g_pMesh)))
	{
		// If model is not in current folder, try parent folder
		if (FAILED(D3DXLoadMeshFromX(sw, D3DXMESH_SYSTEMMEM,
			g_pd3dDevice, NULL,
			&pD3DXMtrlBuffer, NULL, &g_dwNumMaterials,
			&g_pMesh)))
		{
			Logger::getInstance().log(WARNING, "Could not find file: " + filename);
			return E_FAIL;
		}
	}

	// We need to extract the material properties and texture names from the 
	// pD3DXMtrlBuffer
	D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();
	g_pMeshMaterials = new D3DMATERIAL9[g_dwNumMaterials];
	if (g_pMeshMaterials == NULL)
	{
		return E_OUTOFMEMORY;
	}
	g_pMeshTextures = new LPDIRECT3DTEXTURE9[g_dwNumMaterials];
	if (g_pMeshTextures == NULL)
	{
		return E_OUTOFMEMORY;
	}

	for (DWORD i = 0; i < g_dwNumMaterials; i++)
	{
		// Copy the material
		g_pMeshMaterials[i] = d3dxMaterials[i].MatD3D;

		// Set the ambient color for the material (D3DX does not do this)
		g_pMeshMaterials[i].Ambient = g_pMeshMaterials[i].Diffuse;

		g_pMeshTextures[i] = NULL;
		if (d3dxMaterials[i].pTextureFilename != NULL &&
			lstrlenA(d3dxMaterials[i].pTextureFilename) > 0)
		{
			// Create the texture
			if (FAILED(D3DXCreateTextureFromFileA(g_pd3dDevice,
				d3dxMaterials[i].pTextureFilename,
				&g_pMeshTextures[i])))
			{
				// If texture is not in current folder, try parent folder
				const CHAR* strPrefix = "..\\";
				CHAR strTexture[MAX_PATH];
				strcpy_s(strTexture, MAX_PATH, strPrefix);
				strcat_s(strTexture, MAX_PATH, d3dxMaterials[i].pTextureFilename);
				// If texture is not in current folder, try parent folder
				if (FAILED(D3DXCreateTextureFromFileA(g_pd3dDevice,
					strTexture,
					&g_pMeshTextures[i])))
				{
					std::string lol = std::string(strTexture);
					Logger::getInstance().log(WARNING, "Could not find texture: " + lol);
				}
			}
		}
	}

	// Done with the material buffer
	pD3DXMtrlBuffer->Release();

	return S_OK;
}

//-----------------------------------------------------------------------------
// Name: Cleanup()
// Desc: Releases all previously initialized objects
//-----------------------------------------------------------------------------
void DirectXRenderer::Cleanup()
{
	if (g_pd3dDevice != NULL)
	{
		g_pd3dDevice->Release();
	}

	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
	}
}

//-----------------------------------------------------------------------------
// Name: SetupMatrices()
// Desc: Sets up the world, view, and projection transform matrices.
//-----------------------------------------------------------------------------
void DirectXRenderer::SetupMatrices()
{
	// Set up world matrix
	D3DXMATRIXA16 matWorld;
	//D3DXMatrixRotationY(&matWorld, timeGetTime() / 1000.0f);

	//g_pd3dDevice->SetTransform(D3DTS_WORLD, &matWorld);

	// Set up our view matrix. A view matrix can be defined given an eye point,
	// a point to lookat, and a direction for which way is up. Here, we set the
	// eye five units back along the z-axis and up three units, look at the 
	// origin, and define "up" to be in the y-direction.

	if (up)
	{
		camY += 0.1f;
	}
	if (down)
	{
		camY -= 0.1f;
	}
	if (right)
	{
		camX += 0.1f;
	}
	if (left)
	{
		camX -= 0.1f;
	}

	if (forward)
	{
		camZ += 0.1f;
	}
	if (back)
	{
		camZ -= 0.1f;
	}

	D3DXVECTOR3 vEyePt(camX, camY, camZ);
	D3DXVECTOR3 vLookatPt(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);
	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH(&matView, &vEyePt, &vLookatPt, &vUpVec);
	g_pd3dDevice->SetTransform(D3DTS_VIEW, &matView);

	// For the projection matrix, we set up a perspective transform (which
	// transforms geometry from 3D view space to 2D viewport space, with
	// a perspective divide making objects smaller in the distance). To build
	// a perpsective transform, we need the field of view (1/4 pi is common),
	// the aspect ratio, and the near and far clipping planes (which define at
	// what distances geometry should be no longer be rendered).
	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, 1.0f, 1.0f, 100.0f);
	g_pd3dDevice->SetTransform(D3DTS_PROJECTION, &matProj);
}

void DirectXRenderer::WorldMatrix(int type)
{
	// For our world matrix, we will just rotate the object about the y-axis.
	D3DXMATRIXA16 matWorldFinal;
	D3DXMATRIXA16 matWorldScaled;
	D3DXMATRIXA16 matWorldTranslate;

	// Set up the rotation matrix to generate 1 full rotation (2*PI radians) 
	// every 1000 ms. To avoid the loss of precision inherent in very high 
	// floating point numbers, the system time is modulated by the rotation 
	// period before conversion to a radian angle.
	UINT iTime = timeGetTime() / 10;
	FLOAT fAngle = iTime * (2.0f * D3DX_PI) / 1000.0f;

	if (type==0)
	{
		D3DXMatrixRotationYawPitchRoll(&matWorldFinal, 0, 0, 0);
		D3DXMatrixTranslation(&matWorldTranslate, 1.0f, 0.0f, 0.0f);
		D3DXMatrixScaling(&matWorldScaled, 0.015f, 0.015f, 0.015f);
	}
	else if (type==1)
	{
		D3DXMatrixRotationYawPitchRoll(&matWorldFinal, -0, -0, -0);
		D3DXMatrixTranslation(&matWorldTranslate, -1.0f, 0.0f, 0.0f);
		//D3DXMatrixScaling(&matWorldScaled, 0.03f, 0.03f, 0.03f);
		D3DXMatrixScaling(&matWorldScaled, 0.015f, 0.015f, 0.015f);
	}
	else
	{
		D3DXMatrixRotationYawPitchRoll(&matWorldFinal, 0.0f, -45.0f, 0.0f);
		D3DXMatrixTranslation(&matWorldTranslate, -2.5f, -2.0f, 1.0f);
		D3DXMatrixScaling(&matWorldScaled, 0.0125f, 1.0f, 0.0125f);
		/*std::stringstream ss;
		ss << "angle; " << fAngle;
		Logger::getInstance().log(INFO, ss.str());*/
	}

	D3DXMatrixMultiply(&matWorldFinal, &matWorldFinal, &matWorldTranslate);
	D3DXMatrixMultiply(&matWorldFinal, &matWorldScaled, &matWorldFinal);

	g_pd3dDevice->SetTransform(D3DTS_WORLD, &matWorldFinal);
}

//-----------------------------------------------------------------------------
// Name: Render()
// Desc: Draws the scene
//-----------------------------------------------------------------------------
void DirectXRenderer::Render(HWND hwnd)
{
	// Clear the backbuffer and the zbuffer
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
		D3DCOLOR_XRGB(0, 127, 0), 1.0f, 0);

	// Begin the scene
	if (SUCCEEDED(g_pd3dDevice->BeginScene()))
	{
		// Setup the world, view, and projection matrices
		SetupMatrices();

		WorldMatrix(0);
		// Meshes are divided into subsets, one for each material. Render them in
		// a loop
		for (DWORD i = 0; i < g_dwNumMaterials; i++)
		{
			// Set the material and texture for this subset
			g_pd3dDevice->SetMaterial(&g_pMeshMaterials[i]);
			g_pd3dDevice->SetTexture(0, g_pMeshTextures[i]);

			// Draw the mesh subset
			g_pMesh->DrawSubset(i);
		}

		WorldMatrix(1);
		// Meshes are divided into subsets, one for each material. Render them in
		// a loop
		for (DWORD i = 0; i < g_dwNumMaterials; i++)
		{
			// Set the material and texture for this subset
			g_pd3dDevice->SetMaterial(&g_pMeshMaterials[i]);
			g_pd3dDevice->SetTexture(0, g_pMeshTextures[i]);

			// Draw the mesh subset
			g_pMesh->DrawSubset(i);
		}

		WorldMatrix(2);
		g_pd3dDevice->SetTexture(0, hmrTexture);
		g_pd3dDevice->SetStreamSource(0, g_pHeightmapVertexBuffer, 0, sizeof(D3DVERTEX));
		g_pd3dDevice->SetFVF(D3DFVF_CUSTOMVERTEX);
		g_pd3dDevice->SetIndices(g_pHeightmapIndexBuffer);
		g_pd3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, hmr->data->width * hmr->data->height/*numvertices*/, 0, (hmr->data->width - 1) * (hmr->data->height - 1) * 2/*primitives count*/);

		// End the scene
		g_pd3dDevice->EndScene();
	}

	// Present the backbuffer contents to the display
	g_pd3dDevice->Present(NULL, NULL, hwnd, NULL);
}