#include "StdAfx.h"
#include "PaoDianControler.h"


PaoDianControler::PaoDianControler(void) : m_pPaoDianGeometry(0)
{
	
}

PaoDianControler::~PaoDianControler(void)
{
}

NodeInfo* PaoDianControler::GetNodeFromID( int id )
{
	return 0;
}

void PaoDianControler::DisplayFromIDs( int id )
{
	m_pPaoDianGeometry->VisblePaoDian(id, true);
}

void PaoDianControler::HideFromIDs( int id )
{
	m_pPaoDianGeometry->VisblePaoDian(id, false);
}

QStandardItemModel* PaoDianControler::GetModel()
{
	return &m_StandardItemModel;
}

void PaoDianControler::HideAll()
{
	m_pPaoDianGeometry->VisbleAll(false);
}

void PaoDianControler::DisplayAll()
{
	m_pPaoDianGeometry->VisbleAll(true);
}
