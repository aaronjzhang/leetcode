#include <stdio.h>
#include <stdlib.h>

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) :val(x), next(NULL){}
};

ListNode *addTwoNumbers( ListNode *l1, ListNode *l2 )
{
	ListNode *result = NULL;
	ListNode **tail = &result;
	int carry = 0;

	ListNode *node1 = l1;
	ListNode *node2 = l2;

	for( ; node1 || node2; )
	{
		int n1 = node1 ? node1->val : 0;
		int n2 = node2 ? node2->val : 0;

		int val = n1 + n2 + carry;

		ListNode *p = new ListNode( val % 10 );
		*tail = p;
		tail = &((*tail)->next);
		
		carry = val / 10;

		node1 = node1 ? node1->next : NULL;
		node2 = node2 ? node2->next : NULL;
	}

	if( carry )
	{
		ListNode *p = new ListNode( carry );
		*tail = p;
	}

	return result;
}


