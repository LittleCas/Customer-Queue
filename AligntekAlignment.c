//********Programmer: Rhona Castanheiro********
//********Date: May 14,2022********

/*Aligntek Alignment Database allows the user to enter customers' vehicles in their daily queue for alignment.
 This program will also allow the user to edit these details and remove them when the customer's vehicle is 
 aligned. When prompted the user can see the daily queue of customers and a specific customer's position
  At the end of the day a report is genrated to show how many customers need to return and the number of customers processed*/

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <windows.h>
#include "AlignmentHeader.h"
#define MAX 15 //Maximum amount of customers that can be done

void login();
AQ EnterQueue(AQ queue,C Cust);
AQ EditCustomer(AQ queue);
void SearchPosition(AQ queue);
AQ DequeueCustomer(AQ queue, C Cust);
void VeiwQueue(AQ queue);
void Report();
int Search(AQ queue,char* target);
int StartMenu();
char username[8];
char password[9];
int count=0; // holds the number of customers aligned
int rcount=0;//holds the number of customers returnin

void main (){
	int choice;
	AQ queue; //calls Queue structure from header file
	C Cust; //calls Customer structure from header file
	
	system("color 76");
    printf("\n\n\n\t\t\t WELCOME TO ALIGNTEK ALIGNMENT DATABASE!\n\n\n");
    system("pause");
    system("cls");
	
	login();//Displays login interface

    system("color 09"); //Changes background and foreground color of the program
    queue= CreateQueue(); // calls createqueue from headerfile
 
	while ((choice= StartMenu())!=0){
        switch (choice){
            case 1:	
         	 	queue=EnterQueue(queue, Cust); //Allows user to enter a record in the Alignment queue
         		system("cls");
            break;
            
            case 2:
               	queue=EditCustomer(queue);//Allows user to edit the value of a selected item previously entered
            	 
            break;
           
            case 3:
              SearchPosition(queue); //Allows the user to search for a record
            break;
              system("cls");
          
            case 4:
            	VeiwQueue(queue);//Allows user to veiw the current queue in order of entry
            break;
            system("cls");
            
            case 5:
          		 queue= DequeueCustomer(queue,Cust); //Allows user to removee the first record entered   	
            break;
            system("cls");
            
            case 6:
            	 Report();//Allows user to veiw the total nmber of cars  and customrs to return
            break;
            system("cls");
            	
            default:
                printf("\n\n\t\tI N V A L I D  R E -E N T E R  C H O I C E\n\n");//if the choice entered is not equal to the option above, error message displayed
                system("pause");
                printf("\n\nRETURNING TO MENU...");
                sleep(1);
                system ("cls");
            break; 
        }  
    }
    printf("\n\t\t\tALIGNTEK DATABASE CLOSED\n\n PRESS ANY KEY TO EXIT ");
}

void login(){
	int i;	

    system("color 30");
    printf("\n\n\n\t\t\t~ALIGNTEK ALIGNMENT DATABASE~\n\n\n");
    
//Gives user three attempts to enter the correct username and password
    for(i=0;i<3;i++){
   		printf("Enter username:\n");
    	scanf("%s",&username);
   		printf("\nEnter Password\n");
    	scanf("%s",&password);
    	
//Predefined Username and Password to enter database
   		if((strcmp(username,"Aligntek")==0)&&(strcmp(password,"Align876")==0)){
    		printf("\nLOGIN SUCCESSFUL\n");
    		sleep(2);
    		break;
    	}
    	else{
    		printf("INCORRECT USERNAME OR PASSWORD\n\n ");
    		printf("\n\t\t*You Have %d entries Remaining*\n\n",2-i);	
		}
		if (i==2) 
		   exit(0);	//Exits program from too many incorrect attempts
	}
}

//displays menu options to user
int StartMenu(){
    int choice;
    
    system ("cls");
    system("color 76");
    printf("\t\t~W E L C O M E  T O  A L I G N T E K  A L I G N M E N T~\n\n");
    printf("S E L E C T  A  C H O I C E  T O  P R O C E E D\n");
    
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("1 --> \t Enter Customer in Queue\n\n");
    printf("2 --> \t Edit Customer in Queue\n\n");
    printf("3 --> \t Search Position\n\n");
    printf("4 --> \t View  Queue\n\n");
    printf("5 --> \t Remove Customer\n\n");
    printf("6 --> \t Report\n\n");
    printf("0 --> \t EXIT PROGRAM\n\n");
    printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n ");
    
    printf("\nSelct any choice by entering a number from the options above\n");
    scanf("%d",&choice);
    system ("cls");
    return choice;
}
 
 
AQ EnterQueue(AQ queue, C Cust){ 
	int copy;
	if(isFull(queue)){ //calls isFull function from header file
		StartMenu();
	}
	else{
		printf("\n\t>>>>>>>>>> E N T E R  Q U E U E >>>>>>>>>>\n\n");
		printf("Enter Customer's License Plate:\n");
		scanf("%s",Cust.lplate);
	
		printf("\nEnter Customer's Contact:\n"); 
		scanf("%d",&Cust.contact);
	
		printf("\nEnter Customer's Appointment Time in 24 hour format hr:min\n"); 
		scanf("%d:%s",&Cust.t.hour,Cust.t.min);
		
		printf("\n\t\t~Customer Added to Queue~\n");
		
		count++;	 //increments number of customers entered for the day
		queue=enqueue(queue, Cust); //calls enqueue function from header file
		
		printf("\nReturning to Menu...");
		sleep(3);
		system("cls");
		return queue;
	}
}

int Search(AQ queue,char* target){
	int i;
	int found=0;

	for(i=0;i<MAX;i++){
		if (strcmp(target,queue.Align[i].lplate)==0){ //compares target with license plates entered in database to find a match
			printf("Customer is in position - %d - \n\n)",i+1);
			return i;
			printf("Their contact is %d\n\n",queue.Align[i].contact);
			printf("Their appointment time is %d:%s\n\n",queue.Align[i].t.hour,queue.Align[i].t.min);
			found=1;
		}
	}
	if(found==0){
		printf("License Plate not Found,Please Re-enter\n");
		return -1;
	}
}

AQ EditCustomer(AQ queue){
	int response;
	int i;
	char target[7];
	if (isempty(queue)){ //calls isempty function from header file
		StartMenu();
	}
	else{
		printf("\n\t>>>>>>>>>>E D I T  C U S T O M E R  I N  Q U E U E >>>>>>>>>>\n\n");
		printf("Enter Customer's License Plate\n");
		scanf("%s",target);
		i=Search(queue,target); //calls search function 
		if(i==-1){
			getch();
			StartMenu(); //returns to start menu if license plate is not found
		}
		else{
		
		printf("What would you like to edit?\n");
		printf(" 1> License Plate\n 2> Phone Number\n 3> Appointment Time\n\n Response:");
		scanf("%d",&response);
		if (response==1){
			printf("\nEnter New License Plate\n");
			scanf("%s",queue.Align[i].lplate); //overwrites previously entered customer details
			printf("\n\t\t~Customer's License Plate is Edited~\n");
		}
		if (response==2){
			printf("Enter New Phone Number\n");
			scanf("%d",&queue.Align[i].contact);
			printf("\n\t\t~Customer's Contact is Edited~\n");
		}
		if (response==3){
			printf("Enter New Appointment Time\n");
	    	scanf("%d:%s",&queue.Align[i].t.hour,queue.Align[i].t.min);
	    	printf("\n\t\t~Customer's Appointment Time is Edited~\n");
		}
		printf("\nReturning to Menu...");
		sleep(3);
		system("cls");
		return queue;
	}
	}
}


void SearchPosition(AQ queue){
	char target[7];
	printf("\n\t>>>>>>>>>> S E A R C H   C U S T O M E R 'S  P O S I T I O N  >>>>>>>>>>\n\n");
	if (isempty(queue)){
		StartMenu();
	}
	else{
		printf("Enter Customer's License Plate\n");
		scanf("%s",target );
		Search(queue,target); //calls search function 
		system("pause");
	}
}

AQ DequeueCustomer(AQ queue,C Cust){
	int response;
	int i=0;
 	system("cls");
 	printf("\n\t>>>>>>>>>> R E M O V E  C U S T O M E R  >>>>>>>>>>\n\n");
 	if(isempty(queue)){
 		StartMenu();
	
	}
	else{    
 		printf("Will the customer be returning? 1 for Yes, 0 for No\n");
 		scanf("%d",&response);
   	
 		if(response==1){
 			rcount++; //increments number of customers returning
 			queue=dequeue(queue,Cust); //calls dequeue function from header file
			printf("\nReturning to Menu...");
			sleep(3);
			system("cls");
			return queue;	
		}
		else{
    	queue=dequeue(queue,Cust); 
		printf("\nReturning to Menu...");
		sleep(3);
		system("cls");
		return queue;
		}
 	}
}

void VeiwQueue(AQ queue){
	int see;
	system ("cls");
	printf("\n\t>>>>>>>>>> V I E W  Q U E U E  >>>>>>>>>>\n\n");
   if(isempty(queue)){
   	StartMenu();
   }
	 else
		{
		printf("\tCustomers Waiting:\n\n");
		for (see=queue.front;see<=queue.rear;see++){
			printf("*****************************\n");
			printf("License Plate: %s\n", queue.Align[see].lplate);
			printf("Contact: %d\n", queue.Align[see].contact);
			printf("Appointment Time: %d:%s\n", queue.Align[see].t.hour,queue.Align[see].t.min);
			printf("*****************************\n\n");	
		}
	}
	system ("pause");
	system ("cls");
}


void Report(){
	int see;
//	system ("cls");
	printf("\n\t>>>>>>>>>> R E P O R T >>>>>>>>>>\n\n");
	if(count==0){
		printf("No Customers Have Been Entered\n");
		system("pause");
	//	StartMenu();
	}
	else{
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("\tTOTAL CUSTOMERS: %d\n",count);
	printf("\tTOTAL RETURNING:%d\n",rcount);
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	system ("pause");
	system ("cls");
	}
}


