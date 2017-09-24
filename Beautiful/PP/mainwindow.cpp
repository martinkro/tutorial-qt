#include "mainwindow.h"
#include <QIcon>
#include <QLabel>
#include <QPixmap>
#include <QDateTime>

const int MAIN_WIDTH = 900;
const int MAIN_HEIGHT = 600;
MainWindow::MainWindow(QWidget* parent)
    :ShadowWindow(parent)
{
	initUI();
	initConnect();
}
    
MainWindow::~MainWindow()
{
}

void MainWindow::closeEvent(QCloseEvent* event)
{
	event->accept();
}

void MainWindow::initUI()
{
	setWindowIcon(QIcon(tr(":/background/logo")));
	setFixedSize(MAIN_WIDTH, MAIN_HEIGHT);

	m_layoutMain = new QVBoxLayout;

	// title widget
	m_titleBar = new TitleBar(this);

	// main area
	initLayoutCenter();

	// status widget
	initLayoutBottom();

	m_layoutMain->addWidget(m_titleBar);
	m_layoutMain->addWidget(m_center);
	m_layoutMain->addLayout(m_layoutBottom);
	m_layoutMain->setSpacing(0);
	m_layoutMain->setContentsMargins(5, 5, 5, 5);
	setLayout(m_layoutMain);
}

void MainWindow::initLayoutCenter()
{
	m_pageProtector = new ProtectorPage;
	m_pageChannel = new ChannelPage;
	m_center = new QStackedWidget;
	m_center->resize(900, 500);
	m_center->setFrameShape(QFrame::NoFrame);
	m_center->addWidget(m_pageProtector);
	m_center->addWidget(m_pageChannel);
}

void MainWindow::initLayoutBottom()
{
	QLabel* labelIcon = new QLabel();
	labelIcon->setPixmap(QPixmap(":/misc/cloud"));
	labelIcon->setFixedSize(QPixmap(":/misc/cloud").size());

	QLabel* labelTime = new QLabel();
	QString currentTime = QDateTime::currentDateTime().toString(tr("yyyy-M-d h:m"));
	QString dt = QString(tr("[Last run]: <b><font color=blue>%1</font></b>")).arg(currentTime);
	labelTime->setText(dt);

	m_layoutBottom = new QHBoxLayout;
	m_layoutBottom->addStretch();
	m_layoutBottom->addWidget(labelIcon, 0, Qt::AlignCenter);
	m_layoutBottom->addWidget(labelTime, 0, Qt::AlignCenter);
	m_layoutBottom->setSpacing(5);
	m_layoutBottom->setContentsMargins(0, 3, 10, 3);

}

void MainWindow::initConnect()
{
	connect(m_titleBar, SIGNAL(buttonMinimizedClicked()), SLOT(showMinimized()));
	connect(m_titleBar, SIGNAL(buttonCloseClicked()), SLOT(close()));
	connect(m_titleBar, SIGNAL(buttonSettingsClicked()), this, SLOT(onButtonSettingsClicked()));
	connect(m_titleBar, SIGNAL(buttonTabClicked(int)), this, SLOT(onButtonTabClicked(int)));
}

void MainWindow::onButtonSettingsClicked()
{

}

void MainWindow::onButtonTabClicked(int index)
{
	int currentIdx = m_center->currentIndex();
	int total = m_center->count();
	if (index < total && index != currentIdx)
	{
		m_center->setCurrentIndex(index);
	}
	
}

void MainWindow::paintEvent(QPaintEvent* event)
{
	// First, we pass the paint event to parent widget to draw window shadow.
	// Then, we do our specific painting stuff.
	ShadowWindow::paintEvent(event);

	// draw the background using the specified image.

	QPainter painter(this);
	painter.setPen(Qt::NoPen);
	painter.setBrush(Qt::white);
	painter.drawPixmap(5, 5, width() - 10, height() - 10, QPixmap(":/background/title_background"));
}