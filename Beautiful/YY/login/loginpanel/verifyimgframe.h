/****************************************************************************
**
** Copyright (C) 2013 HaiHan.
** All rights reserved.
** Contact: yanhubin@163.com
** Please keep the author contact information.
** 2013-10-30
**
****************************************************************************/
#ifndef VERIFYIMGFRAME_H
#define VERIFYIMGFRAME_H

#include <QFrame>
#include <QGraphicsDropShadowEffect>

namespace Ui {
class VerifyImgFrame;
}

class VerifyImgFrame : public QFrame
{
    Q_OBJECT
    
public:
    explicit VerifyImgFrame(QWidget *parent = 0);
    ~VerifyImgFrame();

    void m_SetCurrentIndex(int index);

signals:
    void verifyEditFinished(bool getVerify, QString verify);
    void clickOk();

private slots:
    void getVerifyImgFinished(const QByteArray imgdata);
    
    void on_ok_clicked();

    void on_cancel_clicked();

    void on_pushButton_clicked();

private:
    Ui::VerifyImgFrame *ui;
};

#endif // VERIFYIMGFRAME_H
