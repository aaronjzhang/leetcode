#include <cstdio>
#include <cstdlib>
#include <unordered_map>
#include <list>
#include <fstream>
#include <regex>
#include <vector>
#include <assert.h>

using namespace std;
class LRUCache
{
public:
	LRUCache( int capacity ):_capacity(capacity),_lru_list(NULL),_lru_tail(NULL)
	{
	}

	int get(int key)
	{
		auto got = _cache.find( key );
		if( got == _cache.end() )
		{
			return -1; 
		}

		link_node *node = got->second;	
		if( node == _lru_list )
		{
			return node->_value;
		}

		if( node->_next )
		{
			node->_next->_prev = node->_prev;
			node->_prev->_next = node->_next;
		}
		else
		{
			node->_prev->_next = NULL;
			_lru_tail = node->_prev;
		}
		node->_next = _lru_list;
		_lru_list->_prev = node;

		_lru_list = node;
		_lru_list->_prev = NULL;

		return node->_value;
	}

	void put( int key, int value )
	{
		if( get( key ) != -1 )
		{
			_cache[key]->_value = value;
			return;
		}

		if( _cache.size() == _capacity )
		{
			link_node *node = _lru_tail;
			if( _lru_list == _lru_tail )
			{
				_cache.erase( node->_key );
				node->_key = key;
				node->_value = value;
				_cache[key] = node;
				return;
			}
			_lru_tail = node->_prev;
			_lru_tail->_next = NULL;

			node->_next = _lru_list;
			node->_prev = NULL;
			_lru_list->_prev = node;
			_lru_list = node;

			_cache.erase( node->_key );
			node->_value = value;
			node->_key = key;
			_cache[key] = node;
			return;
		}
		link_node *node = new link_node( key, value );
		node->_next = _lru_list;
		node->_prev = NULL;
		if( _lru_list != NULL )
		{
			_lru_list->_prev = node;
		}

		_lru_list = node;
		if( _lru_tail == NULL )
		{
			_lru_tail = node;
		}
		_cache[key] = node;;
		return;
	}

private:
	struct link_node
	{
		link_node(int key, int value):_key(key),_value(value),_prev(NULL),_next(NULL){}
		int _key;
		int _value;
		link_node *_prev;
		link_node *_next;
	};

	size_t _capacity;
	unordered_map<int,link_node*> _cache;
	link_node *_lru_list;
	link_node *_lru_tail;
};

int main( int argc, char *argv[] )
{
	if( argc < 2 )
	{
		return 1;
	}

	ifstream ifs( argv[1] );
	if( !ifs.is_open() )
	{
		return 1;
	}
	
	char cline[1024*1024] = {0};
	ifs.getline( cline, sizeof(cline)-1);
	vector<string> cmds;

	regex e1("\"(\\w+)\"");
	string sline = cline;
	smatch m;
	while( regex_search( sline, m, e1 ) )
	{
		cmds.push_back( m[1].str() );
		sline = m.suffix().str();
	}

	ifs.getline( cline, sizeof(cline)-1);
	ifs.close();

	sline = cline;
	vector<int> args;
	regex e2("(\\d+)");
	while( regex_search( sline, m, e2 ) )
	{
		args.push_back( stoi(m[1].str()));
		sline = m.suffix();
	}

	string out("[");
	LRUCache *lru_cache = NULL;
	for( auto &cmd : cmds )
	{
		if( !cmd.compare("LRUCache") )
		{
			lru_cache = new LRUCache(args[0]);
			args.erase(args.begin());
			out.append("null,");
		}
		
		if( !lru_cache )
		{
			printf("no LRUCache\n");
			return 1;
		}

		if( !cmd.compare("get") )
		{
			out.append( to_string(lru_cache->get( args.front() ) ) );	
			out.append(",");
			args.erase( args.begin() );
		}

		if( !cmd.compare("put") )
		{
			out.append("null,");
			lru_cache->put( args[0], args[1] );
			args.erase(args.begin(), args.begin()+2);
		}
	}
	out.back() = ']';

	printf("%s\n", out.c_str());
	return 0;
}
