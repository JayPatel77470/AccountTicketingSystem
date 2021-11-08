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
#include "account.h"
#include "ticket.h"
#include "accountTicketingUI.h"
#include "string.h"

void getTicket(struct Ticket* tct)
{
	printf("\nNew Ticket (Ticket#:0%5d)\n", tct->ticketID);
	printf("----------------------------------------\n");

	tct->status = 1;
	printf("Enter the ticket SUBJECT (30 chars. maximum): ");
	getCString(tct->subject, 1, 30);
	printf("\n");
	printf("Enter the ticket message details (150 chars. maximum). Press the ENTER key to submit:\n");
	getCString(tct->message[0].details, 1, 150);
	tct->message[0].type = 'C';
	tct->msg_number = 1;
	printf("\n");
	printf("*** New ticket created! ***\n\n");
}

void updateTicket(struct Ticket* tct)
{
	int flag = 0;
	do
	{
		printf("\n----------------------------------------\n");
		printf("Ticket 0%5d - Update Options\n", tct->ticketID);
		printf("----------------------------------------\n");
		printf("Status  : %-6s\n", tct->status == 1 ? "ACTIVE" : "CLOSED");
		printf("Subject : %s\n", tct->subject);
		printf("----------------------------------------\n");
		printf("1) Modify the subject\n");
		printf("2) Add a message\n");
		printf("3) Close ticket\n");
		printf("0) Done\n");
		printf("Selection: ");
		int select;
		select = getIntFromRange(0, 4);
		switch (select)
		{
		case 1:
		{
			printf("\nEnter the revised ticket SUBJECT (30 chars. maximum): ");
			getCString(tct->subject, 1, 30);
		}
		break;

		case 2:
		{
			if (tct->msg_number == 20)
			{
				printf("\nERROR: Message limit has been reached, call ITS Support!\n");
			}
			else
			{
				int x = tct->msg_number;
				printf("\nEnter the ticket message details (150 chars. maximum). Press the ENTER key to submit:\n");
				getCString(tct->message[x].details, 1, 150);
				strcpy(tct->message[x].name, tct->message->name);
				tct->message[x].type = 'C';
				tct->msg_number++;
			}
		}
		break;

		case 3:
		{
			char C1, C2;
			printf("\nAre you sure you CLOSE this ticket? ([Y]es|[N]o): ");
			C1 = getCharOption("YN");
			if (C1 == 'Y')
			{
				if (tct->msg_number != 20)
				{

					printf("\nDo you want to leave a closing message? ([Y]es|[N]o): ");
					C2 = getCharOption("YN");

					if (C2 == 'N')
					{

						printf("\n*** Ticket closed! ***\n");
						tct->status = 0;
						flag = 1;
					}
					else
					{
						int x;
						x = tct->msg_number;
						printf("\nEnter the ticket message details (150 chars. maximum). Press the ENTER key to submit:\n");
						getCString(tct->message[x].details, 1, 150);
						strcpy(tct->message[x].name, tct->message->name);
						tct->message[x].type = 'C';
						tct->msg_number++;
						printf("\n*** Ticket closed! ***\n\n");
						tct->status = 0;
						flag = 1;
					}
				}
				else
				{
					printf("\n*** Ticket closed! ***\n");
					tct->status = 0;
					flag = 1;
				}

			}
			else
			{
				flag = 0;
			}
		}
		break;

		case 0:
		{
			flag = 1;
		}
		break;
		}


	} while (flag == 0);
}

void manageTicket(struct Ticket* tct, const struct UserLogin* userlog)
{
	int flag = 0;
	do
	{
		int select;
		char C1, C2;

		printf("\n----------------------------------------\n");
		printf("Ticket 0%5d - Update Options\n", tct->ticketID);
		printf("----------------------------------------\n");
		printf("Status  : %s\n", tct->status == 1 ? "ACTIVE" : "CLOSED");
		printf("Subject : %s\n", tct->subject);
		printf("Acct#   : %d\n", tct->acc_number);
		printf("Customer: %s\n", tct->message->name);
		printf("----------------------------------------\n");
		printf("1) Add a message\n");
		printf("2) Close ticket\n");
		printf("3) Re-open ticket\n");
		printf("0) Done\n");
		printf("Selection: ");
		scanf("%d", &select);
		switch (select)
		{

		case 1:
		{
			if (tct->status == 0)
			{
				printf("\nERROR: Ticket is closed - new messages are not permitted.\n");
			}
			else
			{
				if (tct->msg_number != 20)
				{
					int x = tct->msg_number;
					printf("\nEnter the ticket message details (150 chars. maximum). Press the ENTER key to submit:\n");
					getCString(tct->message[x].details, 1, 150);
					tct->message[x].type = 'A';
					strcpy(tct->message[x].name, userlog->name);
					tct->msg_number++;
				}
				else
				{
					printf("\nERROR: Message limit has been reached, call ITS Support!\n");
				}
			}
		}break;

		case 2:
		{
			if (tct->status == 0)
			{
				printf("\nERROR: Ticket is already closed!\n");
			}
			else
			{
				printf("\nAre you sure you CLOSE this ticket? ([Y]es|[N]o): ");
				C1 = getCharOption("YN");
				if (C1 == 'Y')
				{
					if (tct->msg_number != 20)
					{
						printf("\nDo you want to leave a closing message? ([Y]es|[N]o): ");
						C2 = getCharOption("YN");
						if (C2 == 'Y')
						{
							int x = tct->msg_number;
							printf("\nEnter the ticket message details (150 chars. maximum). Press the ENTER key to submit:\n");
							getCString(tct->message[x].details, 1, 150);
							strcpy(tct->message[x].name, userlog->name);
							tct->message[x].type = 'A';
							tct->msg_number++;
							printf("\n*** Ticket closed! ***\n");
							tct->status = 0;
						}
						else
						{
							printf("\n*** Ticket closed! ***\n");
							tct->status = 0;
						}
					}
					else
					{
						printf("\n*** Ticket closed! ***\n");
						tct->status = 0;

					}
				}
				else
				{
					flag = 0;
				}

			}
		}break;

		case 3:
		{

			if (tct->status == 0)
			{
				printf("\nAre you sure you RE-OPEN this closed ticket? ([Y]es|[N]o): ");
				C1 = getCharOption("YN");
				if (C1 == 'N')
				{
					flag = 0;
				}
				else
				{
					printf("\n*** Ticket re-opened! ***\n");
					tct->status = 1;
				}
			}
			else
			{
				printf("\nERROR: Ticket is already active!\n");
			}

		}break;

		case 0:
		{
			printf("\n");
			flag = 1;
		}break;

		}
	} while (flag == 0);

}

void ActiveTickets(struct Ticket* tickets, int max)
{
	int i;
	int valid = 0;
	int num;
	do
	{

        
		displayTicketDetailHeader();
		for (i = 0; i < max; i++)
		{
			if (tickets[i].status == 1 && tickets[i].ticketID > 0)
			{
				displayTicketDetailRecord(&tickets[i]);
			}
		}
		displayTicketDetailFooter();
		num = getTicketNumber();
		do
		{
			if (num < 0)
			{
				printf("ERROR: Value must be positive or zero: ");
			}
			else if (num == 0)
			{
				printf("\n");
			}
			else
			{
				for (i = 0; i < max; i++)
				{
					if (tickets[i].status == 1 && num == tickets[i].ticketID)
					{
						valid = 1;
						displayticket(&tickets[i]);
					}
				}
				if (valid == 0)
				{
					printf("\nERROR: Invalid ticket number.\n\n");
					clearStandardInputBuffer();
					pauseExecution();
				}

			}

		} while (num < 0);
	} while (num != 0);
}

void CloseTickets(struct Ticket* tickets, int max)
{
	int i;
	int valid = 0;
	int num;
	do
	{
		displayTicketDetailHeader();
		for (i = 0; i < max; i++)
		{
			if (tickets[i].status == 0 && tickets[i].ticketID > 0)
				{
					displayTicketDetailRecord(&tickets[i]);
				}
			
		}
		displayTicketDetailFooter();
		num = getTicketNumber();
		do
		{
			if (num < 0)
			{
				printf("ERROR: Value must be positive or zero: ");
			}
			else if (num == 0)
			{
				printf("\n");
			}
			else
			{
				for (i = 0; i < max; i++)
				{
					if (tickets[i].status == 0 && num == tickets[i].ticketID)
					{
						valid = 1;
						displayticket(&tickets[i]);
					}
				}
				if (valid == 0)
				{
					printf("\nERROR: Invalid ticket number.\n\n");
					clearStandardInputBuffer();
					pauseExecution();
				}

			}

		} while (num < 0);
	} while (num != 0);
}

void NewTickets(struct Ticket* tickets, int max)
{
	int i;
	int valid = 0;
	int num;
	do
	{

		displayTicketDetailHeader();
		
		for (i = 0; i < max; i++)
		{
			if (tickets[i].status == 1 && tickets[i].msg_number == 1)
			{
				displayTicketDetailRecord(&tickets[i]);
			}
		}
		displayTicketDetailFooter();
		do
		{
			num = getTicketNumber();
			if (num == 0)
			{
				printf("\n");
			}
			else
			{
				for (i = 0; i < max; i++)
				{
					if (tickets[i].status == 1 && num == tickets[i].ticketID && tickets[i].msg_number == 1)
					{
						valid = 1;
						displayticket(&tickets[i]);
					}
				}
				if (valid == 0)
				{
					printf("\nERROR: Invalid ticket number - you may only access your own tickets.\n\n");
					clearStandardInputBuffer();
					pauseExecution();
				}

			}

		} while (num < 0);
	} while (num != 0);
}

int highestTicketNumber(struct Ticket* tickets, int max)
{
	int newTicket = tickets[0].ticketID;
	int i;
	for (i = 0; i < max; i++)
	{
		if (tickets[i].ticketID > newTicket)
		{
			newTicket = tickets[i].ticketID;
		}
	}
	return newTicket;
}

void modifyTicket(struct Ticket* tickets, int max, const struct Account* acc)
{
	int num;
	int i;
	int valid = 0;

	printf("\nEnter ticket number: ");
	scanf("%d", &num);
	for (i = 0; i < max; i++)
	{
		if (acc->number == tickets[i].acc_number)
		{
			if (num == tickets[i].ticketID)
			{
				if (tickets[i].status == 1)
				{
					updateTicket(&tickets[i]);
					valid = 1;
				}
				else
				{
					valid = 2;
				}
			}
		}
	}
	if (valid == 0)
	{
		printf("\nERROR: Invalid ticket number - you may only modify your own ticket.\n\n");
	}
	if (valid == 2)
	{
		printf("\nERROR: Ticket is closed - changes are not permitted.\n\n");
	}
	clearStandardInputBuffer();
	pauseExecution();
}

void myTickets(struct Ticket* tickets, int max, const struct Account* acc)
{
	int num;
	int i;
	int valid = 0;
	printf("\n");
	do
	{
		displayTicketSummaryHeader();
		for (i = 0; i < max; i++)
		{
			if (acc->number == tickets[i].acc_number)
			{
				displayTicketSummaryRecord(&tickets[i]);
			}
		}
		displayTicketSummaryFooter();
		num = getTicketNumber();
		do
		{
			if (num == 0)
			{
				printf("\n");
			}
			else
			{
				for (i = 0; i < max; i++)
				{
					if (num == tickets[i].ticketID && acc->number == tickets[i].acc_number)
					{
						valid = 1;
						displayticket(&tickets[i]);
					}
				}
				if (valid == 0)
				{
					printf("\nERROR: Invalid ticket number - you may only access your own tickets.\n\n");
					clearStandardInputBuffer();
					pauseExecution();

				}

			}

		} while (num < 0);
	} while (num != 0);
}

void ArchiveClosedTickets(struct Ticket* tickets, int max)
{
	printf("Are you sure? This action cannot be reversed. ([Y]es|[N]o): ");
	char s = getCharOption("YN");
	if (s == 'Y')
	{
		int i;
		int k = 0;
		for (i = 0; i < max; i++)
		{
			if (tickets[i].status == 0 && tickets[i].ticketID > 0)
			{
				archiveTickets(tickets[i]);
				tickets[i].ticketID = 0;
				k++;
			}
		}
		printf("\n*** %d tickets archived ***\n\n", k);
	}
}