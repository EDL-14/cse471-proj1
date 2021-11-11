#include "stdafx.h"
#include "NoiseGateEffect.h"


CNoiseGateEffect::CNoiseGateEffect()
{
}


CNoiseGateEffect::~CNoiseGateEffect()
{
}

void CNoiseGateEffect::Start()
{
	m_wrloc = 0;
	m_rdloc = 0;
	mNoise2 = 1;
	mNoise = 1;
}

bool CNoiseGateEffect::Generate()
{
	return true;
}

void CNoiseGateEffect::Process(double* input, double* output)
{
	if (input[0] > m_Threshold && input[0] < -m_Threshold)
	{
		mNoise += 0.005;
		if (mNoise > 1)
			mNoise = 1;
	}
	else
	{
		mNoise -= 0.005;
		if (mNoise < 0)
			mNoise = 0;

	}
	output[0] = (m_dry * input[0]) + (m_wet * input[0] * mNoise);

	if (input[1] < m_Threshold && input[1] > -m_Threshold)
	{
		mNoise2 -= 0.005;
		if (mNoise2 < 0)
			mNoise2 = 0;
	}
	else
	{
		mNoise2 += 0.005;
		if (mNoise2 > 1)
			mNoise2 = 1;
	}
	output[1] = (m_dry * input[1]) + (m_wet * input[1] * mNoise2);


}



