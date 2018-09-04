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
	vector<ListNode*> mergedV;
	for( auto &node : lists )
	{
		if( node == NULL )
		{
			continue;
		}
		for( ; node; )
		{
			auto next = node->next;
			if( mergedV.empty() )
			{
				mergedV.push_back(node);
			}
			else
			{
				auto it = upper_bound( mergedV.begin(), mergedV.end(), node->val,
						[]( int val, ListNode *n2 )->bool { return val < n2->val;} );
				if( it == mergedV.end() )
				{
					for( ; node; node = node->next )
					{
						mergedV.push_back( node );
					}
					break;
				}
				node->next = *it;
				if( it != mergedV.begin() )
				{
					auto prev = it - 1; 
					(*prev)->next = node;
				}
				mergedV.insert( it, node );
			}
			node = next;
		}
	}
	return mergedV.empty() ? NULL : mergedV.front();
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
