#pragma once
#include "AudioNode.h"

class CEnvelope;

class CAudioFilter :
	public CAudioNode
{
public:
	CAudioFilter();
	virtual ~CAudioFilter();

	void SetEnvelope(CEnvelope* envelope) { m_envelope = envelope; }
	void SetSource(CAudioNode* source) { m_source = source; }
	void SetDuration(double duration) { m_duration = duration; }

	//! Start the node generation
	virtual void Start() override;
	//! Cause one sample to be generated
	virtual bool Generate() override;

protected:
	CAudioNode* m_source;
	CEnvelope* m_envelope;

	double m_duration;
	double m_time;
};

