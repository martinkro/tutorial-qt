#ifndef MEMORYPAGE_H
#define MEMORYPAGE_H

#include <QWidget>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTableView>
#include <QStandardItemModel>
#include <QSortFilterProxyModel>
#include <QTableWidget>
#include <QCompleter>
#include <QFormLayout>
#include <QGroupBox>
#include <QLabel>
#include <QTimer>

#include "base/CustomControl/customitemmodel.h"
#include "base/CustomControl/nofocusdelegate.h"


class SysUsageTab;
class MemMonitorTab;
class MemProtectionTab;
class ManoMeter;
class RealtimeChart;
class DynamicMemory;
class MemoryProps;

class MemoryPage : public QTabWidget
{
	Q_OBJECT

public:
	MemoryPage(QWidget *parent = 0);
	~MemoryPage(){}
private slots:
	void onChangeTab(int index);

private:
	MemoryPage& operator=(const MemoryPage& obj);
	MemoryPage(const MemoryPage& obj);
private:
	SysUsageTab* m_sysUsage;			// system memory usage
	MemMonitorTab* m_memMonitor;		// runtime memory monitoring
	MemProtectionTab* m_memProtect;		// memory protection
};

//////////////////////////////////////////////////////////////////////////
// Definition of system memory usage class.
class SysUsageTab : public QWidget
{
	Q_OBJECT

public:
	SysUsageTab(QWidget* parent = 0);
	~SysUsageTab();
private:
	SysUsageTab(const SysUsageTab& obj);
	SysUsageTab& operator=(const SysUsageTab& obj);

	void createTableHeaders();
	void fulfillTable();
private:
	QVBoxLayout* m_mainLayout;
	QTableView* m_procList;
	CustomItemModel* m_procModel;
	QSortFilterProxyModel* m_proxy;
	QLineEdit* m_filter;
	QCompleter* m_completer;
	DynamicMemory* m_memory;
	// PageFaultCount, PeakWorkingSetSize, WorkingSetSize, QuotaPeakPagedPoolUsage, QuotaPagedPoolUsage
	// QuotaPeakNonPagedPoolUsage, QuotaNonPagedPoolUsage, PagefileUsage, PeakPagefileUsage
};

//////////////////////////////////////////////////////////////////////////
// Definition of application memory usage class.
class MemMonitorTab : public QWidget
{
	Q_OBJECT

public:
	MemMonitorTab(QWidget* parent = 0);
	~MemMonitorTab();
private:
	MemMonitorTab(const MemMonitorTab& obj);
	MemMonitorTab& operator=(const MemMonitorTab& obj);
private slots:
	void onUpdateTimer();
private:
	QFormLayout* m_formLayout;
	QVBoxLayout* m_mainLayout;
	QHBoxLayout* m_bottomLayout;
	RealtimeChart* m_chart;
	ManoMeter* m_memusage;
	QLabel* m_total_mem;
	QLabel* m_avail_mem;
	QLabel* m_used_mem;
	QGroupBox* m_groupBox;
	QTimer* m_timer;
};

//////////////////////////////////////////////////////////////////////////
// Definition of memory monitoring class.
class MemProtectionTab : public QWidget
{
	Q_OBJECT

public:
	explicit MemProtectionTab(QWidget* parent = 0);
	~MemProtectionTab();
private:
	MemProtectionTab(const MemProtectionTab& obj);
	MemProtectionTab& operator=(const MemProtectionTab& obj);

	void createTableHeaders();
	void fulfillTable();
private:
	// PID, AllocationBase, State, AllocationProtect, BaseAddress, RegionSize, Type, Protect
	QTableView* m_view;
	CustomItemModel* m_model;
	QVBoxLayout* m_layout;
	MemoryProps* m_memproperty;
};

#endif // MEMORYPAGE_H
