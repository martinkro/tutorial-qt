#include "my360label.h"
#include<QPainter>
myscoreLabel::myscoreLabel(QString pixscore, QWidget*parent) :QLabel(parent)
{
	m_pixscore = QPixmap(pixscore);


}
void myscoreLabel::paintEvent(QPaintEvent *)
{
	QPixmap m_pixscoreborder(":/image/examine_score.png");
	QPainter p(this);
	p.drawPixmap(rect(), m_pixscoreborder);
	p.drawPixmap((width() - m_pixscore.width()) / 2, (height() - m_pixscore.height()) / 2, m_pixscore);

	QFont font;
	font.setPixelSize(14);
	p.setFont(font);
	p.drawText(width() / 2 + m_pixscore.width() / 2 - 5, height() / 2 + m_pixscore.height() / 2 - 5, "·Ö");
}
