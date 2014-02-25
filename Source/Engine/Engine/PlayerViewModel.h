#pragma once

#include "ViewModel.h"

class Player;
class ITexture;

class PlayerViewModel : ViewModel<Player>
{
public:
	PlayerViewModel();
	virtual ~PlayerViewModel();

	bool InitializeVertexModels(ID3D11Device* d3dDevice);

protected:
	bool RenderEntity(ID3D11DeviceContext* deviceContext, XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix, ColorShader* colorShader, TextureShader* textureShader);

private:
	ITexture* texture;
};

