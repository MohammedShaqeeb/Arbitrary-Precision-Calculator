#include "apc.h"

//Function to add two linked lists
void add(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **r_head, Dlist **r_tail)
{
    int carry=0,op1,op2,res;

    //Temporary pointers to traverse lists backwards
    Dlist *temp1=*tail1;
    Dlist *temp2=*tail2;

    //Loop to traverse both list and add data from nodes
    while(temp1!=NULL && temp2!=NULL)
    {
        op1=temp1->data;
        op2=temp2->data;

        res=carry+op1+op2;
        carry=res/10;       //Carry to add it to next digit
        res=res%10;

        //Insert the result of addition of nodes
        insert_first(r_head,r_tail,res);

        //Updating pointers to traverse to next nodes
        temp1=temp1->prev;
        temp2=temp2->prev;
    }

    //Loop to add to result list if the first list has more digits
    while(temp1!=NULL)
    {
        op1=temp1->data;
        res=carry+op1;
        carry=res/10;
        res=res%10;

        //Insert the result of addition of nodes
        insert_first(r_head,r_tail,res);
        temp1=temp1->prev;
    }

     //Loop to add to result list if the Second list has more digits
    while(temp2!=NULL)
    {
        op2=temp2->data;
        res=carry+op2;
        carry=res/10;
        res=res%10;

        //Insert the result of addition of nodes
        insert_first(r_head,r_tail,res);
        temp2=temp2->prev;
    }

    //Checking whether any carry is leftover
    if(carry>0)
    {
        insert_first(r_head,r_tail,carry);
    }
}