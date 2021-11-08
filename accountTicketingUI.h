/*
  Assignment #2 Milestone #4
  Full name - Jay Girishkumar Patel
  Student ID number - 158741199
  Seneca email address - jgpatel10@gmail.com
  Course section code - ZCC
*/
#ifndef ACCOUNTTICKETINGUI_H_
#define ACCOUNTTICKETINGUI_H_
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include "commonHelpers.h"
#include "account.h"
#include "ticket.h"


struct AccountTicketingData
{
	struct Account* accounts;   // array of accounts 
	const int ACCOUNT_MAX_SIZE; // maximum elements for account array 

	struct Ticket* tickets;    // array of tickets 
	const int TICKET_MAX_SIZE; // maximum elements for ticket array 
};


//ApplicationStartup function starts is the entry point of the code.
void applicationStartup(struct AccountTicketingData* act);

//MenuLogin Function prompts the user to either login to the system or exit it
//It returns the integer type selection of the user.
int menuLogin(const struct  AccountTicketingData act[]);

//This function finds the index of the account by using account number
//It returns the integer type index of the account Number
int findAccountIndexByAcctNum(int accNo, struct Account* account, int max, int Z1);

//This function shows multiple options to customer to look through his accounts
void menuCustomer(struct AccountTicketingData* act, const struct Account* acc);

//This function lets the Agent control all the account and tickets
void menuAgent(struct AccountTicketingData* act, const struct Account* acc);

//These are the options provided to the Agent
void agentOption(void);

//These are the options provided to the Customer
void customerOption(void);

//This contains other functions that will help the Agent to remove an any account
void removeAccount(struct AccountTicketingData* act, const struct Account* acc);

//Contains the functions that let the agent modify an aaccout
void modifyAccount(struct AccountTicketingData* act);

//This contains the data towards the end of the session
void sessionEnd(struct AccountTicketingData* act);

//This contains functions that will help the Customer to create a ticket
void createTicket(struct AccountTicketingData* act, const struct Account* acc, int index);

//This contains functions that will let the Customer to manage a ticket
void ManageATicket(struct AccountTicketingData* act, const struct Account* acc);

//It displays Account summary header
void displayAccountSummaryHeader(void);

//It displays Account summary record
void displayAccountSummaryRecord(const struct Account* accounts);

//It displays Account detail header
void displayAccountDetailHeader(void);

//It displays Account detail record
void displayAccountDetailRecord(const struct Account* accounts);

//It displays All Account summary records
void displayAllAccountSummaryRecords(const struct Account account[], int max);

//It displays All Account detail records
void displayAllAccountDetailRecords(const struct Account account[], int max);

//It displays Ticket summary header
void displayTicketSummaryHeader(void);

//It displays Tickets summary record
void displayTicketSummaryRecord(const struct Ticket* ticket);

//It displays Tickets Summary Footer
void displayTicketSummaryFooter(void);

//It displays Ticket Detail Header
void displayTicketDetailHeader(void);

//It displays Ticket detail record
void displayTicketDetailRecord(const struct Ticket* tickets);

//It displays Ticket detail footer
void displayTicketDetailFooter(void);

//It displays tickets
void displayticket(const struct Ticket* tickets);

//It reads the accounts from accounts.txt files
//It returns the number of accounts
int loadAccounts(struct Account account[], int max);

//It reads the tickets from tickets.txt files
//It returns the number of tickets
int loadTickets(struct Ticket tickets[], int max);

//It adds the ticket to tickets_arc.txt
void archiveTickets(struct Ticket ticket);

//It adds the account to accounts.arc.txt
void archiveAccounts(struct Account account);

//It reads the accounts from accounts_arc.txt files 
//It returns number of accounts
int loadArchiveAccounts(int max);

//It reads the accounts from tickets_arc.txt files
//It returns number of tickets
int loadArchiveTickets(int max, int* messageNumber);

//It writes the current values of tickets in tickets.txt
void storeTicket(struct Ticket* tickets, int max);

//It writes the current values of accounts in accounts.txt
void storeAccounts(struct Account* accounts, int max);

//Used to clear buffer and print a line that prompts user to press enter
void pauseExecution(void);
#endif