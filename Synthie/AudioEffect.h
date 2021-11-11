/*
 * Base class for all effects that will be implemented. Vitrual class. 
 * All of the effects have the same variables associated with them thus the need for this class.
 * Going off of description for effects page/questions
 */

#pragma once
#include "Instrument.h"
#include <vector>
class CAudioEffect :
	public CInstrument
{
public:
	virtual ~CAudioEffect();

	virtual void Process(double *frameIn, double *frameOut) = 0;

	void SetDelay(double delay) { m_delay = delay; }

	void SetWet(double wet) { m_wet = wet; }

	void SetDry(double dry) { m_dry = dry; }

	void SetThreshold(double threshold) { m_Threshold = threshold; }

	virtual void SetNote(CNote *note) override;

protected:
	CAudioEffect();

	// Controllable effects sends
	double	m_delay;
	double	m_wet;
	double	m_dry;
	double  m_Threshold;

	int m_wrloc;
	int m_rdloc;

	double mTime = 5.0;

	std::vector<double> m_queue1;
	std::vector<double> m_queue2;

	const double RANGE = .5;
	const int RATE = 2;
	const int LEVEL = 2;
};

