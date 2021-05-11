#pragma once

#include "hw/core/linked_list.h"
#include "hw/core/handle.h"

namespace hw
{
	class SoundResource;
	struct Vector;
	struct SoundPlatformState;

	struct SoundListener;
	using SoundListenerHandle = Handle< SoundListener, uint64, 32u >;

	struct SoundInstance;
	using SoundInstanceHandle = Handle< SoundInstance, uint64, 32u >;

	class SoundSystem
	{
	public:

							SoundSystem();
							~SoundSystem();

		bool				create();
		void				destroy();

		void				update();

		SoundListenerHandle	addListener( const Vector& position );
		void				removeListener( SoundListenerHandle listener );
		void				setListenerPosition( SoundListenerHandle listenerHandle, const Vector& position );

		SoundInstanceHandle	playSound( const SoundResource* pResource, bool hasPosition, const Vector& position );
		void				stopSound( SoundInstanceHandle instanceHandle );

		void				setInstanceVolume( SoundInstanceHandle instanceHandle, float volume );
		void				setInstancePosition( SoundInstanceHandle instanceHandle, const Vector& position );

	private:

		static constexpr size_t MaxListenerCount = 16u;

		using InstanceList = LinkedList< SoundInstance >;

		SoundPlatformState*	m_PlatformState;

		SoundListener*		m_pListeners;
		uint64				m_nextListenerCounter;

		InstanceList		m_instances;

		SoundListener*		getListener( SoundListenerHandle handle );
	};
}