#include "basepage.h"

XBasePage::XBasePage(QWidget* parent)
	:QWidget(parent)
{
	this->setStyleSheet("background-color:white; \
				border-width:1px; \
				border-style:solid; \
				border-radius:1px; \
				border-color:black; \
		");
}