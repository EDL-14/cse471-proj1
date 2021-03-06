#include "stdafx.h"
#include "AudioEffect.h"

#include "Note.h"


// Constructor -> Resizes the que to be the max size
CAudioEffect::CAudioEffect()
{
	m_queue1.resize(1000000);
	m_queue2.resize(1000000);
}


CAudioEffect::~CAudioEffect()
{
}

void CAudioEffect::SetNote(CNote *note)
{
	// Get a list of all attribute nodes and the
	// length of that list
	CComPtr<IXMLDOMNamedNodeMap> attributes;
	note->Node()->get_attributes(&attributes);
	long len;
	attributes->get_length(&len);

	for (int i = 0; i < len; i++)
	{
		CComPtr<IXMLDOMNode> attrib;
		attributes->get_item(i, &attrib);

		CComBSTR name;
		attrib->get_nodeName(&name);

		CComVariant value;
		attrib->get_nodeValue(&value);

		if (name == "wet")
		{
			value.ChangeType(VT_R8);
			SetWet(value.dblVal);
		}
		else if (name == "delay")
		{
			value.ChangeType(VT_R8);
			SetDelay(value.dblVal);
		}
		else if (name == "dry")
		{
			value.ChangeType(VT_R8);
			SetDry(value.dblVal);
		}
		else if (name == "threshold")
		{
			value.ChangeType(VT_R8);
			SetThreshold(value.dblVal);
		}
	}
}