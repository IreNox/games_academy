#pragma once

namespace hw
{
	class Application;
	class GraphicsSystem;
	class InputSystem;
	class ResourceSystem;
	class SoundSystem;

	class Framework
	{
	public:

		GraphicsSystem*		getGraphicsSystem() { return m_pGraphicsSystem; }
		InputSystem*		getInputSystem() { return m_pInputSystem; }
		ResourceSystem*		getResourceSystem() { return m_pResourceSystem; }
		SoundSystem*		getSoundSystem() { return m_pSoundSystem; }

		int					run();

	private:

		Application*		m_pApplication		= nullptr;

		GraphicsSystem*		m_pGraphicsSystem	= nullptr;
		InputSystem*		m_pInputSystem		= nullptr;
		ResourceSystem*		m_pResourceSystem	= nullptr;
		SoundSystem*		m_pSoundSystem		= nullptr;

		bool				create();
		void				destroy();
	};
}