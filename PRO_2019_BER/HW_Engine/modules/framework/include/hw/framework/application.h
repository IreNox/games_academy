#pragma once

namespace hw
{
	class Framework;

	class Application
	{
	public:

		virtual bool	create( Framework* pFramework ) = 0;
		virtual void	destroy() = 0;

		virtual void	update() = 0;
		virtual void	render() = 0;
	};

	Application& getApplication();
}