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
	LRUCache( int capacity ):_capacity(capacity)
	{
	}

	int get(int key)
	{
		auto it = _cache.find(key);
		if( it != _cache.end() )
		{
			update_cache( it->second );
			//_cache[key] = _dq.begin();
			return it->second->value;
		}

		return -1;
	}

	void put( int key, int value )
	{
		if( get( key ) != -1 )
		{
			_cache[key]->value = value;
			return;
		}

		if( _cache.size() == _capacity )
		{
			auto it = _dq.rbegin();
			int orig_key = it->key;
			it->value = value;
			it->key = key;
			update_cache( _cache[orig_key] );
			_cache[key] = _dq.begin();
			_cache.erase( orig_key );
			return;
		}

		insert_cache( key, value );
		_cache[key] = _dq.begin();
	}

private:
	struct node{
		node( int k, int v ):key(k),value(v){}
		int key;
		int value;
	};
	list<node> _dq;
	unordered_map<int,list<node>::iterator> _cache;
	size_t _capacity;

	void update_cache( list<node>::iterator &it )
	{
		_dq.splice( _dq.begin(), _dq, it );
	}

	void insert_cache( int key, int value )
	{
		_dq.emplace_front( key, value );
	}
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
