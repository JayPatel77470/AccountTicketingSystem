/*
  Assignment #2 Milestone #4
  Full name - Jay Girishkumar Patel
  Student ID number - 158741199
  Seneca email address - jgpatel10@gmail.com
  Course section code - ZCC
*/
#ifndef TICKET_H_
#define TICKET_H_
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include "account.h"
#include "commonHelpers.h"


struct Message
{
	char type; //Type of the user, Customer or Agent
	char name[31]; // name of the user
	char details[151]; //Message details 
};

struct Ticket
{
	int ticketID; //ID of the ticket
	int acc_number; // Account number associated with the ticket ID
	int status; //Status shows ticket is either Active or Closed
	char subject[31]; //Subject of the message is written here
	int msg_number; //Number of messages
	struct Message message[20]; //struct that contains various details of messages

};

//Gets the information of new ticket
void getTicket(struct Ticket* tct);

//It lets the customer modifying the ticket
void updateTicket(struct Ticket* tct);

//It lets the Agent to control the content of the ticket
void manageTicket(struct Ticket* tct, const struct UserLogin* userlog);

//Contains functions that shows the lists of active tickets
void ActiveTickets(struct Ticket* tickets, int max);

//Contains functions that shows the lists of closed tickets
void CloseTickets(struct Ticket* tickets, int max);

//Contains functions that shows the lists of newtickets
void NewTickets(struct Ticket* tickets, int max);

//Gets the highest ticket number
//Returns the highest ticket number
int highestTicketNumber(struct Ticket* tickets, int max);

//Contains the functions that lets the customer modify his tickets
void modifyTicket(struct Ticket* tickets, int max, const struct Account* acc);

//Contains the funtions that shows the customer his tickets
void myTickets(struct Ticket* tickets, int max, const struct Account* acc);

//Contains the functions that send the closed tickets to tickets_arc.txt file
void ArchiveClosedTickets(struct Ticket* tickets, int max);

#endif
