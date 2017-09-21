#include "maskmainwidget.h"

maskmainwidget::maskmainwidget(QWidget *parent) : QWidget(parent)
{
	setMaximumSize(900, 600);
	setMinimumSize(900, 600);
	m_upmain = new UpmainWindow(this);
	m_lowmain = new lowMainWindow(this);
	m_upmain->setGeometry(0, 0, m_upmain->width(), m_upmain->height());
	m_lowmain->setGeometry(0, 440, m_lowmain->width(), m_lowmain->height());
}
