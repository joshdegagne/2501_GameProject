////////////////////////////////////////////////////////////////////////////////
// Filename: IcePatchViewModel.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "ViewModel.h"

class Game;
class Model;
class IcePatchObstacle;
class TextureManager;

////////////////////////////////////////////////////////////////////////////////
// Class: IcePatchViewModel
////////////////////////////////////////////////////////////////////////////////
class IcePatchViewModel : public ViewModel<IcePatchObstacle>
{
public:
	IcePatchViewModel();
	~IcePatchViewModel();
	
	bool InitializeTextures(TextureManager* texMan);
	bool InitializeVertexModels(ID3D11Device* d3dDevice);

protected:
	bool initializeTextures(ID3D11Device* d3dDevice);
	bool RenderEntity(ID3D11DeviceContext* deviceContext,  XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix, ColorShader* colorShader, TextureShader* textureShader, IcePatchObstacle* entity);

	Model*		icePatchVertexModel;
	ITexture*	icePatchTexture;
};