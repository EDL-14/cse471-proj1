#pragma once
#include "Instrument.h"
#include "AdditiveWave.h"

#include <list>

class CAdditiveInstrument :
	public CInstrument
{
public:
	CAdditiveInstrument();
	virtual ~CAdditiveInstrument();

	CAdditiveInstrument(double bpm);

	virtual void Start() override;
	virtual bool Generate() override;
	virtual void SetNote(CNote *note) override;

	void SetNextNote(CNote* next_note);
	void AddHar(std::wstring harmonics);

	void SetFreq(double freq) { add_wave.SetFreq(freq); }
	void SetAmp(double amp) { add_wave.SetAmplitude(amp); }
	void SetDur(double duration) { m_duration = duration; }

private:
	double m_duration;
	double m_time;
	double cross_dur = 0;

private:
	CAdditiveWave add_wave;
	CAdditiveInstrument* m_next = nullptr;
};

