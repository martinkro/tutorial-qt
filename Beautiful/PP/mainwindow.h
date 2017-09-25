#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include "customcontrol/shadowwindow.h"
#include "titlebar.h"
#include "protectorpage.h"
#include "channelpage.h"
#include "signaturepage.h"
#include "historypage.h"
#include <QSTackedWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPaintEvent>

class MainWindow:public ShadowWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = Q_NULLPTR);
    virtual ~MainWindow();
    
public:
    void closeEvent(QCloseEvent* event);

protected:
	void paintEvent(QPaintEvent* event);
    
private:
	void initUI();
	void initLayoutBottom();
	void initLayoutCenter();
	void initConnect();

private slots:
	void onButtonTabClicked(int index);
	void onButtonSettingsClicked();

private:
	QVBoxLayout* m_layoutMain;
	QHBoxLayout* m_layoutBottom;
	TitleBar* m_titleBar;

	QStackedWidget* m_center;
	ProtectorPage* m_pageProtector;
	ChannelPage* m_pageChannel;
	SignaturePage* m_pageSignature;
	HistoryPage* m_pageHistory;
};


#endif