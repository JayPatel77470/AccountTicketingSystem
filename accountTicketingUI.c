/*
  Assignment #2 Milestone #4
  Full name - Jay Girishkumar Patel
  Student ID number - 158741199
  Seneca email address - jgpatel10@gmail.com
  Course section code - ZCC
*/
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include "accountTicketingUI.h"
#include "account.h"
#include "commonHelpers.h"
#include "ticket.h"
#include "string.h"
#include <ctype.h>
#define SIZE 5



void applicationStartup(struct AccountTicketingData* act)
{
	int Z;
	int flag = 0;
	while (flag == 0)
	{
		do
		{
			Z = 0;
			Z = menuLogin(act);
			if (Z == -2)
			{
				printf("\nERROR:  Login failed!\n\n");
				clearStandardInputBuffer();
				pauseExecution();

			}
		} while (Z == -2);

		if (Z < 0)
		{
			printf("\n==============================================\n");
			printf("Account Ticketing System - Terminated\n");
			printf("==============================================\n");
			flag = 1;
		}
		else
		{
			if (act->accounts[Z].type == 'C')
			{
				printf("\n");
				menuCustomer(act, &act->accounts[Z]);
			}

			else
			{
				printf("\n");
				menuAgent(act, &act->accounts[Z]);
			}
		}
	}
}

int menuLogin(const struct  AccountTicketingData act[])
{
	int select;
	int number;
	char login[20];
	char password[20];
	int flag = 0;
	int y = 3;
	int x;
	int Z = 0;
	while (flag == 0)
	{

		printf("==============================================\n");
		printf("Account Ticketing System - Login\n");
		printf("==============================================\n");
		printf("1) Login to the system\n");
		printf("0) Exit application\n");
		printf("----------------------------------------------\n");
		printf("\n");
		printf("Selection: ");

		select = getIntFromRange(0, 1);
		if (select == 1)
		{
			do
			{

				printf("\nEnter the account#: ");
				number = getInteger();
				printf("User Login    : ");
				getCString(login, 1, 20);
				printf("Password      : ");
				getCString(password, 1, 20);
				Z = findAccountIndexByAcctNum(number, act->accounts, act->ACCOUNT_MAX_SIZE, Z);

				if (strcmp(login, act->accounts[Z].userlog.username) == 0 && strcmp(password, act->accounts[Z].userlog.password) == 0)
				{
					flag = 1;
				}
				else
				{
					y--;
					printf("INVALID user login/password combination! [attempts remaining:%d]\n", y);
					if (y == 0)
					{
						flag = 1;
						Z = -2;
					}
				}
			} while (flag == 0);

		}
		else
		{
			printf("\nAre you sure you want to exit? ([Y]es|[N]o): ");
			x = getCharOption("yYnN");
			if (x == 'n' || x == 'N')
			{
				printf("\n");
			}
			else
			{
				Z = -1;
				flag = 1;
			}
		}

	}
	return Z;
}

int findAccountIndexByAcctNum(int accNo, struct Account* account, int max, int Z1)
{

	int i = 0;
	for (i = 0; i < max; i++)
	{
		if (accNo == account[i].number)
		{
			Z1 = i;
			break;
		}

		else
		{
			Z1 = -1;
		}

	}
	return Z1;
}

void menuCustomer(struct AccountTicketingData* act, const struct Account* acc)
{

	int flag = 0;
	loadTickets(act->tickets, act->TICKET_MAX_SIZE);
	while (flag == 0)
	{
		int select;
		int i;
		int N = 0;
		int size = 0;
		for (i = 0; i < act->TICKET_MAX_SIZE; i++)
		{
			if (act->tickets[i].ticketID > 0)
			{

				size++;
			}
			else
			{
				N = i;
			}
		}
		printf("CUSTOMER: %s (%d)\n", acc->userlog.name, acc->number);
		customerOption();
		printf("\nSelection: ");
		select = getIntFromRange(0, 4);

		switch (select)
		{
		case 1:
		{
			printf("\n");
			displayAccountDetailHeader();
			displayAccountDetailRecord(acc);
			printf("\n");
			pauseExecution();
		}
		break;
		case 2:
		{
			if (size < act->TICKET_MAX_SIZE)
			{
				createTicket(act, acc, N);
			}
			else
			{
				printf("\nERROR: Ticket listing is FULL, call ITS Support!\n\n");
				pauseExecution();
			}

		}
		break;
		case 3:
		{
			modifyTicket(act->tickets, act->TICKET_MAX_SIZE, acc);
		}
		break;
		case 4:
		{
			myTickets(act->tickets, act->TICKET_MAX_SIZE, acc);
		}
		break;
		case 0:
		{
			storeTicket(act->tickets, size);
			printf("\nSaving session modifications...\n");
			printf("   %d tickets saved.\n", size);
			printf("### LOGGED OUT ###\n\n");
			flag = 1;
		}
		break;
		}
	}
}

void menuAgent(struct AccountTicketingData* act, const struct Account* acc)
{
	int select;
	int flag = 0;
	loadTickets(act->tickets, act->TICKET_MAX_SIZE);
	loadAccounts(act->accounts, act->ACCOUNT_MAX_SIZE);
	while (flag == 0)
	{
		int size = 0;
		int N = 0;
		int i;
		for (i = 0; i < act->ACCOUNT_MAX_SIZE; i++)
		{
			if (act->accounts[i].number > 0)
			{

				size++;
			}
			else
			{
				N = i;
			}
		}
		printf("AGENT: %s (%d)\n", acc->userlog.name, acc->number);
		agentOption();
		printf("\n");
		printf("Selection: ");
		select = getIntFromRange(0, 12);
		printf("\n");

		switch (select)
		{
		case 1:
		{
			if (size < act->ACCOUNT_MAX_SIZE)
			{
				createAccount(act->accounts, N, act->ACCOUNT_MAX_SIZE);
				pauseExecution();
				printf("\n");
			}
			else
			{
				printf("ERROR: Account listing is FULL, call ITS Support!\n\n");
				pauseExecution();
			}
		}
		break;
		case 2:
		{
			modifyAccount(act);
		}
		break;
		case 3:
		{
			removeAccount(act, acc);
		}
		break;
		case 4:
		{
			displayAllAccountSummaryRecords(act->accounts, act->ACCOUNT_MAX_SIZE);
			pauseExecution();
		}
		break;
		case 5:
		{
			displayAllAccountDetailRecords(act->accounts, act->ACCOUNT_MAX_SIZE);
			pauseExecution();
		}
		break;
		case 6:
		{
			NewTickets(act->tickets, act->TICKET_MAX_SIZE);
		}
		break;
		case 7:
		{
			ActiveTickets(act->tickets, act->TICKET_MAX_SIZE);
		}
		break;
		case 8:
		{
			CloseTickets(act->tickets, act->TICKET_MAX_SIZE);
		}
		break;
		case 9:
		{
			ManageATicket(act, acc);
		}
		break;

		case 10:
		{
			ArchiveClosedTickets(act->tickets, act->TICKET_MAX_SIZE);
			pauseExecution();
		}break;

		case 11:
		{
			int f = loadArchiveAccounts(act->ACCOUNT_MAX_SIZE);
			printf("There are %d account(s) currently archived.\n\n", f);
			pauseExecution();
		}break;

		case 12:
		{
			int n = 0;
			int f = loadArchiveTickets(act->TICKET_MAX_SIZE, &n);
			printf("There are %d ticket(s) and a total of %d message(s) archived.\n\n", f, n);
			pauseExecution();
		}break;

		case 0:
		{
			sessionEnd(act);
			flag = 1;
		}
		break;
		}
	}
}

void agentOption(void)
{
	printf("==============================================\n");
	printf("Account Ticketing System - Agent Menu\n");
	printf("==============================================\n");
	printf(" 1) Add a new account\n");
	printf(" 2) Modify an existing account\n");
	printf(" 3) Remove an account\n");
	printf(" 4) List accounts: summary view\n");
	printf(" 5) List accounts: detailed view\n");
	printf("----------------------------------------------\n");
	printf(" 6) List new tickets\n");
	printf(" 7) List active tickets\n");
	printf(" 8) List closed tickets\n");
	printf(" 9) Manage a ticket\n");
	printf("10) Archive closed tickets\n");
	printf("----------------------------------------------\n");
	printf("11) View archived account statistics\n");
	printf("12) View archived tickets statistics\n");
	printf("----------------------------------------------\n");
	printf("0) Logout\n");
}

void customerOption(void)
{
	printf("==============================================\n");
	printf("Customer Main Menu\n");
	printf("==============================================\n");
	printf("1) View your account detail\n");
	printf("2) Create a new ticket\n");
	printf("3) Modify an active ticket\n");
	printf("4) List my tickets\n");
	printf("----------------------------------------------\n");
	printf("0) Logout\n");
}

void removeAccount(struct AccountTicketingData* act, const struct Account* acc)
{
	int accnumber;
	printf("Enter the account#: ");
	accnumber = getInteger();
	if (acc->number == accnumber)
	{
		printf("\nERROR: You can't remove your own account!\n\n");
		clearStandardInputBuffer();
		pauseExecution();
	}
	else
	{
		int Z = 0;
		Z = findAccountIndexByAcctNum(accnumber, act->accounts, act->ACCOUNT_MAX_SIZE, Z);
		int i = 0;
		int x;
		if (Z >= 0)
		{
			displayAccountDetailHeader();
			displayAccountDetailRecord(&act->accounts[Z]);
			printf("\nAre you sure you want to remove this record? ([Y]es|[N]o): ");
			x = getCharOption("YN");
			if (x == 'N')
			{
				printf("\n*** No changes made! ***\n\n");
				clearStandardInputBuffer();
				pauseExecution();
			}
			else
			{

				for (i = 0; i < act->TICKET_MAX_SIZE; i++)
				{
					if (act->accounts[Z].number == act->tickets[i].acc_number)
					{
						if (act->tickets[i].status == 0 && act->tickets[i].ticketID > 0)
						{
							archiveTickets(act->tickets[i]);
							act->tickets[i].ticketID = 0;

						}
						else if (act->tickets[i].status == 1)
						{
							act->tickets[i].ticketID = 0;
							act->tickets[i].acc_number = 0;
						}

					}
				}
				archiveAccounts(act->accounts[Z]);
				act->accounts[Z].number = 0;
				printf("\n*** Account Removed! ***\n\n");
			}
		}
		pauseExecution();
	}
}

void modifyAccount(struct AccountTicketingData* act)
{
	int accnumber;
	int Z = 0;
	printf("Enter the account#: ");
	accnumber = getInteger();
	Z = findAccountIndexByAcctNum(accnumber, act->accounts, act->ACCOUNT_MAX_SIZE, Z);
	if (Z >= 0)
	{
		printf("\n");
		updateAccount(&act->accounts[Z]);
		printf("\n");
	}
}

void sessionEnd(struct AccountTicketingData* act)
{
	int sizeticket = 0;
	int sizeAccount = 0;
	int i;
	for (i = 0; i < act->ACCOUNT_MAX_SIZE; i++)
	{
		if (act->accounts[i].number > 0)
		{
			sizeAccount++;
		}
	}
	for (i = 0; i < act->TICKET_MAX_SIZE; i++)
	{
		if (act->tickets[i].ticketID > 0)
		{
			sizeticket++;
		}
	}
	printf("Saving session modifications...\n");
	printf("%d account saved. %d tickets saved.\n", sizeAccount, sizeticket);
	storeTicket(act->tickets, act->TICKET_MAX_SIZE);
	storeAccounts(act->accounts, act->ACCOUNT_MAX_SIZE);
	printf("### LOGGED OUT ###\n\n");
}

void createTicket(struct AccountTicketingData* act, const struct Account* acc, int index)
{
	int newTicket = highestTicketNumber(act->tickets, act->TICKET_MAX_SIZE);
	act->tickets[index].ticketID = newTicket + 1;
	getTicket(&act->tickets[index]);
	act->tickets[index].acc_number = acc->number;
	strcpy(act->tickets[index].message[act->tickets[index].msg_number - 1].name, acc->userlog.name);
	clearStandardInputBuffer();
	pauseExecution();
}

void ManageATicket(struct AccountTicketingData* act, const struct Account* acc)
{
	int num, i;
	printf("Enter ticket number: ");
	scanf("%d", &num);
	for (i = 0; i < act->TICKET_MAX_SIZE; i++)
	{
		if (num == act->tickets[i].ticketID)
		{
			manageTicket(&act->tickets[i], &acc->userlog);
		}
	}
}

void displayAccountSummaryHeader(void)
{
	printf("Acct# Acct.Type Birth\n");
	printf("----- --------- -----\n");
}

void displayAccountSummaryRecord(const struct Account* accounts)
{
	printf("%05d %-9s %5d\n", accounts->number, accounts->type == 'A' ? "AGENT" : "CUSTOMER", accounts->demo.birthyear);
}

void displayAccountDetailHeader(void)
{
	printf("Acct# Acct.Type Birth Income      Country    Disp.Name       Login      Password\n");
	printf("----- --------- ----- ----------- ---------- --------------- ---------- --------\n");
}

void displayAccountDetailRecord(const struct Account* accounts)
{
	int i = 0;
	char password[9];
	for (i = 0; i < 9; i++)
	{
		password[i] = accounts->userlog.password[i];
	}
	for (i = 1; i < 9; i += 2)
	{
		password[i] = '*';
	}


	printf("%05d %-9s %5d $%10.2lf %-10s %-15s %-10s %-8s\n", accounts->number, accounts->type == 'A' ? "AGENT" : "CUSTOMER", accounts->demo.birthyear, accounts->demo.income, accounts->demo.country, accounts->userlog.name, accounts->userlog.username, password);
}

void displayAllAccountSummaryRecords(const struct Account account[], int max)
{
	int i;

	displayAccountSummaryHeader();
	for (i = 0; i <= max; i++)
	{
		if (account[i].number > 0)
		{
			displayAccountSummaryRecord(&account[i]);
		}
	}
	printf("\n");
}

void displayAllAccountDetailRecords(const struct Account account[], int max)
{
	int i;

	displayAccountDetailHeader();
	for (i = 0; i <= max; i++)
	{
		if (account[i].number > 0)
		{
			displayAccountDetailRecord(&account[i]);
		}
	}
	printf("\n");
}

void displayTicketSummaryHeader(void)
{
	printf("------ ------ ------------------------------ --------\n");
	printf("Ticket Status Subject                        Messages\n");
	printf("------ ------ ------------------------------ --------\n");
}

void displayTicketSummaryRecord(const struct Ticket* ticket)
{

	printf("%06d %-6s %-30s %5d\n", ticket->ticketID, ticket->status == 1 ? "ACTIVE" : "CLOSED", ticket->subject, ticket->msg_number);
}

void displayTicketSummaryFooter(void)
{
	printf("------ ------ ------------------------------ --------\n");
}

void displayTicketDetailHeader(void)
{
	printf("------ ----- --------------- ------ ------------------------------ --------\n");
	printf("Ticket Acct# Display Name    Status Subject                        Messages\n");
	printf("------ ----- --------------- ------ ------------------------------ --------\n");
}

void displayTicketDetailRecord(const struct Ticket* tickets)
{
	printf("%06d %05d %-15s %s %-30s %5d\n", tickets->ticketID, tickets->acc_number, tickets->message->name, tickets->status == 1 ? "ACTIVE" : "CLOSED", tickets->subject, tickets->msg_number);
}

void displayTicketDetailFooter(void)
{
	printf("------ ----- --------------- ------ ------------------------------ --------\n");
}

void displayticket(const struct Ticket* tickets)
{
	int j;
	printf("\n================================================================================\n");
	printf("%06d (%s) Re: %s\n", tickets->ticketID, tickets->status == 1 ? "ACTIVE" : "CLOSED", tickets->subject);
	printf("================================================================================\n");
	for (j = 0; j < tickets->msg_number; j++)
	{

		printf("%s (%s):\n", tickets->message[j].type == 'A' ? "AGENT" : "CUSTOMER", tickets->message[j].name);
		printf("   %s\n\n", tickets->message[j].details);

		if (j == tickets->msg_number - 1)
		{
			clearStandardInputBuffer();
			pauseExecution();
		}

		else if (tickets->msg_number > 5)
		{

			if (((j + 1) % 5) == 0)
			{
				printf("<< ENTER key to Continue... >>\n\n");
			}
		}
	}
}

int loadAccounts(struct Account account[], int max)
{

	FILE* fp = NULL;
	int i = 0;

	fp = fopen("accounts.txt", "r");
	if (fp != NULL)
	{
		while (i < max && fscanf(fp, "%d~%c~%30[^~]~%30[^~]~%30[^~]~%d~%lf~%30[^\n]", &account[i].number, &account[i].type, account[i].userlog.name, account[i].userlog.username, account[i].userlog.password, &account[i].demo.birthyear, &account[i].demo.income, account[i].demo.country) == 8)
		{
			i++;
		}
		fclose(fp);
	}
	else
	{
		printf("Failed to open file\n");
	}
	return i;
}

int loadTickets(struct Ticket tickets[], int max)
{
	FILE* fp = NULL;
	int i = 0;
	int j = 0;
	int k = 0;
	fp = fopen("tickets.txt", "r");

	if (fp != NULL)
	{

		for (i = 0; i < max; i++)
		{
			fscanf(fp, "%d|%d|%d|%30[^|]|%d|", &tickets[i].ticketID, &tickets[i].acc_number, &tickets[i].status, tickets[i].subject, &tickets[i].msg_number);

			for (j = 0; j < tickets[i].msg_number; j++)
			{
				if (fscanf(fp, "%c|%30[^|]|%150[^|]|", &tickets[i].message[j].type, tickets[i].message[j].name, tickets[i].message[j].details) == 3)
				{
					k = i + 1;
				}
			}
			fscanf(fp, "\n");
		}
		fclose(fp);
	}
	else
	{
		printf("Failed to open file\n");
	}

	return k;
}

void archiveTickets(struct Ticket ticket)
{
	FILE* fp = NULL;
	fp = fopen("tickets_arc.txt", "a");
	int j;
	if (fp != NULL)
	{
		fprintf(fp, "%d|%d|%d|%s|%d|", ticket.ticketID, ticket.acc_number, ticket.status, ticket.subject, ticket.msg_number);
		for (j = 0; j < ticket.msg_number; j++)
		{
			fprintf(fp, "%c|%s|%s|", ticket.message[j].type, ticket.message[j].name, ticket.message[j].details);
		}
		fprintf(fp, "\n");
		fclose(fp);
	}
	else
	{
		printf("Failed to open file\n");
	}
}

void archiveAccounts(struct Account account)
{

	FILE* fp = NULL;
	fp = fopen("accounts_arc.txt", "a");
	fprintf(fp, "%d~%c~%s~%s~%s~%d~%.2lf~%s\n", account.number, account.type, account.userlog.name, account.userlog.username, account.userlog.password, account.demo.birthyear, account.demo.income, account.demo.country);
	fclose(fp);
}

int loadArchiveTickets(int max, int* messageNumber)
{
	FILE* fp = NULL;
	int i;
	int k = 0;
	fp = fopen("tickets_arc.txt", "r");
	int ticketID, extra1, extra2;
	char extra3[50];
	char reststring[5000];
	int msgnumber = 0;
	int m;
	if (fp != NULL)
	{

		for (i = 0; i < max; i++)
		{

			if (fscanf(fp, "%d|%d|%d|%[^|]|%d|%5000[^\n]\n", &ticketID, &extra1, &extra2, extra3, &m, reststring) == 6)
			{
				k++;
				msgnumber = msgnumber + m;
			}



		}
		fclose(fp);
	}
	else
	{
		printf("Failed to open file\n");
	}
	*messageNumber = msgnumber;
	return k;
}

int loadArchiveAccounts(int max)
{
	FILE* fp = NULL;
	int k = 0;
	int i;
	int accountNumber;
	char reststring[500];
	fp = fopen("accounts_arc.txt", "r");
	if (fp != NULL)
	{
		for (i = 0; i < max; i++)
		{
			if (fscanf(fp, "%d~%[^\n]\n", &accountNumber, reststring) == 2)
			{
				k++;
			}
		}
		fclose(fp);

	}
	else
	{
		printf("Failed to open file\n");
	}
	return k;
}

void storeTicket(struct Ticket* tickets, int max)
{
	FILE* fp = NULL;
	fp = fopen("tickets.txt", "w");
	int i,j;
	if (fp != NULL)
	{

		for (i = 0; i < max; i++)
		{
			if (tickets[i].ticketID > 0)
			{
				fprintf(fp, "%d|%d|%d|%s|%d|", tickets[i].ticketID, tickets[i].acc_number, tickets[i].status, tickets[i].subject, tickets[i].msg_number);

				for (j = 0; j < tickets[i].msg_number; j++)
				{
					fprintf(fp, "%c|%s|%s|", tickets[i].message[j].type, tickets[i].message[j].name, tickets[i].message[j].details);
				}
				fprintf(fp, "\n");
			}
		}
		fclose(fp);
	}
}

void storeAccounts(struct Account* accounts, int max)
{

	FILE* fp = NULL;
	int i = 0;

	fp = fopen("accounts.txt", "w");
	if (fp != NULL)
	{
		for (i = 0; i < max; i++)
		{
			if (accounts[i].number > 0)
			{
				fprintf(fp, "%d~%c~%s~%s~%s~%d~%lf~%s\n", accounts[i].number, accounts[i].type, accounts[i].userlog.name, accounts[i].userlog.username, accounts[i].userlog.password, accounts[i].demo.birthyear, accounts[i].demo.income, accounts[i].demo.country);
			}
		}
		fclose(fp);
	}
	else
	{
		printf("Failed to open file\n");
	}
}

void pauseExecution(void)
{
	printf("<< ENTER key to Continue... >>");
	clearStandardInputBuffer();
	putchar('\n');
}






























