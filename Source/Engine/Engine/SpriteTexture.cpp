////////////////////////////////////////////////////////////////////////////////
// Filename: SpriteTexture.cpp
////////////////////////////////////////////////////////////////////////////////
#include "SpriteTexture.h"

SpriteTexture::SpriteTexture()
{
	/*
	ID3D11ShaderResourceView** textures; // Frames
	float index; // Current frame - cast to int - partial steps
	float frameRate;
	int maxFrame; 
	*/

	textures = 0;
	index = 0;
	frameRate = 0;
	maxFrame = 0;
}

SpriteTexture::SpriteTexture(const SpriteTexture& other)
{
}

SpriteTexture::~SpriteTexture()
{
}

bool SpriteTexture::Initialize(ID3D11Device*, WCHAR*)
{
	return false;
}

void SpriteTexture::Shutdown()
{
	if (textures) 
	{
		delete [] textures;
		textures = 0;
	}
	return;
}

ID3D11ShaderResourceView* SpriteTexture::GetCurrentTexture()
{
	// Use index for current frame
	// Return the corresponding texture (for displaying)
	return NULL;
}