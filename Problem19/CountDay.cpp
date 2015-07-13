#include <stdio.h>
#include <iostream>
#include <cstring>

const int DAYS_YEAR = 365; // number of days in a standard year
const int DAYS_IN_WEEK = 7;
const int MONTHS_YEAR = 12; // number of months in any year
const int MONTHS[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}; // the days in each month
const int DATE_SIZE_ARRAY = 3; // the length of the date arrays, i.e. YEAR MONTH DAY which is 3
int SUNDAY_ARRAY[3] = {1899, 12, 31}; // this was a sunday
const std::string DAYS_WEEK[7] = {"Sunday", "Monday",
		"Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
/*30 days in April, June, September and November
All the rest have 31
Save for February alone which has 28, and on a leap year 29*/

/*Determines if a year is considered a leap year*/
// a year is considered a leap year if it is evenly divisble by 4.
// however if it is also evenly divisible by 1000, it is only a leap year
// if it is divisible by 400.
bool isLeapYear(int year)
{
	if (year % 4 == 0)
	{
		if (year % 100 == 0 && year % 400 != 0)
		{
			return false;
		}
		return true;
	}
	return false;
}
/* calculates the number of days between the startDate and the endDate*/
int differenceDays(int startDate[], int endDate[])
{
	int count = 0;
	startDate[1] -= 1;
	endDate[1] -= 1;
	int dayDifference = endDate[2] - startDate[2];
	// calculate differences in years, days
	// months need to be counted seperately in a loop because not all months have the same amount of days
	/*count the months*/
	int monthDiffStart = startDate[1];
	int monthDiffEnd = endDate[1];
	// how many months is the start date, end date away from new years.
	for (int i = 0; i < monthDiffStart; i++) // loop through each month in the start year
	{
		count -= MONTHS[i];  // subtract from the count the number of days in that month
	}
	for (int i = 0; i < monthDiffEnd; i++) // loop through each month in the end year
	{
		count += MONTHS[i]; // add to the count the number of days in that month
	}
	for (int i = startDate[0]; i < endDate[0]; i++) // iterate through each year
		// exclusive to the last year because it is not a whole year and its months were calculated separately
	{
		count += 365;
	}
	for (int i = startDate[0]; i <= endDate[0]; i++)
	{
		if (isLeapYear(i)) // if it is a leap year, increment numLeaps
		{
			count++; // add an extra day if it is a leap year
		}
	}
	if (endDate[1] < 2)
	{
		count--; // if on the last year the 29th of february has not been met, then remove
		// that extra day
	}
	count += dayDifference;

	startDate[1] += 1;
	endDate[1] += 1;

	return count;
}
/*method to calculate day of startDate, day of endDate*/
int giveDay(int date[])
{
	int difference = differenceDays(SUNDAY_ARRAY, date);
	// get the difference between the sunday and the specified day

	//int weeks = difference / DAYS_WEEK
	int daysRemainder = difference % DAYS_IN_WEEK;
	// used to calculate the day of the week
	return daysRemainder;
}
/*Calculate the number of sundays that have elapsed*/
int numberSundays(int start[], int end[])
{
	int difference = differenceDays(start, end);
	// get the difference between the days
	int differenceEnd = differenceDays(SUNDAY_ARRAY, end);
	differenceEnd %= DAYS_IN_WEEK; // how many days away is the end date from a sunday
	difference -= differenceEnd; // remove the remainders
	// i.e. ensure that the difference of days starts and ends on a sunday

	return difference / DAYS_IN_WEEK; // return the number of sundays that passed
}
/*Count sunddays that fell on the first of the month*/
int numberFirstSundays(int start[], int end[])
{
	int sundays = 0; // the number of sundays that have passed
	int dateCopy[3] = {start[0], start[1], start[2]};
	for (int i = 0; dateCopy[0] <= end[0]; i++) // for every year between the two dates
	{
		for (int n = 0; n < MONTHS_YEAR; n++) // for every month in the year
		{
			//std::cout << dateCopy[0] << " " << dateCopy[1] << " " << dateCopy[2] << std::endl;
			if (giveDay(dateCopy) == 0) // if the day is a sunday
			{
				if (dateCopy[0] == end[0] && dateCopy[1] > end[1])
				{
					sundays--; // if the year is the same but the month exceeds the end date
					// decrement sundays because we are going to increment sundays later
				}
				sundays++; // increment sundays
			}
			dateCopy[1]++;
			if (dateCopy[1] > 12) // if the month of the year exceeds 12
			{
				dateCopy[1] = 1; // set the month back to january
				dateCopy[0]++; // increase the year
			}
		}
	}
	if (giveDay(end) == 0)
	{
		sundays++; // if the end is a sunday, increment the number of sundays
	}
	return sundays;
}
/* main */
int main()
{
	int startDate[3];
	int endDate[3];
	std::cout << "Enter a start date in the format YEAR MONTH DAY (e.g. 1996 2 3): ";
	std::cin >> startDate[0] >> startDate[1] >> startDate[2];
	std::cout << "Enter an end date in the format YEAR MONTH DAY (e.g. 2014 2 3): ";
	std::cin >> endDate[0] >> endDate[1] >> endDate[2];
	int difference = differenceDays(startDate, endDate);

	std::cout << difference << " days have elapsed between the two dates." << std::endl;
	std::cout << "The start day was a " << DAYS_WEEK[giveDay(startDate)] <<
	", the end day was a " << DAYS_WEEK[giveDay(endDate)] << "." << std::endl;
	std::cout << numberSundays(startDate, endDate) << " Sundays have passed." << std::endl;
	std::cout << numberFirstSundays(startDate, endDate) << " Sundays fell on the first of the month"
	<< " between the two dates." << std::endl;
}
