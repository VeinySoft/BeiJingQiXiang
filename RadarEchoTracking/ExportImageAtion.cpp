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
	/*QString strFileName = QFileDialog::getSaveFileName(g_MainWindow, QString::fromLocal8Bit("����ͼƬ"), "", "JPEG (*.jpg *.jpeg)");
	if(strFileName.size() > 0)
		g_MainWindow->ExportImage(strFileName);*/

	/*QMessageBox::StandardButton r = (QMessageBox::StandardButton)QMessageBox::question(g_MainWindow
	, QString::fromLocal8Bit("��������")
	, QString::fromLocal8Bit("ȷ��Ҫ�����µ�������Ϣ��")
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
