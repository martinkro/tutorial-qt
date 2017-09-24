#ifndef TITLE_BAR_H
#define TITLE_BAR_H

#include "customcontrol/pushbutton.h"
#include "customcontrol/xtoolbutton.h"

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSignalMapper>
#include <QList>

class TitleBar:public QWidget
{
	Q_OBJECT
public:
	explicit TitleBar(QWidget *parent = Q_NULLPTR);
	virtual ~TitleBar(){}

private:
	void initUI();
	void initConnect();

private slots:
	void onButtonTabClicked(const QString& obj);

signals:
	void buttonMinimizedClicked();
	void buttonCloseClicked();
	void buttonSettingsClicked();
	void buttonTabClicked(int index);
private:
	// top part
	QLabel* m_labelTitle;
	PushButton* m_buttonSettings;
	PushButton* m_buttonMinimized;
	PushButton* m_buttonClose;
	// bottom part
	QList<XToolButton*> m_buttonTabList;
	// layout managers
	QHBoxLayout* m_layoutTop;
	QHBoxLayout* m_layoutBottom;
	QVBoxLayout* m_layoutMain;

	QLabel* m_labelHust;
	QLabel* m_labelSecurity;
	QVBoxLayout* m_layoutLabel;
};

#endif