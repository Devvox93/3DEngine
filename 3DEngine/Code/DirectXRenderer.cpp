#include "DirectXRenderer.h"
#include "Logger.h"
#include <ctime>
DirectXRenderer::DirectXRenderer()
{
	g_pD3D = NULL;
	g_pd3dDevice = NULL;

	g_pMesh = NULL; // Our mesh object in sysmem
	g_pMeshMaterials = NULL; // Materials for our mesh
	g_pMeshTextures = NULL; // Textures for our mesh
	g_dwNumMaterials = 0L;   // Number of mesh materials
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
		//SetupMatrices();
	}
};



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
	D3DXVECTOR3 vEyePt(0.0f, 3.0f, -5.0f);
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

void DirectXRenderer::WorldMatrix(bool right)
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

	if (right)
	{
		D3DXMatrixRotationYawPitchRoll(&matWorldFinal, fAngle, fAngle, fAngle);
		D3DXMatrixTranslation(&matWorldTranslate, 1.0f, 0.0f, 0.0f);
		D3DXMatrixScaling(&matWorldScaled, 0.015f, 0.015f, 0.015f);
	}
	else
	{
		D3DXMatrixRotationYawPitchRoll(&matWorldFinal, -fAngle, -fAngle, -fAngle);
		D3DXMatrixTranslation(&matWorldTranslate, -1.0f, 0.0f, 0.0f);
		D3DXMatrixScaling(&matWorldScaled, 0.03f, 0.03f, 0.03f);
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

		WorldMatrix(true);
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

		WorldMatrix(false);
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

		// End the scene
		g_pd3dDevice->EndScene();
	}

	// Present the backbuffer contents to the display
	g_pd3dDevice->Present(NULL, NULL, hwnd, NULL);
}