#include "TestQDateTime.h"
#include <iostream>
#include <QTextStream>
#include <QDate>
#include <QTime>
#include <QDateTime>

#include <ctime>

void QDate_QTime_init()
{
	std::cout << "---Test QDate,QTime init---" << std::endl;
	QTextStream out(stdout);

	QDate dt1(2015, 4, 12);
	out << "The date is " << dt1.toString() << endl;

	QDate dt2;
	dt2.setDate(2015, 3, 3);
	out << "The date is " << dt2.toString() << endl;

	QTime tm1(17, 30, 12, 55);
	out << "The time is " << tm1.toString("hh:mm:ss.zzz") << endl;

	QTime tm2;
	tm2.setHMS(13, 52, 45, 155);
	out << "The time is " << tm2.toString("hh:mm:ss.zzz") << endl;
}

void QDate_QTime_current()
{
	std::cout << "---Test QDate,QTime current---" << std::endl;
	QTextStream out(stdout);

	QDate cd = QDate::currentDate();
	QTime ct = QTime::currentTime();

	out << "Current date is: " << cd.toString() << endl;
	out << "Current time is: " << ct.toString() << endl;
}

void QDate_compare()
{
	std::cout << "---Test QDate compare---" << std::endl;
	QTextStream out(stdout);

	QDate dt1(2015, 4, 5);
	QDate dt2(2014, 4, 5);

	if (dt1 < dt2) {
		out << dt1.toString() << " comes before "
			<< dt2.toString() << endl;
	}
	else {
		out << dt1.toString() << " comes after "
			<< dt2.toString() << endl;
	}
}

void QDate_leapyear()
{
	std::cout << "---Test QDate leap year---" << std::endl;
	QTextStream out(stdout);

	QList<int> years({ 2010, 2011, 2012, 2013, 2014, 2015, 2016 });

	foreach(int year, years) {
		if (QDate::isLeapYear(year)) {
			out << year << " is a leap year" << endl;
		}
		else {
			out << year << " is not a leap year" << endl;
		}
	}
}

void QDate_format()
{
	std::cout << "---Test QDate format---" << std::endl;
	QTextStream out(stdout);

	QDate cd = QDate::currentDate();

	out << "Today is " << cd.toString(Qt::TextDate) << endl;
	out << "Today is " << cd.toString(Qt::ISODate) << endl;
	out << "Today is " << cd.toString(Qt::SystemLocaleShortDate) << endl;
	out << "Today is " << cd.toString(Qt::SystemLocaleLongDate) << endl;
	out << "Today is " << cd.toString(Qt::DefaultLocaleShortDate) << endl;
	out << "Today is " << cd.toString(Qt::DefaultLocaleLongDate) << endl;
	out << "Today is " << cd.toString(Qt::SystemLocaleDate) << endl;
	out << "Today is " << cd.toString(Qt::LocaleDate) << endl;
}

void QDate_custom_format()
{
	std::cout << "---Test QDate custom format---" << std::endl;
	QTextStream out(stdout);

	QDate cd = QDate::currentDate();

	out << "Today is " << cd.toString("yyyy-MM-dd") << endl;
	out << "Today is " << cd.toString("yy/M/dd") << endl;
	out << "Today is " << cd.toString("d. M. yyyy") << endl;
	out << "Today is " << cd.toString("d-MMMM-yyyy") << endl;
}

void QTime_format()
{
	std::cout << "---Test QTime format---" << std::endl;
	QTextStream out(stdout);

	QTime ct = QTime::currentTime();

	out << "The time is " << ct.toString(Qt::TextDate) << endl;
	out << "The time is " << ct.toString(Qt::ISODate) << endl;
	out << "The time is " << ct.toString(Qt::SystemLocaleShortDate) << endl;
	out << "The time is " << ct.toString(Qt::SystemLocaleLongDate) << endl;
	out << "The time is " << ct.toString(Qt::DefaultLocaleShortDate) << endl;
	out << "The time is " << ct.toString(Qt::DefaultLocaleLongDate) << endl;
	out << "The time is " << ct.toString(Qt::SystemLocaleDate) << endl;
	out << "The time is " << ct.toString(Qt::LocaleDate) << endl;
}

void QTime_custom_format()
{
	std::cout << "---Test QTime custom format---" << std::endl;
	QTextStream out(stdout);

	QTime ct = QTime::currentTime();

	out << "The time is " << ct.toString("hh:mm:ss.zzz") << endl;
	out << "The time is " << ct.toString("h:m:s a") << endl;
	out << "The time is " << ct.toString("H:m:s A") << endl;
	out << "The time is " << ct.toString("h:m AP") << endl;

}

void QDate_weekday()
{
	std::cout << "---Test QDate weekday---" << std::endl;
	QTextStream out(stdout);

	QDate cd = QDate::currentDate();
	int wd = cd.dayOfWeek();

	out << "Today is " << QDate::shortDayName(wd) << endl;
	out << "Today is " << QDate::longDayName(wd) << endl;
}

void QDate_numberOfDays()
{
	std::cout << "---Test QDate number of days---" << std::endl;
	QTextStream out(stdout);
	QList<QString> months;

	months.append("January");
	months.append("February");
	months.append("March");
	months.append("April");
	months.append("May");
	months.append("June");
	months.append("July");
	months.append("August");
	months.append("September");
	months.append("October");
	months.append("November");
	months.append("December");

	QDate dt1(2015, 9, 18);
	QDate dt2(2015, 2, 11);
	QDate dt3(2015, 5, 1);
	QDate dt4(2015, 12, 11);
	QDate dt5(2015, 1, 21);

	out << "There are " << dt1.daysInMonth() << " days in "
		<< months.at(dt1.month() - 1) << endl;
	out << "There are " << dt2.daysInMonth() << " days in "
		<< months.at(dt2.month() - 1) << endl;
	out << "There are " << dt3.daysInMonth() << " days in "
		<< months.at(dt3.month() - 1) << endl;
	out << "There are " << dt4.daysInMonth() << " days in "
		<< months.at(dt4.month() - 1) << endl;
	out << "There are " << dt5.daysInMonth() << " days in "
		<< months.at(dt5.month() - 1) << endl;

	out << "There are " << dt1.daysInYear() << " days in year "
		<< QString::number(dt1.year()) << endl;
}

void QDate_validity()
{
	std::cout << "---Test QDate validity---" << std::endl;
	QTextStream out(stdout);

	QList<QDate> dates({ QDate(2015, 5, 11), QDate(2015, 8, 1),
		QDate(2015, 2, 30) });

	for (int i = 0; i < dates.size(); i++) {

		if (dates.at(i).isValid()) {
			out << "Date " << i + 1 << " is a valid date" << endl;
		}
		else {
			out << "Date " << i + 1 << " is not a valid date" << endl;
		}
	}
}

void QDate_daysToFrom()
{
	std::cout << "---Test QDate to or from---" << std::endl;
	QTextStream out(stdout);

	QDate dt(2015, 5, 11);
	QDate nd = dt.addDays(55);

	QDate xmas(2015, 12, 24);

	out << "55 days from " << dt.toString() << " is "
		<< nd.toString() << endl;
	out << "There are " << QDate::currentDate().daysTo(xmas)
		<< " days till Christmas" << endl;
}

void QDateTime_init()
{
	std::cout << "---Test QDateTime init---" << std::endl;
	QTextStream out(stdout);
	QDateTime cdt = QDateTime::currentDateTime();

	out << "The current datetime is " << cdt.toString() << endl;
	out << "The current date is " << cdt.date().toString() << endl;
	out << "The current time is " << cdt.time().toString() << endl;
}



void QDate_julian()
{
	std::cout << "---Test QDate julian time---" << std::endl;
	QTextStream out(stdout);

	QDate cd = QDate::currentDate();

	out << "Gregorian date for today: " << cd.toString(Qt::ISODate) << endl;
	out << "Julian day for today: " << cd.toJulianDay() << endl;
}

void QDate_battle()
{
	std::cout << "---Test QDate julian time 2---" << std::endl;
	QTextStream out(stdout);

	QDate bordate(1812, 9, 7);
	QDate slavdate(1805, 12, 2);

	QDate cd = QDate::currentDate();

	int j_today = cd.toJulianDay();
	int j_borodino = bordate.toJulianDay();
	int j_slavkov = slavdate.toJulianDay();

	out << "Days since Slavkov battle: " << j_today - j_slavkov << endl;
	out << "Days since Borodino battle: " << j_today - j_borodino << endl;
}

void QDateTime_utc()
{
	std::cout << "---Test QDateTime UTC---" << std::endl;
	QTextStream out(stdout);

	QDateTime cdt = QDateTime::currentDateTime();

	out << "Universal datetime: " << cdt.toUTC().toString() << endl;
	out << "Local datetime: " << cdt.toLocalTime().toString() << endl;
}

void QDateTime_unix()
{
	std::cout << "---Test QDateTime unix---" << std::endl;
	QTextStream out(stdout);

	time_t t = time(0);
	out << t << endl;

	QDateTime dt;
	dt.setTime_t(t);
	out << dt.toString() << endl;

	QDateTime cd = QDateTime::currentDateTime();
	out << cd.toTime_t() << endl;
}


void TestQDateTime()
{
	std::cout << "===>Test QDate,QTime,QDateTime ..." << std::endl;
	QDate_QTime_init();
	QDate_QTime_current();
	QDate_compare();
	QDate_format();
	QDate_custom_format();

	QTime_format();
	QTime_custom_format();
	QDate_weekday();
	QDate_numberOfDays();
	QDate_validity();
	QDate_daysToFrom();
	QDateTime_init();
	QDate_julian();
	QDate_battle();
	QDateTime_utc();
	QDateTime_unix();
}