#include "StdAfx.h"
#include "ExportImageAtion.h"
#include "ui_ExportImage.h"
#include "MainWindow.h"
#include <QMessageBox>
extern MainWindow* g_MainWindow;
extern ConfigAccesser g_GlobleConfig;

ADD_MYACTION_CONTSTRUCTED_DECLARATION(ExportImageAtion)

void ExportImageAtion::MyAction()
{
	/*QString strFileName = QFileDialog::getSaveFileName(g_MainWindow, QString::fromLocal8Bit("导出图片"), "", "JPEG (*.jpg *.jpeg)");
	if(strFileName.size() > 0)
		g_MainWindow->ExportImage(strFileName);*/

	/*QMessageBox::StandardButton r = (QMessageBox::StandardButton)QMessageBox::question(g_MainWindow
	, QString::fromLocal8Bit("保存配置")
	, QString::fromLocal8Bit("确定要保存新的配置信息吗？")
	, QMessageBox::Yes
	, QMessageBox::No);

	if(r == QMessageBox::No) 
	return;*/

	g_GlobleConfig.Write();

	g_MainWindow->FlushCubesList();
}

void ExportImageAtion::InitMyAction()
{
	
}
