#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Date.h"
#include "Record.h"
#include "Employee.h"

/**
\brief Function which reads one string 

This function takes the name of file with input data and returns next string from it
*/
std::string readString(std::ifstream& file)
{
    std::vector<char> bytes;
    char byte;
    while (file.get(byte) && byte != ';')
    {
        bytes.push_back(byte);
    }
    std::string retString;
    for (const auto& i : bytes)
    {
        retString += i;
    }
    return retString;
}

/**
\brief Function which reads a date from a file

This function takes the name of file with input data and returns date from it
*/
Date readDate(std::ifstream& file)
{
    char sep;
    Date retDate;
    file >> retDate.year;
    file >> sep;
    file >> retDate.month;
    file >> sep;
    file >> retDate.day;
    file >> sep;
    return retDate;
}

/**
\brief Function which reads one record from a file

This function takes the name of file with input data and returns next record from it
*/
Record readRecord(std::ifstream& file)
{
    Record retRec;
    retRec.name = readString(file);
    retRec.address = readString(file);
    retRec.department = readString(file);
    retRec.position = readString(file);
    retRec.project = readString(file);
    retRec.task = readString(file);
    retRec.date = readDate(file);
    file >> retRec.logHours;
    return retRec;
}


/**
\brief Function which reads all records from file

This function takes the name of file with input data and returns vector of records from it
*/
std::vector<Record> getAllRecords(std::ifstream& file)
{
    std::vector<Record> records;
    while (!file.eof())
    {
        records.push_back(readRecord(file));
    }
    return records;
}

/**
\brief Function which find employees in file

This function takes the vector of records, find every employee and makes a vector of employees
*/
std::vector<Employee> getAllEmployees(std::vector<Record> allRecords)
{
    std::vector<Employee> allEmp;
    for (int i = 0; i < allRecords.size(); i++)
    {
        bool newEmp = true;
        for (int j = 0; j < allEmp.size(); j++)
        {
            if (allRecords[i].address == allEmp[j].address)
            {
                allEmp[j].emplRecords.push_back(allRecords[i]);
                newEmp = false;
                break;
            }
        }
        if (newEmp)
        {
            Employee emp;
            emp.name = allRecords[i].name;
            emp.address = allRecords[i].address;
            emp.emplRecords.push_back(allRecords[i]);
            allEmp.push_back(emp);
        }
    }
    return allEmp;
}


int main()
{
    std::ifstream fileIn;
    fileIn.open("Employees.txt"); /// File with input data
    if (!fileIn)
    {
        std::cerr << "File with input data was not opened";
        return -1;
    }
    std::string firstline;
    std::getline(fileIn, firstline); /// Read column names
    std::vector<Record> recs = getAllRecords(fileIn);
    fileIn.close();
    std::ofstream fileOut;
    fileOut.open("Answer.txt"); /// Open file for output
    if (!fileOut)
    {
        std::cerr << "File for output data can not be opened";
        return -1;
    }
    fileOut << "Name" << ';' << "Month" << ';' << "Total hours" << '\n'; /// Write column names
    std::vector<Employee> allEmp = getAllEmployees(recs);
    for (auto& i : allEmp)
    {
        i.printWorkHours(fileOut);
    }
    fileOut.close();

    return 0;
}


