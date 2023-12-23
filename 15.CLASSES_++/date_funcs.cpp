#include "date.h"

Date::Date(int year, int month, int day)
	: m_year { year }
	, m_month { month }
	, m_day { day }
{}

void Date::print() const
{
	std::cout << m_year << '/' << m_month << '/' << m_day << '\n';
}
