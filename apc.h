#ifndef DLL_H
#define DLL_L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SUCCESS 0
#define FAILURE -1

typedef struct node
{
	int data;
	struct node *prev;
	struct node *next;
}Dlist;

int validate(const char *str);
void free_list(Dlist **head);
int compare(Dlist *head1,Dlist *head2);
int is_zero(Dlist *head);
int convert_str_to_dll(const char* str,Dlist **head,Dlist **tail);
int insert_last(Dlist **head, Dlist **tail, int data);
int insert_first(Dlist **head, Dlist **tail, int data);
void print_list(Dlist *head);
void add(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **r_head, Dlist **r_tail);
void sub(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **r_head, Dlist **r_tail);
void divide(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **r_head, Dlist **r_tail);
void mul(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **r_head, Dlist **r_tail);

#endif