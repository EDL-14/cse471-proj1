#include "stdafx.h"
#include "FlangeEffect.h"


CFlangeEffect::CFlangeEffect()
{
}


CFlangeEffect::~CFlangeEffect()
{
}

void CFlangeEffect::Process(double* input, double* output)
{
	double m_new = m_delay + (RANGE * m_delay) * sin(2 * PI * RATE);

	m_wrloc = (m_wrloc + 1) % 10000000;
	m_queue1[m_wrloc] = input[0];

	int rdloc = (m_wrloc + 10000000 - int((m_new * m_sampleRate + 0.5)) * 2) % 200000;

	output[0] = input[0] / 3 + m_queue1[rdloc] / 3 + (mOutL[rdloc] * LEVEL) / 3;
	output[0] *= m_wet;
	output[0] += input[0] * m_dry;
	mOutL[m_wrloc] = output[0];


	m_wrloc = (m_wrloc + 1) % 10000000;
	m_queue1[m_wrloc] = input[1];
	rdloc = (m_wrloc + 10000000 - int((m_new * m_sampleRate + 0.5)) * 2) % 200000;

	output[1] = input[1] / 3 + m_queue1[(rdloc + 1) % 10000000] / 3 + (mOutR[(rdloc + 1) % 200000] * LEVEL) / 3;
	output[1] *= m_wet;
	output[1] += input[1] * m_dry;

	mOutR[m_wrloc] = output[1];
}

void CFlangeEffect::Start()
{
	m_wrloc = 0;
	m_rdloc = 0;
	mOutL.resize(10000000);
	mOutR.resize(10000000);
}

bool CFlangeEffect::Generate()
{
	return true;
}