#include <iostream>
#include <queue>
#include <thread>
#include <assert.h>
#include <exception>

#include "hirediscommand.h"

using namespace RedisCluster;
using std::string;
using std::cout;
using std::cerr;
using std::endl;

void processClusterCommand()
{
	Cluster<redisContext>::ptr_t cluster_p;
	printf("%s:%d\n", __func__, __LINE__);

	cluster_p = HiredisCommand<>::createCluster( "127.0.0.1", 6379 );
	printf("%s:%d\n", __func__, __LINE__);

	auto reply = HiredisCommand<>::AltCommand( cluster_p, "FOO", "SET %s %s", "FOO", "BAR1" );
	printf("%s:%d\n", __func__, __LINE__);

	if( reply->type == REDIS_REPLY_STATUS  || reply->type == REDIS_REPLY_ERROR )
	{
		cout << " Reply to SET FOO BAR " << endl;
		cout << reply->str << endl;
	} else {
		cout << "reply->type:" << reply->type << endl;
	}

	delete cluster_p;
}

int main(int argc, const char * argv[])
{
	try
	{
		processClusterCommand();
	} 
	catch (const RedisCluster::ClusterException &e )
	{
		cout << "Cluster exception: " << e.what() << endl;
	}

	return 0;
}
