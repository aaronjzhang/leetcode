#include <vector>
#include <algorithm>
#include <queue>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;
//Definition for singly-linked list
struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x): val(x),next(NULL) {}
};

ListNode* mergeKLists( vector<ListNode*> &lists )
{
	auto compare = []( ListNode *node1, ListNode *node2 ) { return node1->val > node2->val;};
	priority_queue< ListNode*, vector<ListNode*>, decltype(compare) > heap(compare);	
	for( auto &node : lists )
	{
		if( node )
		{
			heap.push( node );
		}
	}
	ListNode *head = NULL;
	ListNode **p = &head;
	while( !heap.empty() )
	{
		ListNode *node = heap.top(); 
		heap.pop();
		*p = node;
		if( node->next )
		{
			heap.push( node->next );
		}
		p = &(*p)->next;
	}
	return head;
}

int main()
{
	FILE *input_file = fopen( "input.txt", "r" );
	if( input_file == NULL )
	{
		printf("input.txt doesn't exist!\n");
		return 1;
	}

	vector< ListNode* > lists;
	char *line = NULL;
	size_t n = 0;
	while ( getline( (char**)&line, &n, input_file ) > 0 )
	{
		printf( "%s", line );
		string str = line;
		free(line);
		line = NULL;
		string delimiters = "->";
		size_t current;
		size_t next = -2;
		ListNode **p = NULL;
		lists.push_back( NULL );
		p = &lists.back();
		do{
			current = next + 2;
			next = str.find_first_of( delimiters, current );
			string token = str.substr( current, next - current );
			printf( "%s ",token.c_str() );
			int val = atoi( token.c_str() );
			*p = new ListNode( val );
			p = &(*p)->next;
		}while( next != string::npos );
		printf( "\n" );
	}

	ListNode *list = mergeKLists( lists );	
	ListNode *p = list;
	for( ; p; p = p->next )
	{
		printf("%d ", p->val );
	}
	printf( "\n" );

	/*

	for( auto &node : lists )
	{
		ListNode *p = node;
		for( ; p; p = p->next )
		{
			printf("%d ", p->val );
		}
		printf( "\n" );
	}

	*/
	return 0;
}
