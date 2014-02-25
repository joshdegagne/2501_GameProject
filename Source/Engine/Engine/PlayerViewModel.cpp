
#include "EntityType.h"
#include "PlayerViewModel.h"
#include "ViewModel.cpp"

PlayerViewModel::PlayerViewModel() : ViewModel<Player>(EntityType::PLAYER)
{
}

PlayerViewModel::~PlayerViewModel()
{
}

bool PlayerViewModel::InitializeVertexModels(ID3D11Device* d3dDevice)
{
	//initialize vertices and textures for rendering to d3dDevice

	bool result = vertexModel->Initialize(d3dDevice);

	if(!result) return false;

	result = initializeTextures(d3dDevice);

	return result;
}

bool PlayerViewModel::initializeTextures(ID3D11Device* d3dDevice){
	
	bool result;

	// Create quad texture object.
	texture = new Texture;
	if(!texture)
	{
		return false;
	}
	// Initialize the body texture object.
	result = texture->Initialize(d3dDevice, textureFileName);
	if(!result)
	{
		return false;
	}

	return true;
}

ID3D11ShaderResourceView* PlayerViewModel::GetTexture(){

	return texture->GetTexture();
}

bool PlayerViewModel::Render(ID3D11DeviceContext* deviceContext, XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix, ColorShader* colorShader, TextureShader* textureShader)
{
	return false;
}