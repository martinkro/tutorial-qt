#include "ProtectorPage.h"
#include "TestTableModel.h"
#include "XCheckBoxDelegate.h"
#include "XTreeView.h"
#include "XTableView.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QScrollArea>
#include <QPushButton>
#include <QTableView>
#include <QHeaderView>
#include <QScrollBar>
#include <QDebug>

void verticalResizeTableViewToContents(QTableView *tableView)
{
    qDebug() << "verticalResizeTableViewToContents:" << tableView->height();
    int count = tableView->verticalHeader()->count();
    
    int scrollBarHeight = tableView->horizontalScrollBar()->height();
    if (tableView->horizontalScrollBar()->isHidden())
    {
        scrollBarHeight = 0;
    }
    //scrollBarHeight = 0;
    int horizontalHeaderHeight = tableView->horizontalHeader()->height();
    bool visible = tableView->horizontalHeader()->isVisible();
    bool hidden = tableView->horizontalHeader()->isHidden();
    if (hidden)
    {
        horizontalHeaderHeight = 0;
    }
    int rowTotalHeight = 0;
    for (int i = 0; i < count; ++i) {
        rowTotalHeight += tableView->verticalHeader()->sectionSize(i);
    }

    int height = horizontalHeaderHeight + rowTotalHeight + scrollBarHeight;
    qDebug() << "height:" << height;
    //tableView->setMinimumHeight(height);
    //tableView->setMaximumHeight(height);
}
ProtectorPage::ProtectorPage(QWidget* parent) :
    XBasePage(parent)
{
    QWidget* leftWidget = new QWidget;
    leftWidget->setObjectName("left");

    QScrollArea* scroll = new QScrollArea;
    scroll->setWidgetResizable(true);
    scroll->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));
    QWidget* scrollWidget = new QWidget;
    scrollWidget->setObjectName("scroll");
    

    tableView = new XTableView;
    EncryptFileTableModel* tableModel = new EncryptFileTableModel(this);
    XCheckBoxDelegate* tableDelegate = new XCheckBoxDelegate(this);
    tableView->setItemDelegate(tableDelegate);
    tableView->setModel(tableModel);
    QHeaderView* h = tableView->horizontalHeader();
    tableView->setSizeAdjustPolicy(QTableView::AdjustToContents);
    //h->setResizeMode(QHeaderView::ResizeToContents);
    tableView->resizeRowsToContents();
    tableView->resizeColumnsToContents();
   
    // tableView->setItemDelegateForColumn(0, tableDelegate);
    tableView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    tableView->horizontalScrollBar()->setVisible(false);
    tableView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    tableView->verticalScrollBar()->setVisible(false);
    tableView->verticalHeader()->setVisible(false);
    tableView->horizontalHeader()->setVisible(false);
    tableView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    tableView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    verticalResizeTableViewToContents(tableView);
    //tableView->setShowGrid(false);
    QHBoxLayout* layoutTable = new QHBoxLayout;
    layoutTable->setContentsMargins(20, 0, 20, 0);
    layoutTable->addWidget(tableView);
    qDebug() << "TableView height 1:" << tableView->height();

    QPushButton* test1Button = new QPushButton(tr("Test 1"));

    QVBoxLayout* layoutScroll = new QVBoxLayout;
    layoutScroll->setContentsMargins(20, 20, 20, 20);
    layoutScroll->addWidget(test1Button, 0, Qt::AlignHCenter);
    qDebug() << "TableView height 11:" << tableView->height();
    layoutScroll->addLayout(layoutTable,1);
    qDebug() << "TableView height 22:" << tableView->height();
    scrollWidget->setLayout(layoutScroll);
    qDebug() << "TableView height 33:" << tableView->height();
    scroll->setWidget(scrollWidget);

    qDebug() << "TableView height:" << tableView->height();

    QPushButton* saveButton = new QPushButton(tr("Save"));
    QPushButton* restoreButton = new QPushButton(tr("Restore"));
    QHBoxLayout* layoutButton = new QHBoxLayout;
    layoutButton->addWidget(saveButton);
    layoutButton->addWidget(restoreButton);

    qDebug() << "TableView height:" << tableView->height();

    QVBoxLayout* layoutLeft = new QVBoxLayout;
    layoutLeft->setContentsMargins(30, 0, 30, 0);
    layoutLeft->addWidget(scroll, 1);
    layoutLeft->addLayout(layoutButton, 0);

    leftWidget->setLayout(layoutLeft);

    QWidget* rightWidget = new QWidget;
    rightWidget->setObjectName("right");

    QHBoxLayout* main = new QHBoxLayout;
    main->setContentsMargins(32, 68, 32, 25);
    main->setSpacing(18);
    main->addWidget(leftWidget);
    main->addWidget(rightWidget);
    setLayout(main);

    qDebug() << "TableView height:" << tableView->height();
}

void ProtectorPage::showEvent(QShowEvent* e)
{
    qDebug() << "<show event>TableView height:" << tableView->height();
    qDebug() << "<show event>TableView size:" << tableView->size();
    XBasePage::showEvent(e);
}