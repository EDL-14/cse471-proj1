#pragma once
#include "Envelope.h"

class CADSREnvelope :
	public CEnvelope
{
public:
	CADSREnvelope();
	virtual ~CADSREnvelope();

	virtual void Start() override;
	virtual bool Generate() override;

	void SetAttack(double attack) { m_attack = attack; }
	void SetDecay(double decay) { m_decay = decay; }
	void SetSustain(double sustain) { sustain_level = sustain; }
	void SetRelease(double release) { m_release = release; }

private:
	double m_attack;
	double m_decay;
	double sustain_level;
	double m_release;
};

