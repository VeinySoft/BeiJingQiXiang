#include "StdAfx.h"
#include "StopTrackingAction.h"
#include "../NetCDFDataProvider/ControlorInterface.h"
#include "MainWindow.h"
extern MainWindow* g_MainWindow;

ADD_MYACTION_CONTSTRUCTED_DECLARATION(StopTrackingAction)

void StopTrackingAction::MyAction()
{
	g_MainWindow->StopStrack();
	//if(pContrlor == 0) return;
	//pContrlor->stop();
	//pContrlor->clearTrec();

	//m_pMap = g_MainWindow->GetMap();

	//goto_gis::Layer* pLayer = m_pMap->GetLayer("radar");
	///*SetCubesInterface* p_SetCubes = (SetCubesInterface*)(pLayer->GetDataProvider()->GetExtendInterface(0));
	//pContrlor = (ControlorInterface*)(pLayer->GetDataProvider()->GetExtendInterface(1));
	//pContrlor->clearTrec();*/

	//m_pMap->RemoveLayer("radar");
	//delete pLayer;
	//g_MainWindow->ClearResult();

	//pContrlor = 0;
}

void StopTrackingAction::InitMyAction()
{
	
}
