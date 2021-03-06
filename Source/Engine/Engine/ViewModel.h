#pragma once

#include "arraylist.h"
#include "Model.h"
#include "ViewModelBase.h"
#include "Texture.h"
#include "TextureManager.h"

class Model;
enum class EntityType;

template <class T>
class ViewModel : public ViewModelBase
{
public:
	virtual ~ViewModel();

	virtual bool InitializeTextures(TextureManager* texMan) = 0;
	virtual bool InitializeVertexModels(ID3D11Device* d3dDevice) = 0;
	
	bool Render(ID3D11DeviceContext* deviceContext,  XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix, ColorShader* colorShader, TextureShader* textureShader);
	
	void Add(T* entity);

	const std::type_info& GetType();

	virtual void cleanUpArrayMemory();

protected:
	ViewModel(EntityType);

	virtual bool initializeTextures(ID3D11Device* d3dDevice) = 0;
	virtual bool RenderEntity(ID3D11DeviceContext* deviceContext,  XMFLOAT4X4 viewMatrix, XMFLOAT4X4 projectionMatrix, ColorShader* colorShader, TextureShader* textureShader, T* entity) = 0;

	//Orientation functions
	XMFLOAT4X4 GetOrientation();
	void orientRotateX(float);
	void orientRotateY(float);
	void orientRotateZ(float);
	void orientTranslate(float, float, float);

	ArrayList<T>*	entityList;

	XMFLOAT4X4 orientRotateMatrix;
    XMFLOAT4X4 orientTranslateMatrix;
};