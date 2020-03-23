#include "StdAfx.h"
#include "CubeSettingsDialogImps.h"

extern ConfigAccesser g_GlobleConfig;

CubeSettingsDialogImps::CubeSettingsDialogImps(void) 
	: m_iMode(-1), m_CheckGroup(new QButtonGroup)
{
	
	m_Setup.setupUi(this);
	m_Setup.buttonBox->button(QDialogButtonBox::Ok)->setText(QString::fromLocal8Bit("确定"));
	m_Setup.buttonBox->button(QDialogButtonBox::Cancel)->setText(QString::fromLocal8Bit("取消"));
	QStringList items;
	items.push_back("500");
	items.push_back("1000");
	items.push_back("1500");
	items.push_back("2000");
	items.push_back("2500");
	items.push_back("3000");
	items.push_back("3500");
	items.push_back("4000");
	items.push_back("4500");
	items.push_back("5000");
	items.push_back("5500");
	items.push_back("6000");
	items.push_back("7000");
	items.push_back("8000");
	items.push_back("9000");
	items.push_back("10000");
	items.push_back("12000");
	items.push_back("14000");
	items.push_back("17000");
	items.push_back("19000");

	m_Setup.HeightcomboBox->addItems(items);
	m_Setup.HeightUpComboBox->addItems(items);
	m_Setup.HeightDownComboBox->addItems(items);

	m_CheckGroup->setExclusive(false);
	m_CheckGroup->addButton(m_Setup.checkBox_1, 0);
	m_CheckGroup->addButton(m_Setup.checkBox_2, 1);
	m_CheckGroup->addButton(m_Setup.checkBox_3, 2);
	m_CheckGroup->addButton(m_Setup.checkBox_4, 3);
	m_CheckGroup->addButton(m_Setup.checkBox_5, 4);
	m_CheckGroup->addButton(m_Setup.checkBox_6, 5);
	m_CheckGroup->addButton(m_Setup.checkBox_7, 6);
	m_CheckGroup->addButton(m_Setup.checkBox_8, 7);
	m_CheckGroup->addButton(m_Setup.checkBox_9, 8);
	m_CheckGroup->addButton(m_Setup.checkBox_10, 9);
	m_CheckGroup->addButton(m_Setup.checkBox_11, 10);
	m_CheckGroup->addButton(m_Setup.checkBox_12, 11);
	m_CheckGroup->addButton(m_Setup.checkBox_13, 12);
	m_CheckGroup->addButton(m_Setup.checkBox_14, 13);
	m_CheckGroup->addButton(m_Setup.checkBox_15, 14);
	m_CheckGroup->addButton(m_Setup.checkBox_16, 15);
}


CubeSettingsDialogImps::~CubeSettingsDialogImps(void)
{
}

void CubeSettingsDialogImps::accept()
{
	cube_data checkCD = g_GlobleConfig.GetCubeFromName(m_Setup.NamelineEdit->text());
	if(m_Setup.NamelineEdit->text().size() <= 0)
	{
		QMessageBox::critical(this, QString::fromLocal8Bit("错误!")
			, QString::fromLocal8Bit("名称不能为空。"));
		return;
	}

	if (checkCD.name.size() > 0)
	{
		QMessageBox::StandardButton iResult = QMessageBox::question(this, QString::fromLocal8Bit("抉择!")
			, QString::fromLocal8Bit("名称为\"") + checkCD.name 
			+  QString::fromLocal8Bit("\"的跟踪框已经存在，是否要修改成当前参数？"));

		if(iResult == QMessageBox::Ok)
		{
			m_iMode = 1;
		}
		
	}

	if(m_iMode != -1)
	{
		cube_data cd;
		cd.height = m_Setup.HeightcomboBox->currentText();
		cd.height_down = m_Setup.HeightDownComboBox->currentText();
		cd.height_up = m_Setup.HeightUpComboBox->currentText();
		cd.left_top_lat = m_Setup.LeftTopLatlineEdit->text().toFloat();
		cd.left_top_lon = m_Setup.LeftTopLonlineEdit->text().toFloat();
		cd.name = m_Setup.NamelineEdit->text();
		cd.right_bottom_lat = m_Setup.RightBottonLatlineEdit->text().toFloat();
		cd.right_bottom_lon = m_Setup.RightBottonLonlineEdit->text().toFloat();
		cd.used = 1;
		for(int i = 0; i < 16; i++)
		{
			QCheckBox* pCheck = dynamic_cast<QCheckBox*>(m_CheckGroup->button(i));

			if(pCheck)
			{
				bool cs = pCheck->isChecked();
				
				if(cs)
				{
					cd.displays.push_back(1);
				}
				else
				{
					cd.displays.push_back(0);
				}
			}
			
		}
		
		g_GlobleConfig.ConfigCubes(m_iMode, m_Setup.NamelineEdit->text(), &cd);
	}

	QDialog::accept();
}

void CubeSettingsDialogImps::slot_buttonClicked( int index )
{
	
}

void CubeSettingsDialogImps::SetValue( const cube_data& cd )
{
	m_Setup.NamelineEdit->setText(cd.name);
	m_Setup.LeftTopLonlineEdit->setText(QString("%1").arg(cd.left_top_lon));
	m_Setup.LeftTopLatlineEdit->setText(QString("%1").arg(cd.left_top_lat));
	m_Setup.RightBottonLonlineEdit->setText(QString("%1").arg(cd.right_bottom_lon));
	m_Setup.RightBottonLatlineEdit->setText(QString("%1").arg(cd.right_bottom_lat));
	int iIndex = m_Setup.HeightcomboBox->findText(cd.height);
	m_Setup.HeightcomboBox->setCurrentIndex(iIndex);

	iIndex = m_Setup.HeightDownComboBox->findText(cd.height_down);
	m_Setup.HeightDownComboBox->setCurrentIndex(iIndex);

	iIndex = m_Setup.HeightUpComboBox->findText(cd.height_up);
	m_Setup.HeightUpComboBox->setCurrentIndex(iIndex);

	for(int i = 0; i < 16; i++)
	{
		QCheckBox* pCheck = dynamic_cast<QCheckBox*>(m_CheckGroup->button(i));

		int iValue = cd.displays.at(i);

		if(iValue == 0)
		{
			pCheck->setCheckState(Qt::Unchecked);
		}
		else if(iValue > 0)
		{
			pCheck->setCheckState(Qt::Checked);
		}
		
	}
}

void CubeSettingsDialogImps::SetCubeName( const QString& name )
{
	static int i = 0;
	static char extname[] = 
	{
		'a','b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'
	};
	m_Setup.NamelineEdit->setText(name + "-" + extname[i]);
	if(i == 25)
	{
		i = 0;
	}
	else
	{
		i++;
	}
}
