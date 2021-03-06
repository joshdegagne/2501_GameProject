////////////////////////////////////////////////////////////////////////////////
// Filename: BoundViewModel.h
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "ViewModel.h"
#include "ColorShader.h"
#include "TextureManager.h"

class BoundingBox;
//class TextureManager;

////////////////////////////////////////////////////////////////////////////////
// Class name: BoundViewModel
////////////////////////////////////////////////////////////////////////////////
class BoundViewModel : public ViewModel<BoundingBox>
{
public:
	BoundViewModel();
	virtual ~BoundViewModel();
	
	bool InitializeTextures(TextureManager* texMan);
	bool InitializeVertexModels(ID3D11Device* d3dDevice);

protected:
	bool initializeTextures(ID3D11Device* d3dDevice);
	bool RenderEntity(ID3D11DeviceContext*, XMFLOAT4X4, XMFLOAT4X4, ColorShader*, TextureShader*, BoundingBox*);

private:
	ColorVertexType* vertices;
	unsigned long*	 indices;
	Model*			 vertexModel;
};