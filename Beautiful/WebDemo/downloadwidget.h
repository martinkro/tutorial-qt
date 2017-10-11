#ifndef DOWNLOADWIDGET_H
#define DOWNLOADWIDGET_H

#include <QWebEngineDownloadItem>
#include "ui_downloadwidget.h"

#include <QFrame>
#include <QTime>

class QWebEngineDownloadItem;

// Displays one ongoing or finished download (QWebEngineDownloadItem).
class DownloadWidget final : public QFrame, public Ui::DownloadWidget
{
    Q_OBJECT
public:
    // Precondition: The QWebEngineDownloadItem has been accepted.
    explicit DownloadWidget(QWebEngineDownloadItem *download, QWidget *parent = nullptr);

signals:
    // This signal is emitted when the user indicates that they want to remove
    // this download from the downloads list.
    void removeClicked(DownloadWidget *self);

private slots:
    void updateWidget();

private:
    QString withUnit(qreal bytes);

    QWebEngineDownloadItem *m_download;
    QTime m_timeAdded;
};

#endif // DOWNLOADWIDGET_H