#pragma once

#include "hw/framework/application.h"

namespace hw
{
	class Resource;
	struct ResourceLoadContext;

	class GameApplication : public Application
	{
	public:

		virtual bool			create( Framework* pFramework ) override final;
		virtual void			destroy() override final;

		virtual void			update() override final;
		virtual void			render() override final;

	private:

		Framework*				m_pFramework	= nullptr;

		ResourceLoadContext*	m_pLoadContext	= nullptr;
		const Resource*			m_pResource		= nullptr;
	};
}