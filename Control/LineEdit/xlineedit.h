#pragma once

#include <QLineEdit>
#include <QToolButton>

class XLineEdit : public QLineEdit
{
	Q_OBJECT

public:
	XLineEdit(QWidget *parent = Q_NULLPTR);
	~XLineEdit();

protected:
	void resizeEvent(QResizeEvent *);

	private slots:
	void updateCloseButton(const QString &text);

private:
	QToolButton *clearButton;
};
