#ifndef ABSTMAINWIDGET_H
#define ABSTMAINWIDGET_H
#include"my360button.h"
#include <QObject>
#include <QWidget>
#include"mainwindowswidlow.h"
#include"mainwindowswidup.h"
class abstmainwidget : public QWidget
{
	Q_OBJECT
public:
	explicit abstmainwidget(QWidget *parent = 0);
	mainwindowswidlow *m_lowwid;
	mainwindowswidup *m_upwid;

	mainwindowswidlow* downwidget() { return m_lowwid; }
	mainwindowswidup * topwidget() { return m_upwid; }

	main3Button*m_btnmini;
	main3Button*m_btnexit;
	main3Button*m_btnfeedback;
	main3Button*m_btnmenu;
	main3Button*m_btnskin;
signals:
};

#endif // ABSTMAINWIDGET_H
