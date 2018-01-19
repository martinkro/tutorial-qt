#ifndef XTABLEVIEW_H
#define XTABLEVIEW_H

#include <QTableView>

class XTableView:public QTableView
{
    Q_OBJECT
public:
    explicit XTableView(QWidget* parent = 0);

public:
    QSize minimumSizeHint()const override;
    QSize sizeHint()const override;

protected:
    QSize viewportSizeHint() const override;
    void scrollContentsBy(int dx, int dy)override;
    void updateGeometries()override;

    void showEvent(QShowEvent* e)override;
    void paintEvent(QPaintEvent* e)override;
};

#endif