#include "stdafx.h"
#include "Instrument.h"


CInstrument::CInstrument()
{
	mInput[0] = 1;
	mInput[1] = 0;
	mInput[2] = 0;
	mInput[3] = 0;
	mInput[4] = 0;
	mInput[5] = 0;
}


CInstrument::~CInstrument()
{
}

//CInstrument::CInstrument(double bpm)
//{
//	m_bpm = bpm;
//}