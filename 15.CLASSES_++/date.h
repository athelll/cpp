#pragma once
#include <iostream>

class Date
{
private:
	int m_year {};
	int m_month {};
	int m_day {};

public:
	Date(int year, int month, int day);
	void print() const;
};
