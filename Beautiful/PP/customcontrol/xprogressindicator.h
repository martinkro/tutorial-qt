#ifndef XPROGRESS_INDICATOR_H
#define XPROGRESS_INDICATOR_H

#include <QWidget>
#include <QLabel>
#include <QTimer>

class XProgressIndicatorTimer:public QWidget
{
    Q_OBJECT
public:
    explicit XProgressIndicatorTimer(const QString& imagePath, int total,QWidget* parent = Q_NULLPTR);
    virtual ~XProgressIndicatorTimer(){}
    
public:
    void start();
    void stop();
	void setTip(const QString& tip);
    
private:
    void updatePixmap();
private:
    int m_index;
	int m_total;
	QString m_imagePath;
    QTimer* m_timer;
    QLabel* m_labelTip;
    QLabel* m_labelImage;
};


#endif