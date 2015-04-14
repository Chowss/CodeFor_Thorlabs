#include "mainwidget.h"
#include "ediitwidget.h"
#include "viewerwidget.h"
#include <QHBoxLayout>

MainWidget::MainWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	setWindowTitle(tr("Para-curve Face"));

	//��ʼ�����༭����
	m_editWidget = new EdiitWidget(this);
	m_editWidget->setFixedWidth(m_editWidget->width());
	m_editWidget->setMinimumHeight(m_editWidget->height());

	//��ʼ���Ҳ�3DView
	m_viewer = new ViewerWidget();

	//���뵽��������
	QHBoxLayout *mainLayout = new QHBoxLayout(this);
	mainLayout->addWidget(m_editWidget);
	mainLayout->addWidget(m_viewer);

	//����3DView
	update(false);
}

void MainWidget::update(bool clicked)
{
	(void)clicked;

	//ȡ��Z=kX^2�е�kֵ
	float value = 1.0f;
	if (!m_editWidget->getValue(value))
		return;

	if (m_viewer)
		m_viewer->setValue(value);
}