#include "StdAfx.h"
#include "QwtPlotDialogImps.h"
#include <qwt_plot_panner.h>
#include <qwt_plot_magnifier.h>
#include <qwt_plot_canvas.h>
#include <qwt_column_symbol.h>
#include <qwt_plot_layout.h>
#include <QToolButton>

Plot::Plot( QWidget *parent ): QwtPlot( parent )
{
	setAutoFillBackground( true );
	setPalette( QPalette( QColor( 165, 193, 228 ) ) );
	updateGradient();

	setTitle( "A Simple QwtPlot Demonstration" );
	insertLegend( new QwtLegend(), QwtPlot::RightLegend );

	// axes
	//setAxisTitle( xBottom, "x -->" );
	//setAxisScale( xBottom, 0.0, 10.0 );

	//setAxisTitle( yLeft, "y -->" );
	//setAxisScale( yLeft, -1.0, 1.0 );

	// canvas
	QwtPlotCanvas *canvas = new QwtPlotCanvas();
	canvas->setLineWidth( 1 );
	canvas->setFrameStyle( QFrame::Box | QFrame::Plain );
	canvas->setBorderRadius( 15 );

	QPalette canvasPalette( Qt::white );
	canvasPalette.setColor( QPalette::Foreground, QColor( 133, 190, 232 ) );
	canvas->setPalette( canvasPalette );

	setCanvas( canvas );

	// panning with the left mouse button
	//( void ) new QwtPlotPanner( canvas );

	// zoom in/out with the wheel
	//( void ) new QwtPlotMagnifier( canvas );

}

void Plot::updateGradient()
{
	QPalette pal = palette();

	const QColor buttonColor = pal.color( QPalette::Button );

	QLinearGradient gradient( rect().topLeft(), rect().bottomLeft() );
	gradient.setColorAt( 0.0, Qt::white );
	gradient.setColorAt( 0.7, buttonColor );
	gradient.setColorAt( 1.0, buttonColor );

	pal.setBrush( QPalette::Window, gradient );
	setPalette( pal );
}

void Plot::resizeEvent( QResizeEvent *event )
{
	QwtPlot::resizeEvent( event );

	// Qt 4.7.1: QGradient::StretchToDeviceMode is buggy on X11
	updateGradient();
}

QwtPlotDialogImps::QwtPlotDialogImps(void) : m_Pos(new QwtPlotMarker( "Marker" ))
	, m_Pos2(new QwtPlotMarker( "Marker" ))
{
	m_pMainWindow = new QMainWindow();
	plotWidget = new QWidget(m_pMainWindow);
	m_ClipImageWidget = new QWidget(m_pMainWindow);
	m_SectionImageWidget = new QWidget(m_pMainWindow);

	m_Setup3.setupUi(m_SectionImageWidget);
	m_Setup2.setupUi(m_ClipImageWidget);
	m_Setup.setupUi(plotWidget);

	m_Plot = new Plot(m_Setup.tabWidget);
	m_plot2 = new Plot(m_Setup.tabWidget);
	m_plot3 = new Plot(m_Setup.tabWidget);

	
	m_Setup.tabWidget->addTab(m_Plot, QString::fromLocal8Bit("��ˮ��"));
	m_Setup.tabWidget->addTab(m_plot3, QString::fromLocal8Bit("Һ̬ˮ����"));
	m_Setup.tabWidget->addTab(m_plot2, QString::fromLocal8Bit("�����ʰٷֱ�"));
	m_Setup.tabWidget->addTab(m_ClipImageWidget, QString::fromLocal8Bit("���ٿ��ͼ"));
	m_Setup.tabWidget->addTab(m_SectionImageWidget,  QString::fromLocal8Bit("��������ͼ"));

	m_pMainWindow->setCentralWidget(plotWidget);
	m_Setup.pushButton->setVisible(true);
	m_Setup.pushButton->setText(QString::fromLocal8Bit("��ʾ��ע"));

	m_ClipScene = new QGraphicsScene(m_Setup2.graphicsView);
	m_Setup2.graphicsView->setScene(m_ClipScene);
	//m_Setup2.graphicsView->setTransform(QTransform::fromScale(8, 8));

	m_SectionScene = new QGraphicsScene(m_Setup3.graphicsView);
	m_Setup3.graphicsView->setScene(m_SectionScene);
	//m_Setup3.graphicsView->setTransform(QTransform::fromScale(2, 1));
	//connect(m_Setup2.listWidget, SIGNAL(activated(const QModelIndex&)), SLOT(slot_clip_activated(const QModelIndex&)));
	//connect(m_Setup3.listWidget, SIGNAL(activated(const QModelIndex&)), SLOT(slot_Section_activated(const QModelIndex&)));

	connect(m_Setup2.listWidget, SIGNAL(currentTextChanged(const QString &)), SLOT(slot_clip_currentTextChanged(const QString&)));
	connect(m_Setup3.listWidget, SIGNAL(currentTextChanged(const QString&)), SLOT(slot_Section_currentTextChanged(const QString&)));

	connect(m_Setup.pushButton, SIGNAL(clicked(bool)), SLOT(slot_HideMark(bool)));
}

QwtPlotDialogImps::~QwtPlotDialogImps(void)
{
}

void QwtPlotDialogImps::DrawPlot(const QPolygonF& points, QwtScaleDraw* sc, const QColor& color, const QString& strTitle)
{
	QPointF p = points.at(points.size() - 1);
	int ixMax = p.rx();
	m_Plot->setAxisMaxMajor(QwtPlot::xBottom, ixMax);
	QwtPlotCurve* pCurve = new QwtPlotCurve();
	pCurve->setTitle(strTitle);
	pCurve->setPen( color, 2 ),
		pCurve->setRenderHint( QwtPlotItem::RenderAntialiased, true );

	QwtSymbol *symbol = new QwtSymbol( QwtSymbol::Ellipse,
		QBrush( Qt::yellow ), QPen( Qt::red, 1 ), QSize( 4, 4 ) );

	if(sc > 0)
		m_Plot->setAxisScaleDraw(QwtPlot::xBottom, sc);

	pCurve->setSymbol( symbol );
	pCurve->attach( m_Plot );

	pCurve->setSamples( points );
	
}



void QwtPlotDialogImps::InitPlot()
{
	//m_Setup.qwtPlot;
	int axis1 = QwtPlot::xBottom;
	int axis2 = QwtPlot::yLeft;

	m_Plot->setTitle(QString::fromLocal8Bit("��ˮ��"));
	m_Plot->setCanvasBackground( Qt::white );
	//m_Setup.qwtPlot->setAxisScale( QwtPlot::yLeft, 0.0, 10.0 );
	m_Plot->setAxisTitle(axis1, QString::fromLocal8Bit("ʱ��"));
	m_Plot->setAxisTitle(axis2, QString::fromLocal8Bit("ֵ��"));
	//m_Plot->setAxisMaxMinor(axis1, 0);
	//QwtScaleDiv div;
	
	//div.setInterval(0.1, 0.2);
	//m_Plot->setAxisScaleDiv(axis1, div);
	m_Plot->insertLegend( new QwtLegend() );

	QwtPlotGrid *grid = new QwtPlotGrid();
	//QwtScaleDiv div;
	//div.setInterval(0.001, 0.01);
	//grid->setXDiv(div);
	grid->setMinorPen(QPen(Qt::DotLine));
	grid->attach( m_Plot );

	// panning with the left mouse button
	//QwtPlotPanner* ppp = new QwtPlotPanner( m_Setup.qwtPlot );

	// zoom in/out with the wheel
	//QwtPlotMagnifier* qpm =  new QwtPlotMagnifier( m_Setup.qwtPlot );

}

void QwtPlotDialogImps::AddMark(const QPolygonF& points)
{
	for(int i = 0; i < points.size(); i++)
	{
		QwtPlotMarker *mPos = new QwtPlotMarker( "Marker" );
		mPos->setRenderHint( QwtPlotItem::RenderAntialiased, true );
		//mPos->setItemAttribute( QwtPlotItem::Legend, true );
		//mPos->setSymbol( new QwtSymbol() );
		mPos->setValue(QPointF( points.at(i).x(), points.at(i).y()));
		mPos->setLabel(QString("%1").arg(points.at(i).y()));
		mPos->setLabelAlignment( Qt::AlignRight | Qt::AlignBottom );
		mPos->attach( m_Plot );
	}
}

void QwtPlotDialogImps::Show(const QString& strName, int ix, int iy, int iWidth, int iHeight)
{
	m_pMainWindow->setWindowTitle(strName);
	m_pMainWindow->setGeometry(ix, iy, iWidth, iHeight);
	m_pMainWindow->show();
}

void QwtPlotDialogImps::InitBar()
{
	m_Plot->setAutoFillBackground( true );

	m_Plot->setPalette( Qt::white );
	m_Plot->canvas()->setPalette( QColor( "LemonChiffon" ) );

	m_Plot->setTitle( QString::fromLocal8Bit("�����ʰٷֱ�") );

	m_Plot->setAxisTitle( QwtPlot::yLeft, QString::fromLocal8Bit("�ٷֱ�") );
	m_Plot->setAxisTitle( QwtPlot::xBottom, QString::fromLocal8Bit("ʱ��") );

	d_barChartItem = new QwtPlotMultiBarChart( "Bar Chart " );
	d_barChartItem->setLayoutPolicy( QwtPlotMultiBarChart::AutoAdjustSamples );
	d_barChartItem->setSpacing( 20 );
	d_barChartItem->setMargin( 10 );

	d_barChartItem->attach( m_Plot );

	m_Plot->insertLegend( new QwtLegend() );
	m_Plot->setAutoReplot( true );

	//setOrientation(0);
	d_barChartItem->setStyle( QwtPlotMultiBarChart::Grouped );
}

void QwtPlotDialogImps::DrawBar(QVector<int>& values, QVector<QColor>& colors, QVector<QVector<double>>& rito, QwtScaleDraw* sc)
{
	if(values.size() != colors.size())
	{
		return;
	}

	QList<QwtText> titles;
	for ( int i = 0; i < values.size(); i++ )
	{
		/*QString title1("%1~%2");
		QString title2("%1");

		if(i == 0)
		{
			titles += title2.arg(values.at(i));
		}
		if(i == values.size() - 1)
		{
			titles += title2.arg(values.at(i));
		}
		
		titles += title2.arg(values.at(i - 1)).arg(values.at(i));*/

		QString title("%1");

		titles += title.arg(values.at(i));
	}
	d_barChartItem->setBarTitles( titles );
	d_barChartItem->setLegendIconSize( QSize( 15, 9 ) );

	for ( int i = 0; i < colors.size(); i++ )
	{
		QwtColumnSymbol *symbol = new QwtColumnSymbol( QwtColumnSymbol::Box );
		symbol->setLineWidth( 2 );
		symbol->setFrameStyle( QwtColumnSymbol::Raised );
		symbol->setPalette( QPalette( colors[i] ) );

		d_barChartItem->setSymbol( i, symbol );
	}

	if(sc > 0)
		m_Plot->setAxisScaleDraw(QwtPlot::xBottom, sc);

	d_barChartItem->setSamples( rito );
	
}

void QwtPlotDialogImps::AddBarMark(const QVector<QVector<double>>& rito)
{
	for(int i = 0; i < rito.size(); i++)
	{
		float ix = 1;
		QVector<double> values = rito.at(i);
		int iValueNum = values.size();
		QwtPlotMarker *mPos = new QwtPlotMarker( "Marker" );
		double dy = 0;
		QString text;
		for(int ii = 0; ii < iValueNum; ii++)
		{
			dy = values.at(ii);

			QString str("%1");
			QString dh(",");
			if(ii == 0)
			{
				text += str.arg(values.at(ii));
			}
			else
				text += ("," + str.arg(values.at(ii)));
		}
		
		mPos->setRenderHint( QwtPlotItem::RenderAntialiased, true );
		mPos->setItemAttribute( QwtPlotItem::Margins, true );
		
		mPos->setValue( QPointF(i, dy) );
		mPos->setLabel( QwtText(text));
		mPos->setLabelAlignment( Qt::AlignLeft | Qt::AlignBottom );
		mPos->attach( m_Plot );
	}
	
}

void QwtPlotDialogImps::setOrientation( int orientation )
{
	QwtPlot::Axis axis1, axis2;

	if ( orientation == 0 )
	{
		axis1 = QwtPlot::xBottom;
		axis2 = QwtPlot::yLeft;

		d_barChartItem->setOrientation( Qt::Vertical );
	}
	else
	{
		axis1 = QwtPlot::yLeft;
		axis2 = QwtPlot::xBottom;

		d_barChartItem->setOrientation( Qt::Horizontal );
	}

	m_Plot->setAxisScale( axis1, 0, d_barChartItem->dataSize() - 1, 1.0 );
	m_Plot->setAxisAutoScale( axis2 );

	QwtScaleDraw *scaleDraw1 = m_Plot->axisScaleDraw( axis1 );
	scaleDraw1->enableComponent( QwtScaleDraw::Backbone, false );
	scaleDraw1->enableComponent( QwtScaleDraw::Ticks, false );

	QwtScaleDraw *scaleDraw2 = m_Plot->axisScaleDraw( axis2 );
	scaleDraw2->enableComponent( QwtScaleDraw::Backbone, true );
	scaleDraw2->enableComponent( QwtScaleDraw::Ticks, true );

	m_Plot->plotLayout()->setAlignCanvasToScale( axis1, true );
	m_Plot->plotLayout()->setAlignCanvasToScale( axis2, false );

	m_Plot->plotLayout()->setCanvasMargin( 0 );
	m_Plot->updateCanvasMargins();

	m_Plot->replot();
}

void QwtPlotDialogImps::DrawPlot2(const QPolygonF& points, QwtScaleDraw* sc, const QColor& color, const QString& strTitle)
{
	QPointF p = points.at(points.size() - 1);
	int ixMax = p.rx();
	m_plot2->setAxisMaxMajor(QwtPlot::xBottom, ixMax);
	QwtPlotCurve* pCurve = new QwtPlotCurve();
	pCurve->setTitle(strTitle);
	pCurve->setPen( color, 2 ),
		pCurve->setRenderHint( QwtPlotItem::RenderAntialiased, true );

	QwtSymbol *symbol = new QwtSymbol( QwtSymbol::Ellipse,
		QBrush( Qt::yellow ), QPen( Qt::red, 1 ), QSize( 4, 4 ) );

	if(sc > 0)
		m_plot2->setAxisScaleDraw(QwtPlot::xBottom, sc);

	pCurve->setSymbol( symbol );
	pCurve->attach( m_plot2 );

	pCurve->setSamples( points );

}

void QwtPlotDialogImps::InitPlot2()
{
	//m_Setup.qwtPlot;
	int axis1 = QwtPlot::xBottom;
	int axis2 = QwtPlot::yLeft;

	m_plot2->setTitle(QString::fromLocal8Bit("Һ̬ˮ����"));
	m_plot2->setCanvasBackground( Qt::white );
	//m_Setup.qwtPlot->setAxisScale( QwtPlot::yLeft, 0.0, 10.0 );
	m_plot2->setAxisTitle(axis1, QString::fromLocal8Bit("ʱ��"));
	m_plot2->setAxisTitle(axis2, QString::fromLocal8Bit("ֵ��"));
	//m_Plot->setAxisMaxMinor(axis1, 0);
	//QwtScaleDiv div;

	//div.setInterval(0.1, 0.2);
	//m_Plot->setAxisScaleDiv(axis1, div);
	m_plot2->insertLegend( new QwtLegend() );

	QwtPlotGrid *grid = new QwtPlotGrid();
	//QwtScaleDiv div;
	//div.setInterval(0.001, 0.01);
	//grid->setXDiv(div);
	grid->setMinorPen(QPen(Qt::DotLine));
	grid->attach( m_plot2 );

	// panning with the left mouse button
	//QwtPlotPanner* ppp = new QwtPlotPanner( m_Setup.qwtPlot );

	// zoom in/out with the wheel
	//QwtPlotMagnifier* qpm =  new QwtPlotMagnifier( m_Setup.qwtPlot );

}

void QwtPlotDialogImps::AddMark2(const QPolygonF& points)
{
	for(int i = 0; i < points.size(); i++)
	{
		QwtPlotMarker *mPos = new QwtPlotMarker( "Marker" );
		mPos->setRenderHint( QwtPlotItem::RenderAntialiased, true );
		//mPos->setItemAttribute( QwtPlotItem::Legend, true );
		//mPos->setSymbol( new QwtSymbol() );
		mPos->setValue(QPointF( points.at(i).x(), points.at(i).y()));
		mPos->setLabel(QString("%1").arg(points.at(i).y()));
		mPos->setLabelAlignment( Qt::AlignRight | Qt::AlignBottom );
		mPos->attach( m_plot2 );
	}
}

void QwtPlotDialogImps::InitAll()
{
	int axis1 = QwtPlot::xBottom;
	int axis2 = QwtPlot::yLeft;

	m_Plot->setTitle(QString::fromLocal8Bit("��ˮ��"));
	m_Plot->setCanvasBackground( Qt::white );
	//m_Setup.qwtPlot->setAxisScale( QwtPlot::yLeft, 0.0, 10.0 );
	m_Plot->setAxisTitle(axis1, QString::fromLocal8Bit("ʱ��"));
	m_Plot->setAxisTitle(axis2, QString::fromLocal8Bit("����"));
	
	m_Plot->insertLegend( new QwtLegend() );
	m_Plot->setAxisAutoScale(axis1);
	m_Plot->setAxisAutoScale(axis2);

	QwtPlotGrid *grid = new QwtPlotGrid();
	
	grid->setMinorPen(QPen(Qt::DashDotLine));
	grid->attach( m_Plot );
	/////////////////////////////////////////////////////////////////

	//m_Setup.qwtPlot;
	
	m_plot2->setTitle(QString::fromLocal8Bit("�����ʰٷֱ�"));
	m_plot2->setCanvasBackground( Qt::white );

	//m_Setup.qwtPlot->setAxisScale( QwtPlot::yLeft, 0.0, 10.0 );
	m_plot2->setAxisTitle(axis1, QString::fromLocal8Bit("ʱ��"));
	m_plot2->setAxisTitle(axis2, QString::fromLocal8Bit(" "));
	m_plot2->insertLegend( new QwtLegend() );

	QwtPlotGrid *grid2 = new QwtPlotGrid();
	grid2->setMinorPen(QPen(Qt::DotLine));
	grid2->attach( m_plot2 );
	//////////////////////////////////////////////////////////////////////////
	m_plot3->setTitle(QString::fromLocal8Bit("Һ̬ˮ����"));
	m_plot3->setCanvasBackground( Qt::white );
	
	//m_Setup.qwtPlot->setAxisScale( QwtPlot::yLeft, 0.0, 10.0 );
	m_plot3->setAxisTitle(axis1, QString::fromLocal8Bit("ʱ��"));
	m_plot3->setAxisTitle(axis2, QString::fromLocal8Bit("ǧ��/ƽ����"));
	m_plot3->insertLegend( new QwtLegend() );

	QwtPlotGrid *grid3 = new QwtPlotGrid();
	grid3->setMinorPen(QPen(Qt::DotLine));
	grid3->attach( m_plot3 );

}

void QwtPlotDialogImps::DrawPlot(int tableid, const QString& name, const QPolygonF& points , QwtScaleDraw* sc, const QColor& color, const QString& strTitle, const QVector<float>* pList )
{
	//qDebug()<<color.red()<<","<<color.green()<<","<<color.blue()<<endl;
	Plot* localPlot = 0;
	//QwtPlotMarker *loPos = 0;
	switch(tableid)
	{
	case 0:
		localPlot = m_Plot;
		//loPos = m_Pos;
		break;
	case 1:
		localPlot = m_plot2;
		//loPos = m_Pos2;
		break;
	case 2:
		localPlot = m_plot3;
	default:
		break;

	}

	if(pList)
		m_OtherValue.insert(name, *pList);

	QMap<QString, QwtPlotCurve*>::iterator fined = m_CurveMap.find(name);

	if(fined == m_CurveMap.end())
	{
		QPointF p = points.at(points.size() - 1);
		int ixMax = p.rx();
		localPlot->setAxisMaxMajor(QwtPlot::xBottom, ixMax);
		QwtPlotCurve* pCurve = new QwtPlotCurve();
		pCurve->setTitle(strTitle);
		pCurve->setPen( color, 2 );
		pCurve->setRenderHint( QwtPlotItem::RenderAntialiased, true );

		QwtSymbol *symbol = new QwtSymbol( QwtSymbol::Ellipse,
			QBrush( Qt::yellow ), QPen( Qt::red, 1 ), QSize( 4, 4 ) );

		pCurve->setSymbol( symbol );
		pCurve->attach( localPlot );

		if(sc > 0)
			localPlot->setAxisScaleDraw(QwtPlot::xBottom, sc);
		pCurve->setSamples( points );

		
		m_CurveMap.insert(name, pCurve);
	}
	else
	{
		if(sc > 0)
			localPlot->setAxisScaleDraw(QwtPlot::xBottom, sc);

		fined.value()->setSamples( points );

		if(points.size() > 2)
		{
			localPlot->setAxisScale(QwtPlot::xBottom, points[0].x(), points[points.size() - 1].x(), 10);
		}

		localPlot->replot();
		
		/*localPlot->update();
		localPlot->autoRefresh();
		localPlot->autoReplot();*/

	}

	QString strFormat("%1-%2"), strSetID;
	for(int ito = 0; ito < points.size(); ito++)
	{
		qreal qrx = points.at(ito).x();
		qreal qry = points.at(ito).y();
		strSetID = strFormat.arg(qrx).arg(qry);
		QSet<QString>::iterator findedMark = m_MarkerSet.find(strSetID);

		if(findedMark == m_MarkerSet.end())
		{
			QwtPlotMarker *loPos = 0;
			loPos = new QwtPlotMarker("name");
			loPos->setVisible(false);
			loPos->setRenderHint( QwtPlotItem::RenderAntialiased, true );
			//mPos->setItemAttribute( QwtPlotItem::Legend, true );
			//mPos->setSymbol( new QwtSymbol() );
			loPos->setValue(QPointF(qrx, qry));
			if(pList)
			{
				loPos->setLabel(QString("(%1, %2)").arg(qry).arg(pList->at(ito)));
			}
			else
				loPos->setLabel(QString("%1").arg(qry));

			loPos->setLabelAlignment( Qt::AlignRight | Qt::AlignBottom );
			loPos->attach( localPlot );

			m_MarkerObjectSet.insert(loPos);
			m_MarkerSet.insert(strSetID);
		}
		else
		{
			continue;
		}
	}
	
#if 0
	QMap<QString, QwtPlotMarker*>::iterator finedMarker = m_MarkerMap.find(name);
	QwtPlotMarker *loPos = 0;
	if(finedMarker != m_MarkerMap.end())
	{
		loPos = finedMarker.value();
	}
	else
	{
		loPos = new QwtPlotMarker("name");

		m_MarkerMap.insert(name, loPos);
	}

	if(loPos)
	{
		for(int ito = 0; ito < points.size(); ito++)
		{
			loPos->setRenderHint( QwtPlotItem::RenderAntialiased, true );
			//mPos->setItemAttribute( QwtPlotItem::Legend, true );
			//mPos->setSymbol( new QwtSymbol() );
			loPos->setValue(QPointF( points.at(ito).x(), points.at(ito).y()));
			loPos->setLabel(QString("%1").arg(points.at(ito).y()));
			loPos->setLabelAlignment( Qt::AlignRight | Qt::AlignBottom );
			loPos->attach( localPlot );
		}
	}
#endif
}

void QwtPlotDialogImps::CloseAll()
{
	m_pMainWindow->close();
}
#include <qwt_scale_widget.h>
void QwtPlotDialogImps::slot_CopyToClipBorad(bool)
{
	QString sourceEdit ="";
	QString strFormat = "%1:%2";
	QwtPlot* pPlot = dynamic_cast<QwtPlot*>(m_Setup.tabWidget->currentWidget());
	QwtPlotItemList Item = pPlot->itemList();

	int iItme = Item.size();

	for(int i=0; i < iItme; i++)
	{
		QwtPlotCurve* pQwtPlotCurve = dynamic_cast<QwtPlotCurve*>(Item.at(i));
		if(pQwtPlotCurve)
		{
			size_t si = pQwtPlotCurve->dataSize();
			for(size_t ii = 0; ii < si; ii++)
			{
				QPointF pointf = pQwtPlotCurve->sample(ii);

				DistroScaleDraw* pDSD = dynamic_cast<DistroScaleDraw*>(
					pPlot->axisWidget(QwtPlot::xBottom)->scaleDraw());

				if(!pDSD) break;

				QwtText text = pDSD->label(pointf.x());

				sourceEdit += strFormat.arg(text.text()).arg(pointf.y());

				if(ii != si - 1)
					sourceEdit += ",";
				
				//pQwtPlotCurve->scaleDraw(QwtPlot::xBottom);

			}
		}
	}

	QClipboard *clipboard = QApplication::clipboard();
	clipboard->setText(sourceEdit);
}

void QwtPlotDialogImps::AddClipImage( QImage* pImage, const QString& text )
{
	//pImage->save("D:\\aaa.png");
	m_ClipReslut.insert(text, *pImage);
	QPixmap pixmap;
	pixmap = QPixmap::fromImage(*pImage);
	
	QListWidgetItem* pItem = new QListWidgetItem(text, m_Setup2.listWidget);
	m_Setup2.listWidget->addItem(pItem);

	QGraphicsScene* pScene = m_Setup2.graphicsView->scene();
	pScene->clear();
	pScene->addItem(new QGraphicsPixmapItem(pixmap, 0, pScene));
	//m_Setup3.graphicsView->setTransform(QTransform::fromScale(5, 5));
	//QToolButton* toolButton = new QToolButton(m_ClipImageWidget);
	//toolButton->setIconSize(QSize(120, 120));
	//QPixmap pixmap;
	//pixmap = QPixmap::fromImage(*pImage);
	//QIcon icon(pixmap);
	////icon.actualSize(QSize(120, 120));
	//toolButton->setIcon(icon);
	//toolButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	//toolButton->setText(text);

	//m_Setup2.horizontalLayout->addWidget(toolButton);
}

void QwtPlotDialogImps::AddSectionImage( QImage* pImage, const QString& text )
{
	m_SectionReslut.insert(text, *pImage);
	QPixmap pixmap;
	pixmap = QPixmap::fromImage(*pImage);

	QListWidgetItem* pItem = new QListWidgetItem(text, m_Setup3.listWidget);
	m_Setup3.listWidget->addItem(pItem);

	QGraphicsScene* pScene = m_Setup3.graphicsView->scene();
	pScene->clear();
	pScene->addItem(new QGraphicsPixmapItem(pixmap, 0, pScene));
}

void QwtPlotDialogImps::SaveReuslt( const QString& strPath )
{
	QDir dir(strPath);

	if(!dir.exists())
	{
		dir.mkpath(strPath);
	}

	int iTabCount = m_Setup.tabWidget->count();

	for(int j = 0; j < iTabCount; j++)
	{
		QwtPlot* pPlot = dynamic_cast<QwtPlot*>(m_Setup.tabWidget->widget(j));
		if(pPlot == 0)
		{
			if(j == 3)
			{
				/*QString NewDir = strPath + "\\";
				QDir ImageDir1(NewDir);
				if(!ImageDir1.exists())
				{
				ImageDir1.mkpath(strPath);
				}*/

				QList<QString> keys = m_ClipReslut.keys();
				for(int i = 0; i < keys.size(); i++)
				{
					const QImage* pImage = &(m_ClipReslut.value(keys[i]));
					pImage->save(strPath + "TrackBoxImages" +  keys[i] + ".bmp");
				}
				continue;
			}
			else if(j == 4)
			{
				/*QString NewDir = strPath + "SectionImages\\";
				QDir ImageDir1(NewDir);
				if(!ImageDir1.exists())
				{
				ImageDir1.mkpath(strPath);
				}*/

				QList<QString> keys = m_SectionReslut.keys();
				for(int i = 0; i < keys.size(); i++)
				{
					const QImage* pImage = &(m_SectionReslut.value(keys[i]));
					pImage->save(strPath + "SectionImages" + keys[i] + ".bmp");
				}
				continue;
			}
		}
		QwtPlotItemList Item = pPlot->itemList();

		int iItme = Item.size();
		QString strFileName;
		if(j == 0)
		{
			strFileName = QString::fromLocal8Bit("��ˮ��.txt");
		}
		else if(j == 1)
		{
			strFileName = QString::fromLocal8Bit("Һ̬ˮ����.txt");
		}

		if(j == 0 || j==1 || j==2)
		{
			for(int i=0; i < iItme; i++)
			{
				QwtPlotCurve* pQwtPlotCurve = dynamic_cast<QwtPlotCurve*>(Item.at(i));

				if(pQwtPlotCurve)
				{
					QString strFileAbsoPath = strPath + strFileName;
					if(j == 2)
					{
						QString strNewName = GetCurveName(pQwtPlotCurve);
						strNewName.replace("<", QString::fromLocal8Bit("С��"));

						strFileAbsoPath = strPath + strNewName + ".txt";
					}
					QFile saveFile(strFileAbsoPath);
					if(!saveFile.open(QIODevice::WriteOnly)) continue;
					QTextStream ts(&saveFile);

					size_t si = pQwtPlotCurve->dataSize();
					for(size_t ii = 0; ii < si; ii++)
					{
						QPointF pointf = pQwtPlotCurve->sample(ii);

						DistroScaleDraw* pDSD = dynamic_cast<DistroScaleDraw*>(
							pPlot->axisWidget(QwtPlot::xBottom)->scaleDraw());

						if(!pDSD) break;

						QwtText text = pDSD->label(pointf.x());

						ts<<text.text()<<"  "<<pointf.y()<<"\r\n";
					}

					saveFile.close();
				}
			}
		}

		QwtPlotRenderer renderer;
		/*renderer.setDiscardFlag(QwtPlotRenderer::DiscardNone, true);
		QString suffix = "png";
		bool discardBackground = "png" == suffix || "svg" == suffix ? true : false;
		renderer.setDiscardFlag(QwtPlotRenderer::DiscardBackground, discardBackground);
		renderer.setDiscardFlag(QwtPlotRenderer::DiscardCanvasBackground, discardBackground);
		renderer.setLayoutFlag(QwtPlotRenderer::FrameWithScales, true);*/

		QSize ss = pPlot->size();
		
		QImage image(ss.width(), ss.height(), QImage::Format_ARGB32);
		//image.fill(QColor(255, 255, 255, 255));��ɫ�������
		image.fill(QColor(255, 0, 0, 0));
		QPainter painter( &image );
		renderer.render(pPlot, &painter, QRectF(0.0, 0.0, ss.width(), ss.height()));
		painter.end();

		if(j == 0)
		{
			strFileName = QString::fromLocal8Bit("��ˮ��.png");
		}
		else if(j == 1)
		{
			strFileName = QString::fromLocal8Bit("Һ̬ˮ����.png");
		}
		else if(j == 2)
		{
			strFileName = QString::fromLocal8Bit("�����ʰٷֱ�.png");
		}
		image.save(strPath + strFileName);

		
	}
	
	
}

QString QwtPlotDialogImps::GetCurveName( const QwtPlotCurve* pPC )
{
	QList<QString> keys = m_CurveMap.keys();

	for(int i = 0; i < keys.size(); i++)
	{
		if(m_CurveMap.value(keys[i]) == pPC)
			return keys[i];
	}
	
	return "";
}

void QwtPlotDialogImps::slot_clip_activated( const QModelIndex & index )
{

}

void QwtPlotDialogImps::slot_Section_activated( const QModelIndex & index )
{

}

void QwtPlotDialogImps::slot_clip_currentTextChanged( const QString & currentText )
{
	QMap<QString, QImage>::iterator ifinded = m_ClipReslut.find(currentText);

	if(ifinded == m_ClipReslut.end()) return;
	

	QPixmap pixmap;
	pixmap = QPixmap::fromImage((ifinded.value()));

	QGraphicsScene* pScene = m_Setup2.graphicsView->scene();
	pScene->clear();
	pScene->addItem(new QGraphicsPixmapItem(pixmap, 0, pScene));
}

void QwtPlotDialogImps::slot_Section_currentTextChanged( const QString & currentText )
{
	QMap<QString, QImage>::iterator ifinded = m_SectionReslut.find(currentText);

	if(ifinded == m_ClipReslut.end()) return;


	QPixmap pixmap;
	pixmap = QPixmap::fromImage((ifinded.value()));

	QGraphicsScene* pScene = m_Setup3.graphicsView->scene();
	pScene->clear();
	pScene->addItem(new QGraphicsPixmapItem(pixmap, 0, pScene));
}

void QwtPlotDialogImps::slot_HideMark( bool )
{
	QString sourceEdit ="";
	QString strFormat = "%1:%2";
	
	bool bVis = false;
	if(m_Setup.pushButton->text() == QString::fromLocal8Bit("��ʾ��ע"))
	{
		//��ʾ��ע
		//pPlot->setAxisScaleDraw(QwtPlot::xBottom, sc);
		bVis = true;
		m_Setup.pushButton->setText(QString::fromLocal8Bit("���ر�ע"));
	}
	else
	{
		//pPlot->setAxisScaleDraw(QwtPlot::xBottom, 0);
		bVis = false;
		m_Setup.pushButton->setText(QString::fromLocal8Bit("��ʾ��ע"));
	}

	QSet<QwtPlotMarker*>::iterator be = m_MarkerObjectSet.begin();
	while(m_MarkerObjectSet.end() != be)
	{
		(*be)->setVisible(bVis);
		be++;
	}
	m_Plot->replot();
	m_plot2->replot();
	m_plot3->replot();
}
