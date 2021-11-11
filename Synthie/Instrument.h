#pragma once
#include "AudioNode.h"
#include "Note.h"
#include "AudioFilter.h"

class CInstrument :
	public CAudioNode
{
public:
	CInstrument();
	~CInstrument();
	CInstrument(double);

	virtual void SetNote(CNote *note) = 0;
	double Send(int i) { return mInput[i]; }
	void SetSend(int i, double value) { mInput[i] = value; }


protected:
	CAudioFilter m_audiofilter;
	CEnvelope* m_envelope;

	double mInput[5];
};

