#include "stdafx.h"
#include "ChorusEffect.h"


CChorusEffect::CChorusEffect()
{
}


CChorusEffect::~CChorusEffect()
{
}

void CChorusEffect::Start()
{
	m_wrloc = 0;
	m_rdloc = 0;
	m_queue1.resize(1000000);
	m_queue2.resize(1000000);
}

bool CChorusEffect::Generate()
{
	return true;
}

void CChorusEffect::Process(double* input, double* output)
{

	double newDelay = m_delay + (RANGE * m_delay) * sin(2 * PI * RATE);

	m_wrloc = (m_wrloc + 1) % 1000000;

	for (auto k = 0; k < 2; k++) 
	{
		m_queue1[m_wrloc] = input[k];
		m_queue2[m_wrloc] = input[k];

	}

	int legnth = int((newDelay * GetSampleRate() + 0.5)) * 2;

	auto i = 0;
	while (i < 2) 
	{
		int rdloc = (m_wrloc + 1000000 - legnth) % 1000000;

		output[i] = input[i] / 2 + m_queue1[rdloc] / 2;
		output[i] *= m_wet;
		output[i] += input[i] * m_dry;

		m_wrloc = (m_wrloc + 1) % 1000000;
		m_queue2[m_wrloc] = input[1];

		output[i] = input[i] / 2 + m_queue2[rdloc] / 2;
		output[i] *= m_wet;
		output[i] += input[i] * m_dry;
		i++;
	}

}


