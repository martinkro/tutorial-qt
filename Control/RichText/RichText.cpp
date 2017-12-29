#include "RichText.h"
#include <QPushButton>
#include <QLabel>
#include <QTextDocument>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTextBrowser>
#include <QFile>

#include <iostream>
using namespace std;
class A
{
public:
	void print()
	{
		cout << "A constructor 1" << endl;
	}
};

RichText::RichText(QWidget *parent)
	: QMainWindow(parent)
{
	//ui.setupUi(this);

	QPushButton* switchButton = new QPushButton(tr("Switch"));
	QLabel* messageLabel = new QLabel(tr("message"));
	
	QTextDocument* infoDocument = new QTextDocument(tr("html"));
	//QTextEdit* textEdit = new QTextEdit;
	//textEdit->setDocument(infoDocument);

	QLabel* textBrowser = new QLabel;
	//textBrowser->setDocument(infoDocument);
	//textBrowser->setFrameStyle(QFrame::NoFrame);
	QString info = getHelpInfo();



	textBrowser->setText(info);

	QTextBrowser* major = new QTextBrowser;
	major->setFrameStyle(QFrame::NoFrame);
	QHBoxLayout* layoutText = new QHBoxLayout;
	layoutText->addWidget(major);
	layoutText->addWidget(textBrowser);
	layoutText->setContentsMargins(0, 0, 0, 0);
	layoutText->setSpacing(18);
	

	QVBoxLayout* main = new QVBoxLayout;
	main->addWidget(messageLabel, 0, Qt::AlignHCenter);
	main->addLayout(layoutText, 0);
	//main->addWidget(textEdit, 0, Qt::AlignHCenter);
	main->addWidget(switchButton, 0, Qt::AlignHCenter);
	QWidget* center = new QWidget;
	center->setLayout(main);
	main->setContentsMargins(32, 0, 32, 25);
	setCentralWidget(center);

	textBrowser->setFixedSize(298,400);
	major->setFixedSize(580, 400);

	setFixedSize(960, 600);
}

QString RichText::getHelpInfo()
{
	QFile file("help/multichannel.html");
	QString info;
	if (file.exists())
	{
		if (file.open(QFile::ReadOnly))
		{
			info = file.readAll();
			file.close();
		}
		else
		{
			info =  tr("Open Fail");
		}
	}
	else
	{
		info = tr("Error");
	}
	return info;
}
