#include "stdafx.h"
#include "ADSREnvelope.h"


CADSREnvelope::CADSREnvelope()
{
	// ADSR
	m_attack = 0.05;
	m_decay = 0.;
	sustain_level = 1.;
	m_release = 0.05;
}


CADSREnvelope::~CADSREnvelope()
{
}


void CADSREnvelope::Start()
{
	m_level = 1.;
	m_time = 0.;
}


bool CADSREnvelope::Generate()
{
	//Attack
	if (m_time <= m_attack)
	{
		m_level = m_time / m_attack * sustain_level;
	}
	//Decay
	else if (m_time > m_attack && m_time <= m_attack + m_decay)
	{
		m_level = (m_level - 1) * ((m_time - (m_duration - m_decay)) / m_decay) + 1;
	}
	//Release
	else if ((m_duration - m_release) < m_time)
	{
		m_level = (1 - (m_time - (m_duration - m_release)) / m_release) * sustain_level;
	}
	//Sustain
	else
	{
		m_level = sustain_level;
	}

	m_time += GetSamplePeriod();

	return m_time < m_duration;
}
