#pragma once

#include "hw/core/linked_list.h"

namespace hw
{
	class SoundResource;
	struct SoundInstance;
	struct SoundListener;
	struct Vector;
	struct SoundPlatformState;

	class SoundSystem
	{
	public:

							SoundSystem();
							~SoundSystem();

		bool				create();
		void				destroy();

		void				update();

		SoundListener*		addListener( const Vector& position );
		void				removeListener( SoundListener* pListener );
		void				setListenerPosition( SoundListener* pListener, const Vector& position );

		SoundInstance*		playSound( const SoundResource* pResource, bool hasPosition, const Vector& position );
		void				stopSound( SoundInstance* pInstance );

		void				setInstanceVolume( SoundInstance* pInstance, float volume );
		void				setInstancePosition(SoundInstance* pInstance, const Vector& position );

	private:

		using ListenerList = LinkedList< SoundListener >;
		using InstanceList = LinkedList< SoundInstance >;

		SoundPlatformState*	m_PlatformState;

		ListenerList		m_listeners;
		InstanceList		m_instances;
	};
}