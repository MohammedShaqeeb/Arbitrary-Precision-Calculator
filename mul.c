#include "apc.h"

void mul(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **r_head, Dlist **r_tail)
{
    //Temporary list pointers to keep count of single level multiplication
    Dlist *temph_res=NULL;
    Dlist *tempt_res=NULL;
    //Initializing list with zero
    insert_first(&temph_res,&tempt_res,0);

    //Temporary list pointers to add all single level multiplication
    Dlist *addh=NULL;
    Dlist *addt=NULL;

    int count=0,carry=0,sum,res;

    //Temporary pointers to traverse lists backwards
    Dlist *temp1=*tail1;
    Dlist *temp2=*tail2;

    //Loop to do multiplication and addition of single level multiplication
    while(temp2!=NULL)
    {
        //Updation for the next iteration of loop
        temp1=*tail1;
        carry=0;
        addh=NULL;
        addt=NULL;

        //Loop to calculate multiplication of single level multiplication
        while(temp1!=NULL)
        {
            sum=((temp1->data)*(temp2->data))+carry;
            carry=sum/10;
            res=sum%10;

            //Inserting the resultant node to result list
            insert_first(&addh,&addt,res);

            //Traverse to previous node
            temp1=temp1->prev;
        }

        //Add carry at first if present, to the single level multiplication result
        if (carry>0)
        {
            insert_first(&addh,&addt,carry);
        }

        //Add trailing zeros to list to add the single level multiplication to its next iteration
        for(int i=0;i<count;i++)
        {
            insert_last(&addh,&addt,0);
        }
        
        //Addition of previous and present single level multiplication result
        add(&addh,&addt,&temph_res,&tempt_res,r_head,r_tail);

        //Free memory of temporary addition list to use it for next iteration
        free_list(&addh);

        //Update temporary list with single level addition result
        temph_res=*r_head;
        tempt_res=*r_tail;

        //Free memory of result list to use it for next iteration 
        *r_head=NULL;
        *r_tail=NULL;

        //Traverse to previous digit to do next single level multiplication
        temp2=temp2->prev;

        //Count variable to keep track of number of digits completed and add trailing zero to single level list
        count++;
    }

    //Update the result to result list
    *r_head=temph_res;
    *r_tail=tempt_res;

    temp1=*r_head;
    while(temp1!=NULL&&temp1->data==0)
    {
        if(*r_head==*r_tail)
        {
            break;
        }
        *r_head=temp1->next;
        (temp1->next)->prev=NULL;
        free(temp1);
        temp1=*r_head;
    }
}