#include "DirectXRenderer.h"
#include "Logger.h"
#include <ctime>
#include <sstream>
#include "InputManager.h"
#include "Model.h"
#include "Defines.h"

DirectXRenderer::DirectXRenderer()
{
	g_pD3D = NULL;
	g_pd3dDevice = NULL;
};

DirectXRenderer::~DirectXRenderer()
{
	Cleanup();
};

LPDIRECT3DDEVICE9 DirectXRenderer::getD3DDevice()
{
	return g_pd3dDevice;
};

void DirectXRenderer::setRenderSize(int width, int height)
{
	setMyRenderSize(width, height, true);
};

D3DPRESENT_PARAMETERS DirectXRenderer::setMyRenderSize(int width, int height, bool activate)
{
	//Set up the structure used to create the D3DDevice. Since we are now
	//using more complex geometry, we will create a device with a zbuffer.
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));//Make sure all the values are emptied, so there's no random results.
	d3dpp.Windowed = true;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;//Render everything, and then throw it away.
	d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;//The higher you can set this, the more accurate the z-buffer is, current seems to be the highest working.
	d3dpp.EnableAutoDepthStencil = true;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;//The higher you can set this, the more accurate the z-buffer is, current seems to be the highest working.
	d3dpp.BackBufferWidth = width;
	d3dpp.BackBufferHeight = height;
	d3dpp.MultiSampleType = D3DMULTISAMPLE_4_SAMPLES;//anti-aliasing

	//We can't activate if the g_pd3dDevice has not yet been initialized, and we use this same function to initialize g_pd3dDevice.
	if (activate)
	{
		g_pd3dDevice->Reset(&d3dpp);
		//For the projection matrix, we set up a perspective transform (which
		//transforms geometry from 3D view space to 2D viewport space, with
		//a perspective divide making objects smaller in the distance). To build
		//a perpsective transform, we need the field of view (1/4 pi is common),
		//the aspect ratio, and the near and far clipping planes (which define at
		//what distances geometry should be no longer be rendered).
		D3DXMATRIXA16 matProj;
		D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, (float)width / (float)height, 0.1f, 1000.0f);
		g_pd3dDevice->SetTransform(D3DTS_PROJECTION, &matProj);

		//Turn off culling
		g_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

		//Turn on ambient lighting 
		g_pd3dDevice->SetRenderState(D3DRS_AMBIENT, 0xffffffff);

		g_pd3dDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR); //minification
		g_pd3dDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR); //magnification
		g_pd3dDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR); //mipmapping
	}
	return d3dpp;
};

void DirectXRenderer::Initialize(int width, int height)
{
	DirectXWindow *window = new DirectXWindow();
	HWND hWnd = window->Create(10, 10, width, height, NULL, NULL, NULL);

	if (g_pd3dDevice == NULL && SUCCEEDED(InitD3D(hWnd, width, height)))
	{
		//We managed to succesfully load.
	}
};

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
	// eye 0.5 units back along the z-axis and up 0 units, look at the 
	// origin + 0.5 on the z-axis, and define "up" to be in the y-direction.
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
	//Create a vertex buffer for the terrain, which is made of a dynamic amount of vertices, depending on it's size.
	g_pd3dDevice->CreateVertexBuffer(terrain->getWidth() * terrain->getHeight() * sizeof(Vertex), D3DUSAGE_WRITEONLY, D3DFVF_CUSTOMVERTEX, D3DPOOL_MANAGED, &g_pTerrainVertexBuffer, NULL);
	//Create an index buffer for the terrain, which is also a dynamic amount, depending on it's size.
	g_pd3dDevice->CreateIndexBuffer(terrain->getAmountOfIndices() * sizeof(int), D3DUSAGE_WRITEONLY, D3DFMT_INDEX32, D3DPOOL_MANAGED, &g_pTerrainIndexBuffer, NULL);

	VOID* pVertices;
	g_pTerrainVertexBuffer->Lock(0, terrain->getWidth() * terrain->getHeight() * sizeof(Vertex), (void**)&pVertices, 0);//lock buffer
	memcpy(pVertices, terrain->getVertices(), terrain->getWidth() * terrain->getHeight() * sizeof(Vertex));//copy data
	g_pTerrainVertexBuffer->Unlock();//unlock buffer

	//Put the g_pTerrainVertexBuffer into the array, we need to do this or we have issues with stack/heap memory allocation.
	terrainVertexBuffers[terrain] = &g_pTerrainVertexBuffer;

	g_pTerrainIndexBuffer->Lock(0, terrain->getAmountOfIndices() * sizeof(int), (void**)&pVertices, 0);//lock buffer
	memcpy(pVertices, terrain->getIndices(), terrain->getAmountOfIndices() * sizeof(int));//copy data
	g_pTerrainIndexBuffer->Unlock();//unlock buffer

	//Put the g_pTerrainIndexBuffer into the array, we need to do this or we have issues with stack/heap memory allocation.
	terrainIndexBuffers[terrain] = &g_pTerrainIndexBuffer;
};

void DirectXRenderer::initSkybox(Skybox* skybox)
{
	//Create a vertex buffer for the skybox, which is always made out of 24 vertices, you can make a cube with 8 but if you want the textures to be correct you need 24.
	g_pd3dDevice->CreateVertexBuffer(24 * sizeof(Vertex), D3DUSAGE_WRITEONLY, D3DFVF_CUSTOMVERTEX, D3DPOOL_MANAGED, &g_pSkyboxVertexBuffer, NULL);
	//Create an index buffer for the skybox, 6 indices per side, so 36 indices total.
	g_pd3dDevice->CreateIndexBuffer(36 * sizeof(int), D3DUSAGE_WRITEONLY, D3DFMT_INDEX32, D3DPOOL_MANAGED, &g_pSkyboxIndexBuffer, NULL);

	VOID* pVertices;
	g_pSkyboxVertexBuffer->Lock(0, 24 * sizeof(Vertex), (void**)&pVertices, 0);   //lock buffer
	memcpy(pVertices, skybox->getVertices(), 24 * sizeof(Vertex)); //copy data
	g_pSkyboxVertexBuffer->Unlock();                                 //unlock buffer

	//Put the g_pSkyboxVertexBuffer into the array, we need to do this or we have issues with stack/heap memory allocation.
	skyboxVertexBuffers[skybox] = &g_pSkyboxVertexBuffer;

	g_pSkyboxIndexBuffer->Lock(0, 36 * sizeof(int), (void**)&pVertices, 0);   //lock buffer
	memcpy(pVertices, skybox->getIndices(), 36 * sizeof(int));   //copy data
	g_pSkyboxIndexBuffer->Unlock();                                 //unlock buffer

	//Put the g_pSkyboxIndexBuffer into the array, we need to do this or we have issues with stack/heap memory allocation.
	skyboxIndexBuffers[skybox] = &g_pSkyboxIndexBuffer;
};

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
};

void DirectXRenderer::Render(HWND hwnd, Scene* scene)
{
	// Clear the backbuffer and the zbuffer
	g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 127, 0), 1.0f, 0);

	// Begin the scene
	if (SUCCEEDED(g_pd3dDevice->BeginScene()))
	{
		Entity* activeCamera = scene->getActiveCamera();

		//If we do not set a default material, there's a chance it will crash or show black matter.
		D3DMATERIAL9 material = D3DMATERIAL9();
		material.Ambient = D3DCOLORVALUE();
		material.Ambient.a = 1.0f;
		material.Ambient.r = 1.0f;
		material.Ambient.g = 1.0f;
		material.Ambient.b = 1.0f;
		g_pd3dDevice->SetMaterial(&material);

		//We disable the z-buffer for the skybox so it will always be the background.
		g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
		//We only want to rotate the skybox with the camera, not move it
		D3DXMATRIXA16 matWorldFinal;
		D3DXMatrixTranslation(&matWorldFinal, 0.0f, 0.0f, 0.0f);
		D3DXMatrixMultiply(&matWorldFinal, &matWorldFinal, &activeCamera->rotationMatrix);
		g_pd3dDevice->SetTransform(D3DTS_WORLD, &matWorldFinal);

		//Draw the actual skybox
		if (Skybox *skybox = scene->getSkybox())
		{
			//Make sure the TextureResource is loaded properly, otherwise set the texture to NULL so it's white instead of a crash.
			if (skybox->getTextureResource())
			{
				g_pd3dDevice->SetTexture(0, skybox->getTextureResource()->getTexture());
			}
			else
			{
				g_pd3dDevice->SetTexture(0, NULL);
			}
			g_pd3dDevice->SetStreamSource(0, *skyboxVertexBuffers[skybox], 0, sizeof(Vertex));
			g_pd3dDevice->SetFVF(D3DFVF_CUSTOMVERTEX);
			g_pd3dDevice->SetIndices(*skyboxIndexBuffers[skybox]);
			g_pd3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 24, 0, 12);
		}

		//Enable the z-buffer again because we want all the other objects to behave "normal"
		g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
		//In addition to moving the terrain with the camera, we also want to scale it in height, otherwise there's not much depth.
		D3DXMATRIXA16 matWorldScaled;
		D3DXMatrixScaling(&matWorldScaled, 1.0f, 250.0f, 1.0f);
		D3DXMatrixMultiply(&matWorldFinal, &matWorldScaled, &activeCamera->finalMatrix);
		g_pd3dDevice->SetTransform(D3DTS_WORLD, &matWorldFinal);

		//Draw the actual terrain
		if (Terrain *terrain = scene->getTerrain())
		{
			//Make sure the TextureResource is loaded properly, otherwise set the texture to NULL so it's white instead of a crash.
			if (terrain->getTextureResource())
			{
				g_pd3dDevice->SetTexture(0, terrain->getTextureResource()->getTexture());
			}
			else
			{
				g_pd3dDevice->SetTexture(0, NULL);
			}
			g_pd3dDevice->SetStreamSource(0, *terrainVertexBuffers[terrain], 0, sizeof(Vertex));
			g_pd3dDevice->SetFVF(D3DFVF_CUSTOMVERTEX);
			g_pd3dDevice->SetIndices(*terrainIndexBuffers[terrain]);
			g_pd3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, terrain->getWidth() * terrain->getHeight(), 0, (terrain->getWidth() - 1) * (terrain->getHeight() - 1) * 2);
		}
		//We want to draw all the models in the current scene, so we loop through them.
		std::vector<Entity*> entities = scene->getModels();
		for each(Entity *currentEntity in entities)
		{
			//Make sure the model "moves" properly with the active camera. 
			D3DXMATRIXA16 matWorldFinal;
			D3DXMatrixMultiply(&matWorldFinal, &currentEntity->finalMatrix, &activeCamera->finalMatrix);
			g_pd3dDevice->SetTransform(D3DTS_WORLD, &matWorldFinal);

			Model *currentModel = (Model*)currentEntity;
			if (currentModel->getModel())
			{
				// Meshes are divided into subsets, one for each material. Render them in a loop
				for (DWORD i = 0; i < currentModel->getModel()->getNumberOfMaterials(); i++)
				{
					// Set the material and texture for this subset
					g_pd3dDevice->SetMaterial(&currentModel->getModel()->getMeshMaterials()[i]);
					//Make sure the TextureResource is loaded properly, otherwise set the texture to NULL so it's white instead of a crash.
					if (currentModel->getModel()->getTextures()[i])
					{
						g_pd3dDevice->SetTexture(0, currentModel->getModel()->getTextures()[i]->getTexture());
					}
					else
					{
						g_pd3dDevice->SetTexture(0, NULL);
					}

					// Draw the mesh subset
					currentModel->getModel()->getMesh()->DrawSubset(i);
				}
			}
		}
		// End the scene
		g_pd3dDevice->EndScene();
	}

	// Present the backbuffer contents to the display
	g_pd3dDevice->Present(NULL, NULL, hwnd, NULL);
};