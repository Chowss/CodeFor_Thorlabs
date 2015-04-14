#pragma once

#include <QTimer>
#include <QApplication>
#include <osgViewer/CompositeViewer>
#include <osgQt/GraphicsWindowQt>

class __declspec(dllexport) ViewerWidget : public QWidget, public osgViewer::CompositeViewer
{
public:
	ViewerWidget();

	QWidget* addViewWidget(osgQt::GraphicsWindowQt* gw);

	osgQt::GraphicsWindowQt* createGraphicsWindow(int x, int y, int w, int h, const std::string& name = "", bool windowDecoration = false);

	virtual void paintEvent(QPaintEvent* event);

	virtual osg::Group* generateAxis();//����������ڵ�

	virtual void setValue(float value);//����Z=kX^2�е�kֵ

protected:
	virtual void redraw(float value);//����Z=kX^2�е�kֵ���²�������ʾ

	QTimer _timer;
	osg::ref_ptr<osg::Group> m_axis;
	osgViewer::View* m_view;
};