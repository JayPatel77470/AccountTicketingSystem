/*
  Assignment #2 Milestone #4
  Full name - Jay Girishkumar Patel
  Student ID number - 158741199
  Seneca email address - jgpatel10@gmail.com
  Course section code - ZCC
*/

#ifndef ACCOUNT_H_
#define ACCOUNT_H_
#define _CRT_SECURE_NO_WARNINGS

struct Demographic
{
	int birthyear; //Birth year of the customer/agent
	double income; //Income of the customer/agent
	char country[31]; //Country of the customer/agent
}demo;

struct UserLogin
{
	char name[31]; //name of the customer/agent
	char username[11]; //username of the customer/agent
	char password[9]; //password of the account of the customer/agent
}userlog;

struct Account
{
	int number; //Account number
	char type; //Account type, Agent or Customer
	struct UserLogin userlog; //Struct of Userlogin type
	struct Demographic demo; //Struct of Demographic type
};

//Gets the account information of the new account
void getAccount(struct Account* account);

//Gets the login information of the new account
void getUserLogin(struct Account* account);

//Gets the personal information of the user creating new account
void getDemographic(struct Account* account);

//Lets the agent make change in the information of the account
void updateAccount(struct Account* account);

//Lets the agent make change in the information of the userlogin
void updateUserLogin(struct Account* account);

//Lets the agent make the change in the information of the user personal information
void updateDemographic(struct Account* account);

//Contains the functions that let the agent create a new account
void createAccount(struct Account* accounts, int index, int max);

//Gets the highest account number
//It returns the highest account number
int highestAccountNumber(struct Account* accounts, int max);

#endif