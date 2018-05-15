/*
* Name : James Young
* ID : 100273383
* Course : CPSC 1160
* Instructor : Bijan Farrahi
* Assignment #4
* Purpose : To display the current time and date

* I pledge that I have completed the programming assignment independently.
* I have not copied the code from a student or any other source.
* I have not given my code to any student

* Date : May 23, 2017
*/
#include <iostream>
#include <time.h>
using namespace std;

/* currDate method
* This method calls the methods to calculate the required values to display the current time
* @param seconds The total seconds since midnight January 1, 1970
* @param month The c-string that holds month's name. Eg. January
* @param day The address of current day (to be calculated)
* @param year The address of the current year (to be calculated)
* @param hour The address of the current hour (to be calculated)
* @param min The address of the current min (to be calculated)
* @param sec The address of the current sec (to be calculated)
*/
void currDate(unsigned seconds, char month[], unsigned &day, unsigned &year, 
	unsigned &hour, unsigned &min, unsigned &sec);
/* calculateYear method
* This method calculates the current year from the total seconds
* @param seconds The total seconds since midnight January 1, 1970
* @param year The address of the current year (to be calculated)
*/
void calculateYear(unsigned seconds, unsigned &year);
/* getDaysSince1970 method
* This method calculates the number of days since midnight Janurary 1 1970
* @param seconds The total seconds since midnight January 1, 1970
* @param numberOfDays The number of days since midnight Janurary 1 1970  (to be calculated)
*/
void getDaysSince1970(unsigned seconds, unsigned &numberOfDays);
/* calculateMonthAndDay method
* This method calculates the current month and day of the current year given the total seconds since 1970 and then displays it
* It also translates the number into the month's name
* Precondition : Month can hold the length of the month's name
* Postcondition : Month is set to the current month's name
* @param seconds The total seconds since midnight January 1, 1970
* @param year The address of the current year (to be calculated)
* @param day The address of the current day (to be calculated)
* @param numberOfDays The number of days since midnight Janurary 1 1970
* @param month The name of the month (to be found)
*/
void calculateMonthAndDay(unsigned seconds, unsigned &year, unsigned &day, char month[], unsigned int numberOfDays);
/* calculateHour method
* This method calculates the current hour from the total seconds
* @param seconds The total seconds since midnight January 1, 1970
* @param hour The address of the current hour (to be calculated)
*/
void calculateHour(unsigned seconds, unsigned &hour);
/* calculateMinute method
* This method calculates the current minute from the total seconds
* @param seconds The total seconds since midnight January 1, 1970
* @param min The address of the current minute (to be calculated)
*/
void calculateMin(unsigned seconds, unsigned &min);
/* calculateSec method
* This method calculates the current seconds from the total seconds
* @param seconds The total seconds since midnight January 1, 1970
* @param sec The address of the current seconds (to be calculated)
*/
void calculateSec(unsigned seconds, unsigned &sec);

int main()
{
	unsigned int seconds, day, year, hour, min, sec;
	const int MAX_SIZE = 100;
	char month[MAX_SIZE] = { 0 };
	//Gets the current time in seconds since midnight January 1, 1970
	int currentSeconds = time(0);

	//Calculate the current time and date
	currDate(currentSeconds, month, day, year,
		hour, min, sec);

	//Display the current time and date
	system("pause");
	return 0;
}

/* currDate method
* This method calls the methods to calculate the required values to display the current time
* @param seconds The total seconds since midnight January 1, 1970
* @param month The c-string that holds month's name. Eg. January
* @param day The address of current day (to be calculated)
* @param year The address of the current year (to be calculated)
* @param hour The address of the current hour (to be calculated)
* @param min The address of the current min (to be calculated)
* @param sec The address of the current sec (to be calculated)
*/
void currDate(unsigned seconds, char month[], unsigned &day, unsigned &year,
	unsigned &hour, unsigned &min, unsigned &sec)
{
	unsigned int numberOfDays;
	//Calculate the current year
	calculateYear(seconds, year);
	getDaysSince1970(seconds, numberOfDays);

	//Calculate the current month
	calculateMonthAndDay(seconds, year, day, month, numberOfDays);


	//Calculate the current hour
	calculateHour(seconds, hour);

	//Calculate the current minute
	calculateMin(seconds, min);

	//Calculate the current seconds
	calculateSec(seconds, sec);
}

/* calculateYear method
* This method calculates the current year from the total seconds
* @param seconds The total seconds since midnight January 1, 1970
* @param year The address of the current year (to be calculated)
*/
void calculateYear(unsigned seconds, unsigned &year)
{
	const int STARTING_YEAR = 1970;
	year = (seconds / 60 / 60 / 24 / 365) + STARTING_YEAR;
}

/* getDaysSince1970 method
* This method calculates the number of days since midnight Janurary 1 1970
* @param seconds The total seconds since midnight January 1, 1970
* @param numberOfDays The number of days since midnight Janurary 1 1970  (to be calculated)
*/
void getDaysSince1970(unsigned seconds, unsigned &numberOfDays)
{
	numberOfDays = seconds / 60 / 60 / 24;
}

/* calculateMonthAndDay method
* This method calculates the current month and day of the current year given the total seconds since 1970 and then displays it
* It also translates the number into the month's name
* Precondition : Month can hold the length of the month's name
* Postcondition : Month is set to the current month's name
* @param seconds The total seconds since midnight January 1, 1970
* @param year The address of the current year (to be calculated)
* @param day The address of the current day (to be calculated)
* @param numberOfDays The number of days since midnight Janurary 1 1970
* @param month The name of the month (to be found)
*** Logic and Algorithm for calculating month and day from :
*** http://howardhinnant.github.io/date_algorithms.html#civil_from_days
*** Modified for the context of this program
*/
void calculateMonthAndDay(unsigned seconds, unsigned &year, unsigned &day, char month[], unsigned int numberOfDays)
{
	//The gregorian calender repeats itself every 400 years
	//Let era = every 400 years the calender repeats itself
	int era, dayOfEra, yearOfEra, dayOfYear, monthNumber;
	//The numberOfDays needs to be shifted to begin from 03/01/2000
	//where 719468 is the number of days since 01/01/1970
	numberOfDays += 719468;
	//Find the era from the shifted total days 
	//number of days in an era is 146097
	era = numberOfDays / 146097;
	//Find the day of the era, numberOfDays - (era * number of days in a era)
	dayOfEra = numberOfDays - (era * 146097);
	//Find the year of the era, first four years of an era + first 100 years of an era + days in era excluding last day / total days in a year
	yearOfEra = (dayOfEra - (dayOfEra / 1460) + (dayOfEra / 36524) - (dayOfEra / 146096)) / 365;
	//Find the day of the current year, subtract dayOfEra from the days that have occurred in all years in this era
	dayOfYear = dayOfEra - (365 * yearOfEra + (yearOfEra / 4) - (yearOfEra / 100));

	//Find the month number of the current year (0, 11)
	monthNumber = (5 * dayOfYear + 2) / 153;
	//Find the day in the month
	day = dayOfYear - (153 * monthNumber + 2) / 5 + 1;

	//Transform the monthNumber into the Gregorian calender equivalent (1, 12)
	monthNumber = monthNumber + (monthNumber < 10 ? 3 : -9);
	switch(monthNumber)
	{
		case 1:
			month = "January";
			break;
		case 2:
			month = "Feburary";
			break;
		case 3:
			month = "March"; 
			break;
		case 4:
			month = "April";
			break;
		case 5:
			month = "May";
			break;
		case 6:
			month = "June";
			break;
		case 7:
			month = "July";
			break;
		case 8:
			month = "August";
			break;
		case 9:
			month = "September";
			break;
		case 10:
			month = "October";
			break;
		case 11:
			month = "November";
			break;
		case 12:
			month = "December";
			break;
		default:
			month = "INVALID_MONTH";
			break;
	}
	//Print out the current time
	cout << "Current date and time is " << month << " " << day << ", " << year;
}
/* calculateHour method
* This method calculates the current hour from the total seconds
* @param seconds The total seconds since midnight January 1, 1970
* @param hour The address of the current hour (to be calculated)
*/
void calculateHour(unsigned seconds, unsigned &hour)
{
	//60 seconds in a minute, 60 minutes in an hour. 24 possible hours.
	hour = (seconds / 60 / 60) % 24;
	cout << " " << hour;
}
/* calculateMinute method
* This method calculates the current minute from the total seconds
* @param seconds The total seconds since midnight January 1, 1970
* @param min The address of the current minute (to be calculated)
*/
void calculateMin(unsigned seconds, unsigned &min)
{
	//60 seconds in a minute. 60 possible minutes.
	min = (seconds / 60) % 60;
	cout << ":" << min;
}
/* calculateSec method
* This method calculates the current seconds from the total seconds
* @param seconds The total seconds since midnight January 1, 1970
* @param sec The address of the current seconds (to be calculated)
*/
void calculateSec(unsigned seconds, unsigned &sec)
{
	//60 possible seconds.
	sec = seconds % 60;
	cout << ":" << sec << " GMT" << endl;
}