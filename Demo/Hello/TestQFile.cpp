#include "TestQFile.h"
#include <QFileInfo>
#include <QTextStream>
#include <QDateTime>
#include <QDir>
#include <QFile>

#include <iostream>

int QFile_filesize(QString filename)
{
	QTextStream out(stdout);
	if (!QFile(filename).exists()) {

		qWarning("The file does not exist");
		return 1;
	}

	QFileInfo fileinfo(filename);

	qint64 size = fileinfo.size();

	QString str = "The size is: %1 bytes";

	out << str.arg(size) << endl;
	return 0;
}

int QFile_readContent(QString filename)
{
	QTextStream out(stdout);

	QFile file("colours");

	if (!file.open(QIODevice::ReadOnly)) {

		qWarning("Cannot open file for reading");
		return 1;
	}

	QTextStream in(&file);

	while (!in.atEnd()) {

		QString line = in.readLine();
		out << line << endl;
	}

	file.close();

	return 0;
}

void QFile_writeContent()
{
	QTextStream out(stdout);

	QString filename = "distros";
	QFile file(filename);

	if (file.open(QIODevice::WriteOnly)) {

		QTextStream out(&file);
		out << "Xubuntu" << endl;
		out << "Arch" << endl;
		out << "Debian" << endl;
		out << "Redhat" << endl;
		out << "Slackware" << endl;

	}
	else {

		qWarning("Could not open file");
	}

	file.close();
}

int QFile_copy(QString source, QString destin)
{
	if (!QFile(source).exists()) {
		qWarning("The source file does not exist");
		return 1;
	}

	QFile::copy(source, destin);
	return 0;
}

void QFileInfo_owner(QString filename)
{
	QTextStream out(stdout);
	QFileInfo fileinfo(filename);

	QString group = fileinfo.group();
	QString owner = fileinfo.owner();

	out << "Group: " << group << endl;
	out << "Owner: " << owner << endl;
}

void QFileInfo_lastread(QString filename)
{
	QTextStream out(stdout);
	QFileInfo fileinfo(filename);

	QDateTime last_rea = fileinfo.lastRead();
	QDateTime last_mod = fileinfo.lastModified();

	out << "Last read: " << last_rea.toString() << endl;
	out << "Last modified: " << last_mod.toString() << endl;
}

void QDir_test()
{
	QTextStream out(stdout);
	QDir dir;

	if (dir.mkdir("mydir")) {
		out << "mydir successfully created" << endl;
	}

	dir.mkdir("mydir2");

	if (dir.exists("mydir2")) {
		dir.rename("mydir2", "newdir");
	}

	dir.mkpath("temp/newdir");
}

void QDir_specialPath()
{
	QTextStream out(stdout);

	out << "Current path:" << QDir::currentPath() << endl;
	out << "Home path:" << QDir::homePath() << endl;
	out << "Temporary path:" << QDir::tempPath() << endl;
	out << "Rooth path:" << QDir::rootPath() << endl;
}

void QFile_path(QString filename)
{
	QTextStream out(stdout);
	QFileInfo fileinfo(filename);

	QString absPath = fileinfo.absoluteFilePath();
	QString baseName = fileinfo.baseName();
	QString compBaseName = fileinfo.completeBaseName();
	QString fileName = fileinfo.fileName();
	QString suffix = fileinfo.suffix();
	QString compSuffix = fileinfo.completeSuffix();

	out << "Absolute file path: " << absPath << endl;
	out << "Base name: " << baseName << endl;
	out << "Complete base name: " << compBaseName << endl;
	out << "File name: " << fileName << endl;
	out << "Suffix: " << suffix << endl;
	out << "Whole suffix: " << compSuffix << endl;
}

void QFile_permissions(QString filename)
{
	QTextStream out(stdout);
	QFile::Permissions ps = QFile::permissions(filename);

	QString fper;

	if (ps & QFile::ReadOwner) {
		fper.append('r');
	}
	else {
		fper.append('-');
	}

	if (ps & QFile::WriteOwner) {
		fper.append('w');
	}
	else {
		fper.append('-');
	}

	if (ps & QFile::ExeOwner) {
		fper.append('x');
	}
	else {
		fper.append('-');
	}

	if (ps & QFile::ReadGroup) {
		fper.append('r');
	}
	else {
		fper.append('-');
	}

	if (ps & QFile::WriteGroup) {
		fper.append('w');
	}
	else {
		fper.append('-');
	}

	if (ps & QFile::ExeGroup) {
		fper.append('x');
	}
	else {
		fper.append('-');
	}

	if (ps & QFile::ReadOther) {
		fper.append('r');
	}
	else {
		fper.append('-');
	}

	if (ps & QFile::WriteOther) {
		fper.append('w');
	}
	else {
		fper.append('-');
	}

	if (ps & QFile::ExeOther) {
		fper.append('x');
	}
	else {
		fper.append('-');
	}

	out << fper << endl;
}

int QDir_listContent(QString directory)
{
	QTextStream out(stdout);
	QDir dir(directory);

	if (!dir.exists()) {
		qWarning("The directory does not exist");
		return 1;
	}

	dir.setFilter(QDir::Files | QDir::AllDirs);
	dir.setSorting(QDir::Size | QDir::Reversed);

	QFileInfoList list = dir.entryInfoList();

	int max_size = 0;

	foreach(QFileInfo finfo, list) {

		QString name = finfo.fileName();
		int size = name.size();

		if (size > max_size) {

			max_size = size;
		}
	}

	int len = max_size + 2;

	out << QString("Filename").leftJustified(len).append("Bytes") << endl;

	for (int i = 0; i < list.size(); ++i) {

		QFileInfo fileInfo = list.at(i);
		QString str = fileInfo.fileName().leftJustified(len);
		str.append(QString("%1").arg(fileInfo.size()));
		out << str << endl;
	}

	return 0;
}

void TestQFileAndQDir()
{
	std::cout << "===>Test QContainers ..." << std::endl;
	QDir_specialPath();
}