#include "apc.h"

void sub(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **r_head, Dlist **r_tail)
{
    int bor=0,res;

    //Temporary pointers to traverse lists backwards
    Dlist *temp1=*tail1;
    Dlist *temp2=*tail2;
    
    //Loop to traverse both list and subtract data from nodes
    while(temp1!=NULL && temp2!=NULL)
    {
        //Check whether the first list data is greater or smaller to determine borrow
        if(temp1->data-bor < temp2->data)
        {
            res=temp1->data - temp2->data - bor +10;    //Add 10 to make the result positive and correct
            bor=1;      //Set borrow
        }
        else
        {
            res=temp1->data - temp2->data - bor;
            bor=0;      //Reset borrow
        }
        
        //Insert the result of Subtraction of nodes
        insert_first(r_head,r_tail,res);

        //Updating pointers to traverse to next nodes
        temp1=temp1->prev;
        temp2=temp2->prev;
    }

    //Loop to add to result list if the first list has more digits
    while(temp1!=NULL)
    {
        //check whether borrow present or not 
        if(temp1->data<bor)
        {
            res=temp1->data - bor +10;
            bor=1;      //Set borrow
        }
        else
        {
            res=temp1->data - bor;
            bor=0;      //Reset borrow
        }

        //Insert the result of Subtraction of nodes
        insert_first(r_head,r_tail,res);

        //Updating pointers to traverse to next node
        temp1=temp1->prev;
    }

    Dlist *temp=*r_head;

    //Removing leading zeros in the result subtraction list
    while(temp!=NULL && temp->data==0)
    {
        //Only one digit then do not remove zero
        if(*r_head==*r_tail)
        {
            break;
        }

        //Updating to traverse to next node
        *r_head=temp->next;
        (temp->next)->prev=NULL;

        //Free memory of removed zero node
        free(temp);
        temp=*r_head;
    }
}