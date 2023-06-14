#include "llist.h"
#include "stdio.h"
#include "stdlib.h"

void	print_int(void *content)
{
	printf("[%d]->", *(int *)content);
}

void	*new_int(int n)
{
	int *res = malloc(sizeof(int));
	*res = n;
	return (res);
}

void print_choice(void)
{
	puts("1 : print list (with llstiter)");
	puts("2 : llstaddback, add node to end of list");
	puts("3 : llstaddfront, add node in begin of list");
	puts("4 : llstaddafter, add node after a node of list");
	puts("5 : llstaddbefore, add node before a node of list");
	puts("6 : llstsize, get size of list");
	puts("7 : llstfirst, get first node of list");
	puts("8 : llstlast, get last node to list");
	puts("0 : Quit");
}

int main(void)
{
	t_llist	*llist = NULL;
	int		choice;
	int		n;

	puts("TEST MENU");
	while (1)
	{
		print_choice();
		scanf("%d", &choice);
		switch(choice)
		{
			case 1 :
				llstiter(llist, print_int);
				break;
			case 2 :
				scanf("%d", &n);
				llstadd_back(&llist, llstnew(new_int(n)));
				break;
			case 3 :
				scanf("%d", &n);
				llstadd_front(&llist, llstnew(new_int(n)));
				break;
			default :
				puts("Bad input");

		}
		puts(""), puts("");
	}
}