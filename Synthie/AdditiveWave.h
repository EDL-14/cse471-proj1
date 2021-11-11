#pragma once
#include "CVibrato.h"
#include "AudioNode.h"

#include <vector>
using namespace std;

class CAdditiveWave :
	public CAudioNode
{
public:
	CAdditiveWave();
	virtual ~CAdditiveWave();

	virtual void Start() override;
	virtual bool Generate() override;

	void AddHarmonic(double harmonic) { m_harmonics.push_back(harmonic); }
	void ImplementHarmonics(double* sample, double time);
	void ImplementVib(double* sine_rads, double* vibrato_rads);
	void GenerateCF(double time, double crossfade_dur);

	vector<double> GetHarm() { return m_harmonics; }
	bool GetVibstar() { return m_implement_vib; }
	bool GetCFstar() { return m_imp_cf; }
	double GetCFTime() { return m_cf_time; }

	void SetNextWave(CAdditiveWave* next) { m_cf_wave = next; }

	void SetVibstar(bool star) { m_implement_vib = star; }
	void SetVib(double vibrato) { m_vib_effect.vibrato = vibrato; }
	void SetVibrate(double vibrato_rate) { m_vib_effect.vibrato_rate = vibrato_rate; }


	void SetCFstar(bool star) { m_imp_cf = star; }
	void SetCFTime(double time) { m_cf_time = time; }

	double GetContainerSize() { return m_container.size(); }

	void SetFreq(double f) { m_freq = f; }
	void SetAmplitude(double a) { m_amp = a; }
	void SetWavetables();



private:
	vector<double> m_harmonics;
	double m_time;
	bool m_implement_vib = false;
	bool m_imp_cf = false;
	double m_cf_time;
	CVibrato m_vib_effect;
	CAdditiveWave* m_cf_wave = nullptr;

	std::vector<double> m_container;
	double m_freq;
	double m_amp;
	int m_period;
};

