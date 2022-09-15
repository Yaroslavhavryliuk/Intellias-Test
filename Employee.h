#pragma once
#include <vector>
#include <string>
#include "Record.h"
#include "HoursOnMonth.h"

std::string monthes[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"}; /// String names of monthes

/**
\brief Class for an employee

This class contains some information about the employee

*/
class Employee
{
public:
	/**
	\brief Method which prints output information to file

	This method takes the name of file for output data and fill it
	*/
	void printWorkHours(std::ofstream& file)
	{
		setWorkHours();
		for (const auto& i : workHours)
		{
			file << name << ';' <<monthes[i.workMonth.month - 1]<< ' ' << i.workMonth.year << ';' << i.hours<<'\n';
		}
	}
	std::string name;  /// Employee name
	std::string address; /// Employee e-mail addres(unique)
	std::vector<Record> emplRecords; /// Records from file about this employee
	std::vector<HoursOnMonth> workHours; /// Monthes in which employee worked and hours of work
private:
	/**
	\brief Method for getting working info

	This method takes info from the record's vector and fill field workHours
	*/
	void setWorkHours()
	{
		for (const auto& i : emplRecords)
		{
			bool newMonth = true;
			for (int j = 0; j < workHours.size(); j++)
			{
				if (i.date.month == workHours[j].workMonth.month && i.date.year == workHours[j].workMonth.year)
				{
					workHours[j].hours += i.logHours;
					newMonth = false;
					break;
				}
			}
			if (newMonth)
			{
				HoursOnMonth hom;
				hom.workMonth = i.date;
				hom.hours = i.logHours;
				workHours.push_back(hom);
			}
		}
	}
	
};