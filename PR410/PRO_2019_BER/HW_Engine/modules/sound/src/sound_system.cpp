#include "hw/sound/sound_system.h"

namespace hw
{
	SoundSystem::SoundSystem()
	{
	}

	SoundSystem::~SoundSystem()
	{
	}

	bool SoundSystem::create()
	{
		return true;
	}

	void SoundSystem::destroy()
	{
	}

	void SoundSystem::update()
	{
	}

	SoundListener* SoundSystem::addListener( const Vector& position )
	{
		return nullptr;
	}

	void SoundSystem::removeListener( SoundListener* pListener )
	{
	}

	void SoundSystem::setListenerPosition(SoundListener* pListener, const Vector& position)
	{
	}

	SoundInstance* SoundSystem::playSound( const SoundResource* pResource, bool hasPosition, const Vector& position )
	{
		return nullptr;
	}

	void SoundSystem::stopSound( SoundInstance* pInstance )
	{
	}

	void SoundSystem::setInstanceVolume( SoundInstance* pInstance, float volume )
	{
	}

	void SoundSystem::setInstancePosition( SoundInstance* pInstance, const Vector& position )
	{
	}
}
