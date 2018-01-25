#include "XApplication.h"
#include "XLogger.h"


#include <QFontDatabase>
#include <QStyleFactory>
#include <QTranslator>
#include <QDir>
#include <QDebug>

const QString TranslatorName = "mv_zh.qm";
const QString QssName = "mv.qss";

XApplication::XApplication(int &argc, char **argv) :
	QApplication(argc, argv)
{
	qInstallMessageHandler(XLogger::messageHandler);
	initialize();
}

void XApplication::initialize()
{
	intializeFonts();
	intializeTranslator();
	intializeStyleSheet();

	// ³õÊ¼»¯
	//sSSOLogin->initialize();
	//sQQTicket->initialize();
	//sMTPEngine->initialize();
	//sMTPStatusMgr->initialize();
}

XApplication::~XApplication()
{
	qDebug() << "XApplication destructor";
}

void XApplication::intializeTranslator()
{
	// Translator settings
	bool ret = false;
	translator = new QTranslator(this);
#ifdef QT_DEBUG
	ret = translator->load(TranslatorName);
#else
	ret = translator->load(QString(TranslatorName));
#endif
	if (!ret)
	{
		qCritical() << "Load translator fail";
	}
	ret = installTranslator(translator);
	if (!ret)
	{
		qCritical() << "Install translator fail";
	}
}
void XApplication::intializeStyleSheet()
{
	//QFile test(":/test/test");
	//if (!test.open(QFile::ReadOnly))
	//{
	//	qCritical() << "test not exist";
	//}

	// Qt StyleSheet
	bool ret = false;
#ifdef QT_DEBUG
	QFile file(QssName);
#else
	QFile file(QssName);
#endif
	
	ret = file.open(QFile::ReadOnly);
	if (!ret)
	{
		qCritical() << "Open stylesheet fail";
	}
	else
	{
		setStyleSheet(file.readAll());
		file.close();
	}
	
}
void XApplication::intializeFonts()
{
	QString homeDir = "";
#ifdef QT_DEBUG
	homeDir = QDir::currentPath();
#else
	homeDir = applicationDirPath();
#endif

	// Font settings
	QString yhPath = homeDir + "/fonts/MSYH.TTC";
	QString fontName;
	if (QFile::exists(yhPath))
	{
		int fontId = QFontDatabase::addApplicationFont(homeDir + "/fonts/MSYH.TTC");
		QString fontName = QFontDatabase::applicationFontFamilies(fontId).at(0);
		qDebug() << fontName;
		QFont font(fontName);
		setFont(font);
	}
	else
	{
		qWarning() << "font:" << yhPath << " not exists";
	}
	

	yhPath = homeDir + "/fonts/MSYHBD.TTC";
	if (QFile::exists(yhPath))
	{
		int fontBoldId = QFontDatabase::addApplicationFont(yhPath);
		fontName = QFontDatabase::applicationFontFamilies(fontBoldId).at(0);
		qDebug() << fontName;
	}
	else
	{
		qWarning() << "font:" << yhPath << " not exists";
	}

	
}