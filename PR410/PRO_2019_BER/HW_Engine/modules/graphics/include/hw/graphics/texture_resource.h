#pragma once

#include "hw/resource/resource.h"

struct ID3D11Texture2D;

namespace hw
{
	class TextureResource : public Resource
	{
	public:

							TextureResource();
							~TextureResource();

		ID3D11Texture2D*	getTexture() const { return m_pTexture; }

	protected:

		virtual bool		handleCreate( const void* pData, size_t dataSize ) override final;
		virtual void		handleDestroy() override final;

	private:

		ID3D11Texture2D*	m_pTexture = nullptr;
	};
}