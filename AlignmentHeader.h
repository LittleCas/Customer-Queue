#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>  
#define MAX 15 

typedef struct AppointmentTime{ //
	int hour;
	char min[2];
}time;

typedef struct Customer{
	char lplate[6];
	int contact;
	time t;	 //Appointment Time Structure
}C;
 
typedef struct Queue{ //Alignment queue
int front;
int rear;
 C Align [MAX]; //Customer structure holding queue elements
}AQ; 

AQ CreateQueue(){ //creates the queue for alingment and returns it empty
    AQ Q;
    Q.front=-1;
    Q.rear=-1;
return Q;
}
//checks if queue is full to prevent overflow of queue
int isFull(AQ data) 
{
	if(data.rear==MAX-1){
		printf("There is no more space in the queue\n");
		printf("\nReturning to Menu..\n");
		system("pause");
		return 1;
	}
	else
		return 0;
}

AQ enqueue(AQ data, C Cust){//AQ data is the alignment aueue, C Cust is the customer's details entered in the  queue
	if(data.front ==-1)
	     data.front++; //increments front to add element to the queue
//endif front
    data.rear =data.rear +1;
	strcpy(data.Align[data.rear].lplate,Cust.lplate);
	data.Align[data.rear].contact =Cust.contact; //enters customer data into rear of queue
	data.Align[data.rear].t.hour=Cust.t.hour;
	strcpy(data.Align[data.rear].t.min,Cust.t.min);

return data;
}

//checks if queue is empty to prevent underflow of queue
int isempty(AQ data)
{
    if (data.front==-1){
    	printf("There is nothing in the queue\n");
    	printf("\n\tReturning to Menu..\n");
		system("pause");
        return 1;
    }
    else
        return 0;
    
}

 AQ dequeue(AQ data,C Cust){
	int i;
 	printf("\n~Customer with License Plate %s is Removed From Queue~\n",data.Align[data.front].lplate);
 		
    for(i=data.front; i<MAX;i++){
    	strcpy(data.Align[i].lplate, data.Align[i+1].lplate); //moves elements up the queue
      	data.Align[i].contact=data.Align[i+1].contact; 
        data.Align[i].t.hour=data.Align[i+1].t.hour;
        strcpy(data.Align[i].t.min,data.Align[i+1].t.min);
	}
    --data.rear;
        
    if(data.rear==-1) //empty queue
        data.front=-1;

    return data;
}

