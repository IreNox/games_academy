#pragma once

#include "hw/resource/resource.h"

namespace hw
{
	enum class SoundChannelConfig
	{
		Mono,
		Stereo,
		FiveDotOne,
		SevenDotOne
	};

	enum class SoundSampleFormat
	{
		UInt8,
		UInt16,
		UInt32,
		Float,
	};

	class SoundResource : Resource
	{
	public:

		uint32				getSampleRate() const { return m_sampleRate; }
		SoundChannelConfig	getChannelConfig() const { return m_channelConfig; }
		SoundSampleFormat	getSampleFormat() const { return m_sampleFormat; }
		uint32				getFrameCount() const { return m_frameCount; }

		const void*			getSampleData() const { return m_pSampleData; }

	private:

		uint32				m_sampleRate;
		SoundChannelConfig	m_channelConfig;
		SoundSampleFormat	m_sampleFormat;
		uint32				m_frameCount;

		const void*			m_pSampleData;

		virtual bool		handleCreate( const void* pData, size_t dataSize ) override final;
		virtual void		handleDestroy() override final;
	};
}