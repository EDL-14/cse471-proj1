#include "stdafx.h"
#include "AdditiveWave.h"
#include <cmath>

CAdditiveWave::~CAdditiveWave()
{
}

CAdditiveWave::CAdditiveWave()
{
	m_period = 0;
	m_amp = 0.1;
	m_freq = 440;
}





void CAdditiveWave::Start()
{
	m_period = 0;
	m_time = 0;
	SetWavetables();
}


bool CAdditiveWave::Generate()
{
	// set frame
	m_frame[0] = m_container[m_period];
	m_frame[1] = m_frame[0];
	m_period = (m_period + 1) % m_container.size();

	return true;
}


void CAdditiveWave::SetWavetables()
{
	auto m_size = GetSampleRate();
	m_container.resize(m_size);

	double m_sine = 0;
	double m_vib = 0;

	for (auto i = 0; i < m_size; i++, m_time += 1. / GetSampleRate())
	{
		auto sample = sin(m_sine) * m_amp;		
		
		if (m_implement_vib)
		{
			ImplementVib(&m_sine, &m_vib);
		}

		if (m_harmonics.size() > 0)
		{
			ImplementHarmonics(&sample, m_time);
		}



		m_container[i] = sample;
	}
}


void CAdditiveWave::ImplementHarmonics(double* sample, double time)
{

	auto i = 0;
	while (i < m_harmonics.size() && (m_freq * (i + 1)) < GetSampleRate() / 2)
	{
		*sample += m_harmonics[i] * (m_amp / (i + 1)) * (sin(time * 2 * PI * (i + 1) * m_freq));
		i++;
	}
}


void CAdditiveWave::ImplementVib(double* sine_rads, double* vibrato_rads)
{
	double sample = short(m_amp * sin(*sine_rads));

	*sine_rads += (2 * PI * (m_freq + (sin(*vibrato_rads) * m_vib_effect.vibrato))) / m_sampleRate;
	*vibrato_rads += (2 * PI * m_vib_effect.vibrato_rate) / m_sampleRate;
}


void CAdditiveWave::GenerateCF(double time, double crossfade_dur)
{
	double next_sample[2];
	double current_sample[2];
	double interpolated_sample;

	if (m_cf_wave != nullptr && m_period > m_cf_wave->GetContainerSize() && m_period > GetContainerSize())
	{
		m_frame[0] = m_container[m_period];
		m_frame[1] = m_frame[0];

	}

	else
	{
		next_sample[0] = next_sample[1] = m_cf_wave->m_container[m_period];
		current_sample[0] = current_sample[1] = m_container[m_period];
		interpolated_sample = current_sample[0] * ((crossfade_dur - time - m_cf_time) / crossfade_dur) + next_sample[0] * (time - m_cf_time / crossfade_dur);

		m_frame[0] = m_frame[1] = interpolated_sample;
	}

	m_period = (m_period + 1) % m_container.size();
}