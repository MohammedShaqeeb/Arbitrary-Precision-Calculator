#include "apc.h"

void divide(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **r_head, Dlist **r_tail)
{
    //Temporary list pointers to store the count of number of dividions 
    Dlist *h_res=NULL;
    Dlist *t_res=NULL;

    //Initializing list with zero
    insert_first(&h_res,&t_res,0);

    //Temporary list pointers to add one to the count list
    Dlist *h_one=NULL;
    Dlist *t_one=NULL;
    //Initializing list with one
    insert_first(&h_one,&t_one,1);

    int cmp;

    //Loop to find the division of two lists
    while ((cmp = compare(*head1, *head2))!=1)
    {
        //Temporary list pointers to store the subtraction of list 1 by list 2
        Dlist *tadd_h = NULL;
        Dlist *tadd_t = NULL;

        //Subtract list 1 by list 2
        sub(head1,tail1,head2,tail2,&tadd_h,&tadd_t);

        //Free memory of 1st List and update it with the subtracted result list
        free_list(head1);
        *head1=tadd_h;
        *tail1=tadd_t; 

        //Update subtract list with NULL to use it for next operation
        tadd_h=NULL;
        tadd_t=NULL;

        //Add the count list with one to increment count list by 1
        add(&h_res,&t_res,&h_one,&t_one,&tadd_h,&tadd_t);

        //Free memory of count list and update it with updated count result
        free_list(&h_res);
        h_res=tadd_h;
        t_res=tadd_t;

        //Update add list with NULL to use it for next iteration
        tadd_h = NULL;
        tadd_t = NULL;
    }

    //Update the result to result list
    *r_head=h_res;
    *r_tail=t_res;
}