#include "stdafx.h"
#include "AudioFilter.h"
#include "Envelope.h"


CAudioFilter::CAudioFilter()
{
}


CAudioFilter::~CAudioFilter()
{
}

void CAudioFilter::Start()
{
	m_time = 0;

	m_envelope->SetDuration(m_duration);
	m_envelope->SetSampleRate(GetSampleRate());

	m_envelope->Start();
}


bool CAudioFilter::Generate()
{
	auto amplitude_factor = m_envelope->GetEnvelopeLevel();

	m_frame[0] = m_source->Frame(0) * amplitude_factor;
	m_frame[1] = m_source->Frame(1) * amplitude_factor;

	m_time += GetSamplePeriod();

	return m_duration > m_time;
}
