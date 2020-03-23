#include "StdAfx.h"
#include "NextFrameAction.h"
#include "../NetCDFDataProvider/ControlorInterface.h"
#include "MainWindow.h"
extern MainWindow* g_MainWindow;

ADD_MYACTION_CONTSTRUCTED_DECLARATION(NextFrameAction)

void NextFrameAction::MyAction()
{
	g_MainWindow->StopStrack();
}

void NextFrameAction::InitMyAction()
{
	
}
