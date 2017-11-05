#include "lineedit.h"
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QCompleter>
#include <QStandardItemModel>
#include <qfiledialog.h>

// http://blog.csdn.net/liang19890820/article/details/50357523

LineEdit::LineEdit(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	QHBoxLayout* r1 = new QHBoxLayout;
	QLineEdit* search = new QLineEdit;
	search->setClearButtonEnabled(true);
	search->setPlaceholderText(tr("Search ..."));
	QAction* actionSearch = search->addAction(QIcon("search.png"), QLineEdit::LeadingPosition);
	connect(actionSearch, &QAction::triggered, [=]() {
		QMessageBox::information(NULL, "Title", "Search", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
	});
	r1->addWidget(search);
	r1->addStretch();

	QLineEdit* search1 = new QLineEdit;
	search1->setPlaceholderText(tr("Search ..."));
	QAction* actionSearch1 = search1->addAction(QIcon("search.png"), QLineEdit::TrailingPosition);
	connect(actionSearch1, &QAction::triggered, [=]() {
		QMessageBox::information(NULL, "Title", "Search1", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
	});

	QLineEdit* password = new QLineEdit;
	password->setEchoMode(QLineEdit::EchoMode::Password);

	QLineEdit* filebrowser = new QLineEdit;
	QAction* actionFileBrowser = filebrowser->addAction(QIcon("folder-24px.png"), QLineEdit::TrailingPosition);
	actionFileBrowser->setToolTip(tr("File Open"));
	connect(actionFileBrowser, &QAction::triggered, [=]() {
		QString filename;
		filename = QFileDialog::getOpenFileName(this,
			tr("ѡ��ͼ��"),
			"",
			tr("APK (*.apk)")); //ѡ��·��  
		if (filename.isEmpty())
		{
			return;
		}
		else {
			filebrowser->setText(filename);
		}
	
	});

	email = new QLineEdit;
	email->setPlaceholderText(tr("E-Mail"));
	QStandardItemModel* model = new QStandardItemModel(0, 1, this);
	QCompleter* completer = new QCompleter(model, this);
	email->setCompleter(completer);
	connect(completer, SIGNAL(activated(const QString&)),this, SLOT(onEmailChoosed(const QString&)));
	connect(email, &QLineEdit::textChanged, [=](const QString& str) {
	
		if (str.contains("@")) // ����Ѿ�������@���ţ����Ǿ�ֹͣ��ȫ�ˡ���Ϊ������һ���������ٲ�ȫ����Ҳ�����ˡ� 
		{
			return;
		}
		QStringList strlist;
		strlist << "@163.com" << "@qq.com" << "@gmail.com" << "@hotmail.com" << "@126.com";
		model->removeRows(0, model->rowCount());   // ������Ѿ����ڵ����ݣ���Ȼ�Ļ�ÿ���ı��������������ݣ��������ظ�����
		for (int i = 0; i < strlist.size(); ++i)
		{
			model->insertRow(0);
			model->setData(model->index(0, 0), str + strlist.at(i));
		}
	});


	QVBoxLayout* layoutSearch = new QVBoxLayout;
	layoutSearch->addWidget(search1);
	layoutSearch->addWidget(password);
	layoutSearch->addWidget(filebrowser);
	layoutSearch->addWidget(email);
	QHBoxLayout* r2 = new QHBoxLayout;
	r2->addLayout(layoutSearch);

	QVBoxLayout* main = new QVBoxLayout;
	main->addLayout(r1);
	main->addLayout(r2);
	setLayout(main);
}

void LineEdit::onEmailChoosed(const QString& text){
	email->clear();
	email->setText(text);
}
