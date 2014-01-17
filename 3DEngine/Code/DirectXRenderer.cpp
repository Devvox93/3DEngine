#include "DirectXRenderer.h"
#include "Logger.h"
#include <ctime>
#include <sstream>
#include "InputManager.h"
#include "Model.h"
#include "Defines.h"

#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ | D3DFVF_TEX1)

DirectXRenderer::DirectXRenderer()
{
	g_pD3D = NULL;
	g_pd3dDevice = NULL;
};

DirectXRenderer::~DirectXRenderer()
{
	Cleanup();
};

void DirectXRenderer::setActiveCamera(Camera* camera)
{
	activeCamera = camera;
}

void DirectXRenderer::setRenderSize(int width, int height)
{
	setMyRenderSize(width, height, true);
}

D3DPRESENT_PARAMETERS DirectXRenderer::setMyRenderSize(int width, int height, bool activate)
{
	// Set up the structure used to create the D3DDevice. Since we are now
	// using more complex geometry, we will create a device with a zbuffer.
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	d3dpp.Windowed = true;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
	d3dpp.EnableAutoDepthStencil = true;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	d3dpp.BackBufferWidth = width;
	d3dpp.BackBufferHeight = height;
	d3dpp.MultiSampleType = D3DMULTISAMPLE_4_SAMPLES;//anti-aliasing

	if (activate)
	{
		g_pd3dDevice->Reset(&d3dpp);
		// For the projection matrix, we set up a perspective transform (which
		// transforms geometry from 3D view space to 2D viewport space, with
		// a perspective divide making objects smaller in the distance). To build
		// a perpsective transform, we need the field of view (1/4 pi is common),
		// the aspect ratio, and the near and far clipping planes (which define at
		// what distances geometry should be no longer be rendered).
		D3DXMATRIXA16 matProj;
		D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, (float)width / (float)height, 0.1f, 1000.0f);
		g_pd3dDevice->SetTransform(D3DTS_PROJECTION, &matProj);

		// Turn off culling
		g_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

		// Turn on ambient lighting 
		g_pd3dDevice->SetRenderState(D3DRS_AMBIENT, 0xffffffff);

		g_pd3dDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR); // minification
		g_pd3dDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR); // magnification
		g_pd3dDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR); // mipmapping
	}
	return d3dpp;
}

void DirectXRenderer::Initialize(int width, int height)
{
	DirectXWindow *window = new DirectXWindow();
	HWND hWnd = window->Create(10, 10, width, height, NULL, NULL, NULL);

	if (g_pd3dDevice == NULL && SUCCEEDED(InitD3D(hWnd, width, height)))
	{

	}
};

//-----------------------------------------------------------------------------
// Name: InitD3D()
// Desc: Initializes Direct3D
//-----------------------------------------------------------------------------
HRESULT DirectXRenderer::InitD3D(HWND hWnd, int width, int height)
{
	// Create the D3D object.
	if (NULL == (g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
	{
		return E_FAIL;
	}

	// Create the D3DDevice
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&setMyRenderSize(width, height, false), &g_pd3dDevice)))
	{
		return E_FAIL;
	}
	// Set up our view matrix. A view matrix can be defined given an eye point,
	// a point to lookat, and a direction for which way is up. Here, we set the
	// eye five units back along the z-axis and up three units, look at the 
	// origin, and define "up" to be in the y-direction.
	D3DXVECTOR3 vEyePt(0, 0, -0.5f);
	D3DXVECTOR3 vLookatPt(0, 0, 0.5f);
	D3DXVECTOR3 vUpVec(0.0f, 0.5f, 0.0f);
	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH(&matView, &vEyePt, &vLookatPt, &vUpVec);
	g_pd3dDevice->SetTransform(D3DTS_VIEW, &matView);
	setMyRenderSize(width, height, true);
	return S_OK;
};

void DirectXRenderer::initTerrain(Terrain *terrain)
{
	g_pd3dDevice->CreateVertexBuffer(terrain->data->width * terrain->data->height * sizeof(Vertex), D3DUSAGE_WRITEONLY, D3DFVF_CUSTOMVERTEX, D3DPOOL_MANAGED, &g_pTerrainVertexBuffer, NULL);
	g_pd3dDevice->CreateIndexBuffer(terrain->amountOfIndices * sizeof(int), D3DUSAGE_WRITEONLY, D3DFMT_INDEX32, D3DPOOL_MANAGED, &g_pTerrainIndexBuffer, NULL);

	VOID* pVertices;
	g_pTerrainVertexBuffer->Lock(0, terrain->data->width * terrain->data->height * sizeof(Vertex), (void**)&pVertices, 0);   //lock buffer
	memcpy(pVertices, terrain->aTerrainVertices, terrain->data->width * terrain->data->height * sizeof(Vertex)); //copy data
	g_pTerrainVertexBuffer->Unlock();                                 //unlock buffer

	terrainVertexBuffers[terrain] = &g_pTerrainVertexBuffer;

	g_pTerrainIndexBuffer->Lock(0, terrain->amountOfIndices * sizeof(int), (void**)&pVertices, 0);   //lock buffer
	memcpy(pVertices, terrain->aTerrainIndices, terrain->amountOfIndices * sizeof(int));   //copy data
	g_pTerrainIndexBuffer->Unlock();                                 //unlock buffer

	terrainIndexBuffers[terrain] = &g_pTerrainIndexBuffer;
};

void DirectXRenderer::initSkybox(Skybox* skybox)
{
	g_pd3dDevice->CreateVertexBuffer(24 * sizeof(Vertex), D3DUSAGE_WRITEONLY, D3DFVF_CUSTOMVERTEX, D3DPOOL_MANAGED, &g_pSkyboxVertexBuffer, NULL);
	g_pd3dDevice->CreateIndexBuffer(36 * sizeof(int), D3DUSAGE_WRITEONLY, D3DFMT_INDEX32, D3DPOOL_MANAGED, &g_pSkyboxIndexBuffer, NULL);

	VOID* pVertices;
	g_pSkyboxVertexBuffer->Lock(0, 24 * sizeof(Vertex), (void**)&pVertices, 0);   //lock buffer
	memcpy(pVertices, skybox->aSkyboxVertices, 24 * sizeof(Vertex)); //copy data
	g_pSkyboxVertexBuffer->Unlock();                                 //unlock buffer

	skyboxVertexBuffers[skybox] = &g_pSkyboxVertexBuffer;

	g_pSkyboxIndexBuffer->Lock(0, 36 * sizeof(int), (void**)&pVertices, 0);   //lock buffer
	memcpy(pVertices, skybox->aSkyboxIndices, 36 * sizeof(int));   //copy data
	g_pSkyboxIndexBuffer->Unlock();                                 //unlock buffer

	skyboxIndexBuffers[skybox] = &g_pSkyboxIndexBuffer;
};

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
// Name: Render()
// Desc: Draws the scene
//-----------------------------------------------------------------------------
void DirectXRenderer::Render(HWND hwnd, Scene* scene)
{
	activeCamera->update();//DIT MOET IN SCENE GEBEUREN!
	// Clear the backbuffer and the zbuffer
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 127, 0), 1.0f, 0);

	// Begin the scene
	if (SUCCEEDED(g_pd3dDevice->BeginScene()))
	{
		D3DMATERIAL9 material = D3DMATERIAL9();
		material.Ambient = D3DCOLORVALUE();
		material.Ambient.a = 1.0f;
		material.Ambient.r = 1.0f;
		material.Ambient.g = 1.0f;
		material.Ambient.b = 1.0f;
		g_pd3dDevice->SetMaterial(&material);

		g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
		D3DXMATRIXA16 matWorldFinal;
		D3DXMatrixTranslation(&matWorldFinal, 0.0f, 0.0f, 0.0f);
		D3DXMatrixMultiply(&matWorldFinal, &matWorldFinal, &activeCamera->rotationMatrix);
		Skybox *skybox = scene->getSkybox();
		g_pd3dDevice->SetTransform(D3DTS_WORLD, &matWorldFinal);
		g_pd3dDevice->SetTexture(0, skybox->texture->texture);
		g_pd3dDevice->SetStreamSource(0, *skyboxVertexBuffers[skybox], 0, sizeof(Vertex));
		g_pd3dDevice->SetFVF(D3DFVF_CUSTOMVERTEX);
		g_pd3dDevice->SetIndices(*skyboxIndexBuffers[skybox]);
		g_pd3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 24, 0, 12);
		g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

		D3DXMATRIXA16 matWorldScaled;
		D3DXMatrixScaling(&matWorldScaled, 1.0f, 250.0f, 1.0f);
		D3DXMatrixMultiply(&matWorldFinal, &matWorldScaled, &activeCamera->finalMatrix);
		g_pd3dDevice->SetTransform(D3DTS_WORLD, &matWorldFinal);
		Terrain *terrain = scene->getTerrain();
		g_pd3dDevice->SetTexture(0, terrain->texture->texture);
		g_pd3dDevice->SetStreamSource(0, *terrainVertexBuffers[terrain], 0, sizeof(Vertex));
		g_pd3dDevice->SetFVF(D3DFVF_CUSTOMVERTEX);
		g_pd3dDevice->SetIndices(*terrainIndexBuffers[terrain]);
		g_pd3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, terrain->data->width * terrain->data->height, 0, (terrain->data->width - 1) * (terrain->data->height - 1) * 2);
		
		std::vector<Entity*> entities = scene->getEntities();
		for each(Entity *currentEntity in entities)
		{
			D3DXMATRIXA16 matWorldFinal;
			D3DXMatrixMultiply(&matWorldFinal, &currentEntity->finalMatrix, &activeCamera->finalMatrix);
			g_pd3dDevice->SetTransform(D3DTS_WORLD, &matWorldFinal);

			Model *lol = (Model*)currentEntity;
			// Meshes are divided into subsets, one for each material. Render them in a loop
			for (DWORD i = 0; i < lol->model->g_dwNumMaterials; i++)
			{
				// Set the material and texture for this subset
				g_pd3dDevice->SetMaterial(&lol->model->g_pMeshMaterials[i]);
				if (lol->model->myTextures[i])
				{
					g_pd3dDevice->SetTexture(0, lol->model->myTextures[i]->texture);
				}
				else
				{
					g_pd3dDevice->SetTexture(0, NULL);
				}

				// Draw the mesh subset
				lol->model->g_pMesh->DrawSubset(i);
			}
		}
		// End the scene
		g_pd3dDevice->EndScene();
	}

	// Present the backbuffer contents to the display
	g_pd3dDevice->Present(NULL, NULL, hwnd, NULL);
}