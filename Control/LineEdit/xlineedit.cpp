#include "xlineedit.h"
#include <QStyle>

// https://web.archive.org/web/20130613105442/http://blog.qt.digia.com/blog/2007/06/06/lineedit-with-a-clear-button
XLineEdit::XLineEdit(QWidget *parent)
	: QLineEdit(parent)
{
	clearButton = new QToolButton(this);
	QPixmap pixmap("fileclose.png");
	clearButton->setIcon(QIcon(pixmap));
	clearButton->setIconSize(pixmap.size());
	clearButton->setCursor(Qt::ArrowCursor);
	clearButton->setStyleSheet("QToolButton { border: none; padding: 0px; }");
	clearButton->hide();
	connect(clearButton, SIGNAL(clicked()), this, SLOT(clear()));
	connect(this, SIGNAL(textChanged(const QString&)), this, SLOT(updateCloseButton(const QString&)));
	int frameWidth = style()->pixelMetric(QStyle::PM_DefaultFrameWidth);
	setStyleSheet(QString("QLineEdit { padding-right: %1px; } ").arg(clearButton->sizeHint().width() + frameWidth + 1));
	QSize msz = minimumSizeHint();
	setMinimumSize(qMax(msz.width(), clearButton->sizeHint().height() + frameWidth * 2 + 2),
		qMax(msz.height(), clearButton->sizeHint().height() + frameWidth * 2 + 2));
}

XLineEdit::~XLineEdit()
{
}

void XLineEdit::resizeEvent(QResizeEvent *)
{
	QSize sz = clearButton->sizeHint();
	int frameWidth = style()->pixelMetric(QStyle::PM_DefaultFrameWidth);
	clearButton->move(rect().right() - frameWidth - sz.width(),
		(rect().bottom() + 1 - sz.height()) / 2);
}

void XLineEdit::updateCloseButton(const QString& text)
{
	clearButton->setVisible(!text.isEmpty());
}
