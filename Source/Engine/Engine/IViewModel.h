#pragma once

#include "DirectXHelper.h"
#include <d3d11.h>

using namespace DirectX;

class ColorShader;
class TextureShader;

class IViewModel
{
public:
	virtual bool InitializeVertexModels(ID3D11Device* d3dDevice) = 0;
	virtual bool Render(ID3D11DeviceContext* deviceContext,  DirectX::XMFLOAT4X4 viewMatrix, DirectX::XMFLOAT4X4 projectionMatrix, ColorShader* colorShader, TextureShader* textureShader) = 0;
};