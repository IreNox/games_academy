#pragma once

#include "hw/framework/application.h"

namespace hw
{
	class GameApplication : public Application
	{
	public:

		virtual bool	create( Framework* pFramework ) override final;
		virtual void	destroy() override final;

		virtual void	update() override final;
		virtual void	render() override final;

	private:

		Framework*		m_pFramework = nullptr;
	};
}