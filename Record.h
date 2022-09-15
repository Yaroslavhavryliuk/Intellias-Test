#pragma once
#include <string>
#include "Date.h"

/**
\brief Struct for a record from file

This struct is to contain all the information from the record and separate it
*/
struct Record
{
	std::string name;
	std::string address;
	std::string department;
	std::string position;
	std::string project;
	std::string task;
	Date date;
	int logHours;
};