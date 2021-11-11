#include "stdafx.h"
#include "AdditiveInstrument.h"
#include "Note.h"
#include "Notes.h"
#include "Envelope.h"
#include "ADSREnvelope.h"
#include <sstream>


CAdditiveInstrument::CAdditiveInstrument()
{
	m_duration = 0.1;
}


CAdditiveInstrument::CAdditiveInstrument(double bpm)
{
	m_duration = 0.1;
	m_bpm = bpm;
}


CAdditiveInstrument::~CAdditiveInstrument()
{
}


void CAdditiveInstrument::Start()
{
	add_wave.SetSampleRate(GetSampleRate());
	add_wave.Start();
	m_time = 0;

	m_envelope = new CADSREnvelope();

	static_cast<CADSREnvelope*>(m_envelope)->SetAttack(.05);
	static_cast<CADSREnvelope*>(m_envelope)->SetRelease(.05);

	m_audiofilter.SetEnvelope(m_envelope);
	m_audiofilter.SetSource(&add_wave);
	m_audiofilter.SetSampleRate(GetSampleRate());
	m_audiofilter.SetDuration(m_duration);
	m_audiofilter.Start();
}


bool CAdditiveInstrument::Generate()
{
	m_envelope->Generate();

	if (add_wave.GetCFstar())
	{
		if (m_time < add_wave.GetCFTime())
		{
			add_wave.Generate();
		}

		else if (m_time > add_wave.GetCFTime() && m_time < add_wave.GetCFTime() + cross_dur)
		{
			add_wave.GenerateCF(m_time, cross_dur);
		}
	}

	else
	{
		add_wave.Generate();
	}

	auto flag = m_audiofilter.Generate();

	for (auto i = 0; i < 2; i++) 
	{
		m_frame[i] = m_audiofilter.Frame(i);
	}

	m_time += GetSamplePeriod();

	return flag;
}


void CAdditiveInstrument::SetNote(CNote *note)
{
	// Get a list of all attribute nodes and the
	// length of that list
	CComPtr<IXMLDOMNamedNodeMap> attributes;
	note->Node()->get_attributes(&attributes);
	long len;
	attributes->get_length(&len);

	// Loop over the list of attributes
	for (int i = 0; i < len; i++)
	{
		// Get attribute i
		CComPtr<IXMLDOMNode> attrib;
		attributes->get_item(i, &attrib);

		// Get the name of the attribute
		CComBSTR name;
		attrib->get_nodeName(&name);

		// Get the value of the attribute.  A CComVariant is a variable
		// that can have any type. It loads the attribute value as a
		// string (UNICODE), but we can then change it to an integer 
		// (VT_I4) or double (VT_R8) using the ChangeType function 
		// and then read its integer or double value from a member variable.
		CComVariant value;
		attrib->get_nodeValue(&value);

		if (name == "duration")
		{
			value.ChangeType(VT_R8);
			
			SetDur(value.dblVal * (1 / (m_bpm / 60)));
		}

		else if (name == "note")
		{
			SetFreq(NoteToFrequency(value.bstrVal));
		}

		else if (name == "harmonics")
		{
			AddHar(value.bstrVal);
		}

		else if (name == "vibrato")
		{
			value.ChangeType(VT_R8);
			add_wave.SetVibstar(true);
			add_wave.SetVib(value.dblVal);
		}

		else if (name == "vibratoRate")
		{
			value.ChangeType(VT_R8);
			add_wave.SetVibrate(value.dblVal);
		}

		else if (name == "crossfade")
		{
			value.ChangeType(VT_R8);

			cross_dur = value.dblVal;
			add_wave.SetCFstar(true);

			add_wave.SetCFTime(m_duration - cross_dur);
		}

		else if (name == "crossfadeBetween")
		{
			value.ChangeType(VT_R8);

			add_wave.SetCFTime(add_wave.GetCFTime() - (1 / (m_bpm / 60)) * value.dblVal);
		}
	}
}


void CAdditiveInstrument::SetNextNote(CNote* next_note)
{
	m_next = new CAdditiveInstrument();

	m_next->SetSampleRate(GetSampleRate());

	m_next->SetNote(next_note);

	m_next->Start();

	add_wave.SetNextWave(&m_next->add_wave);
}


void CAdditiveInstrument::AddHar(wstring harmonics)
{
	// harmonics = 1 .3 .5
	wstringstream m_save(harmonics);
	wstring harmonic_amp;
	while (m_save >> harmonic_amp) 
	{
		add_wave.AddHarmonic(stod(harmonic_amp));
	}
}