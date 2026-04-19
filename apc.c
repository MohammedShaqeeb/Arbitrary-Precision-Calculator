/*DOCUMENTATION:
  NAME: N.MOHAMMED SHAQEEB
  REG_NO: 25031_124
  START_DATE: 10-04-2026
  END_DATE: 17-04-2026
  DESC: This Project is Arbitrary Precision Calculator, which can calculate larger numbers with basic operations of 
        Addition, Subtraction, Multiplication and Division using the help of Doubly Linked list.
  */

#include "apc.h"

//Validate the input operands 
int validate(const char *str)
{
    int i=0,sign=0;
    while(str[i]!='\0')
    {
        //Check whether the 1st character of the operand is '-' or '+'  
        if(i==0 && (str[i]=='-' || str[i]=='+'))
        {
            //Check if the opersnd is signed or not
            if(str[i]=='-' )
            {
                sign=1;
            } 
            else if(str[i]=='+')
            {
                sign=0;
            }
            i++;
            continue;
        }

        //Check whether the characters are digits or not
        if(isdigit(str[i])==0)
        {
            return -1;
        }
        i++;
    }
    //Return the sign 
    return sign;
}

//Function to free a list node by node
void free_list(Dlist **head)
{
    //Traverse with temporary pointer
    Dlist *temp=*head;
    while(temp!=NULL)
    {
        Dlist *next=temp->next;
        free(temp);
        temp=next;
    }
    *head=NULL;
}

//Function to insert new node at last of the linked list
int insert_last(Dlist **head, Dlist **tail, int data)
{
    //Allocate memory for new node 
    Dlist *new=malloc(sizeof(Dlist));
    //Chcek the node is created or not
    if(new==NULL)
    {
        return FAILURE;
    }
    //Update the node fields with required data and links
    new->data=data;
    new->prev=NULL;
    new->next=NULL;

    //Check whether the list is empty or not
    if(*head==NULL)
    {
        *head=new;
    }
    else
    {
        new->prev=*tail;
        (*tail)->next=new;
    }
    *tail=new;
    return SUCCESS;
}

//Function to insert new node at first of the linked list
int insert_first(Dlist **head, Dlist **tail, int data)
{
    //Allocate memory for new node 
    Dlist *new=malloc(sizeof(Dlist));
    //Check the node is created or not
    if(new==NULL)
    {
        return FAILURE;
    }
    //Update new node fields with required dat and link
    new->data=data;
    new->prev=NULL;
    //Check whether the list is empty or not
    if(*head==NULL)
    {
        new->next=NULL;
        *head=new;
        *tail=new;
        return SUCCESS;
    }
    new->next=*head;
    (*head)->prev=new;
    *head=new;
    return SUCCESS;
}

//Function to print list node by node
void print_list(Dlist *head)
{
	/* Cheking the list is empty or not */
	if (head == NULL)
	{
		printf("INFO : List is empty\n");
	}
	else
	{
	    while (head)		
	    {
		    /* Printing the list */
		    printf("%d", head -> data);

		    /* Travering in forward direction */
		    head = head -> next;
	    }
        printf("\n");
    }
}

//Function to convert the input operand string to linked list
int convert_str_to_dll(const char* str,Dlist **head,Dlist **tail)
{
    int i=0;
    //Convert all characters to digits and insert at last of the list
    while(str[i]!='\0')
    {
        int num=str[i]-'0';
        if (insert_last(head,tail,num)==FAILURE) 
		{
			printf("INFO : Insertion Failure\n");
    	}
        i++;
    }
    //Remove characters '-' and '+' if it is present at start
    Dlist *temp=*head;
    while(temp!=NULL && (temp->data==-3 || temp->data==-5))
    {
        *head=temp->next;
        (temp->next)->prev=NULL;
        free(temp);
        temp=*head;
    }
    //Remove all leading zeros before the non zero numbers 
    while(temp!=NULL&&temp->data==0)
    {
        if(*head==*tail)
        {
            break;
        }
        *head=temp->next;
        (temp->next)->prev=NULL;
        free(temp);
        temp=*head;
    }
    return 0;
}

//Function to check whether the operand is zero or not
int is_zero(Dlist *head)
{
    Dlist *temp=head;
    while(temp!=NULL)
    {
        //Check whether list node have non zero number
        if(temp->data!=0)
        {
            return 0;
        }
        temp=temp->next;
    }
    return 1;
}

//Function to compare and find the greater and smaller operand list
int compare(Dlist *head1,Dlist *head2)
{
    //Temporary pointer to traverse lists
    Dlist *temp1=head1;
    Dlist *temp2=head2;

    //Count the number of digits of both lists
    int l1_count=0,l2_count=0;
    while(temp1!=NULL)
    {
        temp1=temp1->next;
        l1_count++;
    }
    while(temp2!=NULL)
    {
        temp2=temp2->next;
        l2_count++;
    }

    
    //Compare using digits to check greater number
    if(l1_count>l2_count)
    {
        return 0;
    }
    else if(l1_count<l2_count)
    {
        return 1;
    }
    else
    {
        //If the digits are equal compare each node data with eachother
        temp1=head1;
        temp2=head2;
        while(temp1!=NULL)
        {
            if(temp1->data>temp2->data)
            {
                return 0;
            }
            else if(temp2->data>temp1->data)
            {
                return 1;
            }
            temp1=temp1->next;
            temp2=temp2->next;
        }
        //If no match found return both are equal
        return -1;
    }
}

int main(int argc,char *argv[])
{
    //Check whether all required input data are given
    if(argc!=4)
    {
        printf("INVALID INPUT!\nUsage: ./a.out <operand_1> <operator> <operand_2>\n");
        return 0;
    }

    //Check whether the operator is any of the four '+', '-', '*' or '/'
    if(!(argv[2][0]=='+'||argv[2][0]=='-' ||argv[2][0]=='*'||argv[2][0]=='/'))
    {
        printf("INVALID INPUT!\nUsage: Operator should one of these '+','-','*','/'\n");
        return 0;
    }

    //Validate the operands and receive the sign of both operands
    int sign1,sign2;
    if((sign1=validate(argv[1]))==FAILURE)
    {
        printf("INVALID INPUT!\nUsage: Operands should be only digits!\n");
        return 0;
    }
    if((sign2=validate(argv[3]))==FAILURE)
    {
        printf("INVALID INPUT!\nUsage: Operands should be only digits!\n");
        return 0;
    }

    //Pointers to two operand list and result list
	Dlist *head1 = NULL; 
    Dlist *tail1 = NULL;	
    Dlist *head2 = NULL; 
	Dlist *tail2 = NULL;
    Dlist *r_head = NULL;
    Dlist *r_tail = NULL;

    //Store the operator in character op
    char op=argv[2][0];

    //Converting the string input to list to do operations
    if(convert_str_to_dll(argv[1],&head1,&tail1)==FAILURE)
    {
        perror("Linked List Creation");
        return 0;
    }
    if(convert_str_to_dll(argv[3],&head2,&tail2)==FAILURE)
    {
        perror("Linked List Creation");
        return 0;
    }

    //Checking whether the second operand is zero and prevent infinite loop for dividion
    int zero=is_zero(head2);
    if(op=='/' && zero==1 )
    {
        printf("Division of %s and %s is Not possible! Second operand should not be zero for division!\n",argv[1],argv[3]);
        return 0;
    }

    //Compare and find the greater and smaller operand
    int cmp=compare(head1,head2);

    //Switch case to implement the operation based on operator character
    switch(op)
    {
        //Case to implement Addition
        case '+':
        {
            if((sign1==0 && sign2==0) || (sign1==1&&sign2==1))
            {
                add(&head1,&tail1,&head2,&tail2,&r_head,&r_tail);
                if((sign1==0 && sign2==0))
                {
                    printf("Addition of %s and %s is: ",argv[1],argv[3]);
                }
                else
                {
                    printf("Addition of %s and %s is: -",argv[1],argv[3]);
                }
            }
            else
            {
                if(cmp==-1)
                {
                    printf("Addition of %s and %s is: 0\n",argv[1],argv[3]);
                    return 0;
                }
                if(sign1==0 && sign2==1)
                {
                    if(cmp==0)
                    {
                        sub(&head1,&tail1,&head2,&tail2,&r_head,&r_tail);
                        printf("Addition of %s and %s is: ",argv[1],argv[3]);
                    }
                    else if(cmp==1)
                    {
                        sub(&head2,&tail2,&head1,&tail1,&r_head,&r_tail);
                        printf("Addition of %s and %s is: -",argv[1],argv[3]);
                    }
                }
                else if(sign1==1 && sign2==0)
                {
                    if(cmp==0)
                    {
                        sub(&head1,&tail1,&head2,&tail2,&r_head,&r_tail);
                        printf("Addition of %s and %s is: -",argv[1],argv[3]);
                    }
                    else if(cmp==1)
                    {
                        sub(&head2,&tail2,&head1,&tail1,&r_head,&r_tail);
                        printf("Addition of %s and %s is: ",argv[1],argv[3]);
                    }
                }
            }
            //Print the result list
            print_list(r_head);
            break;
        }
        //Case to implement Subtraction
        case '-':
        {
            if((sign1==0 && sign2==1) || (sign1==1&&sign2==0))
            {
                add(&head1,&tail1,&head2,&tail2,&r_head,&r_tail);
                if((sign1==1 && sign2==0))
                {
                    printf("Subtraction of %s and %s is: -",argv[1],argv[3]);
                }
                else
                {
                    printf("Subtraction of %s and %s is: ",argv[1],argv[3]);
                }
            }
            else 
            {
                if(cmp==-1)
                {
                    printf("Subtraction of %s and %s is: 0\n",argv[1],argv[3]);
                    return 0;
                }
                else if(cmp==0)
                {
                    sub(&head1,&tail1,&head2,&tail2,&r_head,&r_tail);
                    if(sign1==0 && sign2==0)
                    {
                        printf("Subtraction of %s and %s is: ",argv[1],argv[3]);
                    }
                    else 
                    {
                        printf("Subtraction of %s and %s is: -",argv[1],argv[3]);
                    }
                }
                else if(cmp==1)
                {
                    sub(&head2,&tail2,&head1,&tail1,&r_head,&r_tail);
                    if(sign1==0 && sign2==0)
                    {
                        printf("Subtraction of %s and %s is: -",argv[1],argv[3]);
                    }
                    else 
                    {
                        printf("Subtraction of %s and %s is: ",argv[1],argv[3]);
                    }
                }
            }
            //Print the result list
            print_list(r_head);
            break;
        }
        //Case to implement Multiplication
        case '*':
        {
            mul(&head1,&tail1,&head2,&tail2,&r_head,&r_tail);
            if((sign1==0 && sign2==0) || (sign1==1&&sign2==1))
            {  
                printf("Multiplication of %s and %s is: ",argv[1],argv[3]);
            }
            else
            {
                printf("Multiplication of %s and %s is: -",argv[1],argv[3]);
            }
            //Print the result list
            print_list(r_head);
            break;
        }
        //Case to implement Division
        case '/':
        {
            if(cmp==1)
            {
                printf("Division of %s and %s is: 0\n",argv[1],argv[3]);
            }
            else if(cmp==-1)
            {
                if((sign1==0 && sign2==0) || (sign1==1&&sign2==1))
                {
                    printf("Division of %s and %s is: 1\n",argv[1],argv[3]);
                }
                else
                {
                    printf("Division of %s and %s is: -1\n",argv[1],argv[3]);
                }
            }
            else if(cmp==0)
            {
                divide(&head1,&tail1,&head2,&tail2,&r_head,&r_tail);
                if((sign1==0 && sign2==0) || (sign1==1&&sign2==1))
                {
                    printf("Division of %s and %s is: ",argv[1],argv[3]);
                }
                else
                {
                    printf("Division of %s and %s is: -",argv[1],argv[3]);
                }
                //Print the result list
                print_list(r_head);
            }
            break;
        }
    }
}