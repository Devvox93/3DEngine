/*
	3D Engine
	Xresource.h
	Purpose: Loads X resources.

	@author Patrick, Nick, Robert, Jordi
	@version 1.0
*/

#ifndef _XRESOURCE_H
#define _XRESOURCE_H

#include "Resource.h"
#include <d3dx9.h>
#include "TextureResource.h"
#include "ResourceManager.h"

class XResource : public Resource
{
public:
	/*
		Loads an X resource from file.

		@param path: Path to the resource file.
		@param g_pd3dDevice: Device to use for loading the resource.
		@param rsm: The resource manager which manages textures.
	*/
	XResource(std::string path, LPDIRECT3DDEVICE9 g_pd3dDevice, ResourceManager* rsm);

	XResource();

	~XResource();
	/*
		Function to get the mesh of the X model.

		@return LPD3DXMESH: The mesh of the X model.
	*/
	LPD3DXMESH getMesh();

	/*
		Function to get the mesh materials of the X model.

		@return D3DMATERIAL9*: Pointer to the mesh material of the X model.
	*/
	D3DMATERIAL9* getMeshMaterials();

	/*
		Function to get the textures of the X model.

		@return TextureResource**: Array of pointers to the textures of the X model.
	*/
	TextureResource** getTextures();

	/*
		Function to get the number of materials from the X model.

		@return DWORD: The number of materials of the X model.
	*/
	DWORD getNumberOfMaterials();
private:
	LPD3DXMESH          g_pMesh;			// Our mesh object in sysmem
	D3DMATERIAL9*       g_pMeshMaterials;	// Materials for our mesh
	TextureResource**   myTextures;			// Textures for our mesh
	DWORD               g_dwNumMaterials;	// Number of mesh materials
};
#endif