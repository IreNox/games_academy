#pragma once

#include "hw/resource/resource.h"

struct ID3D11Device;
struct ID3D11ShaderResourceView;
struct ID3D11Texture2D;

namespace hw
{
	struct TextureResourceContext
	{
		ID3D11Device*				pDevice;
	};

	class TextureResource : public Resource
	{
	public:

									TextureResource();
									~TextureResource();

		ID3D11Texture2D*			getTexture() const { return m_pTexture; }
		ID3D11ShaderResourceView*	getView() const { return m_pView; }

	protected:

		virtual bool				handleCreate( const void* pData, size_t dataSize, void* pContext ) override final;
		virtual void				handleDestroy() override final;

	private:

		ID3D11Texture2D*			m_pTexture	= nullptr;
		ID3D11ShaderResourceView*	m_pView		= nullptr;
	};
}