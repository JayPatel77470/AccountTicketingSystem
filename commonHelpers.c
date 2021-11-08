/*
  Assignment #2 Milestone #4
  Full name - Jay Girishkumar Patel
  Student ID number - 158741199
  Seneca email address - jgpatel10@gmail.com
  Course section code - ZCC
*/


#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include "commonHelpers.h"
#include <time.h>
#include <ctype.h>
#include<stdlib.h>
#include"string.h"




// Uses the time.h library to obtain current year information 
// Get the current 4-digit year from the system 
int currentYear(void)
{
	time_t currentTime = time(NULL);
	return localtime(&currentTime)->tm_year + 1900;
}


// As demonstrated in the course notes:
// Empty the standard input buffer 
void clearStandardInputBuffer(void)
{
	while (getchar() != '\n')
	{
		; // On purpose: do nothing 
	}

}

// 1 getinteger
int getInteger(void)
{
	int y;
	int flag = 0;
	char newline = 'x';
	do
	{
		newline = 'x';
		scanf("%d%c", &y, &newline);

		if (newline == '\n')
		{
			flag = 1;
		}
		else
		{
			flag = 0;
			clearStandardInputBuffer();
			printf("ERROR: Value must be an integer: ");
		}
	} while (flag == 0);
	return y;
}

//2 getPositiveInteger
int getPositiveInteger(void)
{
	int y;
	int flag = 0;
	do
	{
		y = getInteger();

		if (y >= 0)
		{
			flag = 1;

		}
		else
		{
			clearStandardInputBuffer();
			printf("ERROR: Value must be a positive integer greater than zero: ");
		}
	} while (flag == 0);

	return y;
}

//3 getDouble
double getDouble(void)
{
	double y;
	int flag = 0;
	char newline = 'x';
	do
	{
		newline = 'x';
		scanf("%lf%c", &y, &newline);

		if (newline == '\n')
		{
			flag = 1;
		}
		else
		{
			clearStandardInputBuffer();
			printf("ERROR: Value must be a double floating-point number: ");
		}
	} while (flag == 0);
	return y;
}

//4 getPositiveDouble
double getPositiveDouble(void)
{
	double y;

	int flag = 0;
	do
	{
		y = getDouble();

		if (y > 0)
		{
			flag = 1;
		}
		else
		{
			printf("ERROR: Value must be a positive double floating-point number: ");
		}
	} while (flag == 0);
	return y;
}

//5 getIntFromRange
int getIntFromRange(int lower, int upper)
{
	int y;
	int flag = 0;

	do
	{
		y = getInteger();

		if (y <= upper && y >= lower)
		{
			flag = 1;
		}
		else
		{
			printf("ERROR: Value must be between %d and %d inclusive: ", lower, upper);

		}

	} while (flag == 0);
	return y;
}

//6 getCharOption
char getCharOption(const char validchar[])
{
	int flag = 0;
	int flag2 = 0;
	char y;
	int i = 0;
	char newline;
	do
	{
		scanf(" %c%c", &y, &newline);
		if (newline == '\n')
		{
			for (i = 0; i < strlen(validchar); i++)
			{

				if (y == validchar[i])
				{
					flag++;
				}
			}

			if (flag >= 1)
			{
				flag2 = 1;
			}
			else
			{
				printf("ERROR: Character must be one of [%s]: ", validchar);
			}
		}
		else
		{
			printf("ERROR: Character must be one of [%s]: ", validchar);
			clearStandardInputBuffer();
		}
	} while (flag2 == 0);
	return y;
}

//7 getCString
void getCString(char* string, int min, int max)
{

	int flag = 0;
	do
	{


		scanf(" %[^\n]s", string);

		if (strlen(string) <= max && strlen(string) >= min)
		{
			flag = 1;
		}
		else
		{
			if (max == min)
			{

				printf("ERROR: String length must be exactly %d chars: ", max);
				clearStandardInputBuffer();
			}
			else if (strlen(string) > max)
			{

				printf("ERROR: String length must be no more than %d chars: ", max);
				clearStandardInputBuffer();
			}
			else
			{

				printf("ERROR: String length must be between %d and %d chars: ", min, max);
				clearStandardInputBuffer();
			}
		}

	} while (flag == 0);
}

//8 getTicketNumber
int getTicketNumber(void)
{
	int flag = 0;
	int num;
	printf("\nEnter the ticket number to view the messages or\n");
	printf("0 to return to previous menu: ");
	do
	{
		scanf("%d", &num);
		if (num < 0)
		{
			printf("ERROR: Value must be positive or zero: ");
		}
		else
		{
			flag = 1;
		}
	} while (flag == 0);
	return num;
}