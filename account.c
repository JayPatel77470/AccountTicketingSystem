/*
  Assignment #2 Milestone #4
  Full name - Jay Girishkumar Patel
  Student ID number - 158741199
  Seneca email address - jgpatel10@gmail.com
  Course section code - ZCC
*/

#define _CRT_SECURE_NO_WARNINGS
#include "commonHelpers.h"
#include "account.h"
#include "ticket.h"
#include "string.h"

#include "ctype.h"

void getAccount(struct Account* account)
{
	
	printf("Enter the account type (A=Agent | C=Customer): ");
	account->type = getCharOption("AC");
}

void getUserLogin(struct Account* account)
{
	{
		int i;
		int flag;
		printf("User Login Data Input\n");
		printf("----------------------------------------\n");
		do
		{
			char username[100];
			flag = 0;
			printf("Enter user login (10 chars max): ");
			getCString(username, 1, 10);
			for (i = 0; i < strlen(username); i++)
			{
				if (username[i] == ' ')
				{
					flag = 1;
				}
			}
				if (flag == 1)
				{
					printf("ERROR:  The user login must NOT contain whitespace characters.\n");
				}
				else
				{
					strcpy(account->userlog.username, username);
				}		
			
		} while (flag == 1);
	}
	{
		char name[100];
		int i;
		int flag, flag2, flag3, flag4;
		int error;
		printf("Enter the display name (30 chars max): ");
		getCString(name, 1, 30);
		strcpy(account->userlog.name, name);
		do
		{
			char password[20];
			flag = 0;
			flag2 = 0;
			flag3 = 0;
			flag4 = 0;
			error = 0;
			printf("Enter the password (must be 8 chars in length): ");
			getCString(password, 8, 8);
			for (i = 0; i < 8; i++)
			{
				if (isdigit(password[i]))
					flag++;
				if (isupper(password[i]))
					flag2++;
				if (islower(password[i]))
					flag3++;
				if (password[i] == '!' || password[i] == '@' || password[i] == '$' || password[i] == '%' || password[i] == '^' || password[i] == '&' || password[i] == '*' || password[i] == '#')
				{
					flag4++;
				}
			}
			error = (flag < 2 || flag2 < 2 || flag3 < 2 || flag4 < 2);
			if (error != 0)
			{
				printf("SECURITY: Password must contain 2 of each:\n");
				printf("          Digit: 0-9\n");
				printf("          UPPERCASE character\n");
				printf("          lowercase character\n");
				printf("          symbol character: !@#$%%^&*\n");
			}
			else
			{
				strcpy(account->userlog.password, password);
			}
		} while (error != 0); 
	}
	printf("\n");
}

void getDemographic(struct Account* account)
{
	int year;
	year = currentYear();
	int flag = 0;
	printf("Demographic Data Input\n");
	printf("----------------------------------------\n");
	printf("Enter birth year (current age must be between 18 and 110): ");
	do
	{
		flag = 0;
		scanf("%d", &account->demo.birthyear);
		if (account->demo.birthyear < year - 110 || account->demo.birthyear > year - 18)
		{
			printf("ERROR: Value must be between %d and %d inclusive: ", year - 110, year - 18);
			flag = 1;
		}

	} while (flag != 0);
	printf("Enter the household Income: $");
	account->demo.income = getPositiveDouble();
	printf("Enter the country (30 chars max.): ");
	char country[100];
	getCString(country, 1, 30);
	int i;
	for (i = 0; i <= strlen(country); i++)
	{
		if (country[i] >= 97 && country[i] <= 122)
			country[i] = country[i] - 32;
	}
	strcpy(account->demo.country, country);
}

void updateAccount(struct Account* account)
{
	int select;
	int flag;
	do
	{
		flag = 0;
		printf("Account: %05d - Update Options\n", account->number);
		printf("----------------------------------------\n");
		printf("1) Update account type (current value: %c)\n", account->type);
		printf("2) Login\n");
		printf("3) Demographics\n");
		printf("0) Done\n");
		printf("Selection: ");
		select = getIntFromRange(0, 3);
		if (select == 1)
		{
			printf("\n");
			getAccount(account);
		}
		else if (select == 2)
		{
			updateUserLogin(account);
			printf("\n");
		}
		else if (select == 3)
		{
			updateDemographic(account);
			printf("\n");
		}
		else
			flag = 1;
	} while (flag == 0);
}

void updateUserLogin(struct Account* account)
{
	int flag = 0;
	do
	{
		flag = 0;
		int select;
		printf("\n");
		printf("User Login: %s - Update Options\n", account->userlog.username);
		printf("----------------------------------------\n");
		printf("1) Display name (current value: %s)\n", account->userlog.name);
		printf("2) Password\n");
		printf("0) Done\n");
		printf("Selection: ");
		select = getIntFromRange(0, 2);

		if (select == 1)
		{

			printf("\nEnter the display name (30 chars max): ");
			getCString(account->userlog.name, 1, 30);
		}
		else if (select == 2)
		{
			printf("\n");

			int i, flag, flag2, flag3, flag4, error;
			do
			{
				flag = 0;
				flag2 = 0;
				flag3 = 0;
				flag4 = 0;
				error = 0;
				printf("Enter the password (must be 8 chars in length): ");
				getCString(account->userlog.password, 8, 8);
				for (i = 0; i < strlen(account->userlog.password); i++)
				{
					if (isdigit(account->userlog.password[i]))
						flag++;
					if (isupper(account->userlog.password[i]))
						flag2++;
					if (islower(account->userlog.password[i]))
						flag3++;
					if (ispunct(account->userlog.password[i]))
						flag4++;
				}
				error = (flag < 2 || flag2 < 2 || flag3 < 2 || flag4 < 2);
				if (error != 0)
				{
					printf("SECURITY: Password must contain 2 of each:\n");
					printf("          Digit: 0-9\n");
					printf("          UPPERCASE character\n");
					printf("          lowercase character\n");
					printf("          symbol character: !@#$%%^&*\n");
				}
			} while (error != 0);
		}
		else
			flag = 1;
	} while (flag == 0);
}

void updateDemographic(struct Account* account)
{
	int flag = 0;
	do
	{
		flag = 0;
		int select;
		printf("\n");
		printf("Demographic Update Options\n");
		printf("----------------------------------------\n");
		printf("1) Household Income (current value: $%0.2lf)\n", account->demo.income);
		printf("2) Country (current value: %s)\n", account->demo.country);
		printf("0) Done\n");
		printf("Selection: ");
		select = getIntFromRange(0, 2);
		if (select == 1)
		{

			printf("\nEnter the household Income: $");
			account->demo.income = getPositiveDouble();
		}
		else if (select == 2)
		{
			printf("\nEnter the country (30 chars max.): ");
			getCString(account->demo.country, 1, 30);
			int i;
			for (i = 0; i <= strlen(account->demo.country); i++)
			{
				if (account->demo.country[i] >= 97 && account->demo.country[i] <= 122)
					account->demo.country[i] = account->demo.country[i] - 32;
			}
		}
		else
			flag = 1;
	} while (flag == 0);
}

void createAccount(struct Account* accounts, int index, int max)
{
	int highest_acc_no = highestAccountNumber(accounts, max);
	accounts[index].number = highest_acc_no + 1;
	printf("New Account Data (Account#:%d)\n", accounts[index].number);
	printf("----------------------------------------\n");
	getAccount(&accounts[index]);
	printf("\n");
	getUserLogin(&accounts[index]);
	getDemographic(&accounts[index]);
	printf("\n*** New account added! ***\n\n");
}

int highestAccountNumber(struct Account* accounts, int max)
{

	int highest_acc_no;
	int i;
	highest_acc_no = accounts[0].number;
	for (i = 0; i < max; i++)
	{
		if (accounts[i].number > highest_acc_no)
		{
			highest_acc_no = accounts[i].number;
		}
	}
	return highest_acc_no;
}
