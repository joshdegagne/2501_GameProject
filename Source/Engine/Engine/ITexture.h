#ifndef ITEXTURE_H
#define ITEXTURE_H


#include <d3d11.h>

class ITexture
{
public:
	virtual ~ITexture() {}

	virtual ID3D11ShaderResourceView* GetTexture() = 0;
	virtual bool Initialize(ID3D11Device*, WCHAR*) = 0;
	virtual void Shutdown() = 0;
};

#endif