#ifndef MY360LABEL_H
#define MY360LABEL_H

#include <QObject>
#include <QWidget>
#include<QLabel>
class myscoreLabel : public QLabel
{
public:
	myscoreLabel(QString pixscore, QWidget*parent = 0);
protected:
	void paintEvent(QPaintEvent*);
private:
	QPixmap m_pixscore;

};

#endif // MY360LABEL_H
