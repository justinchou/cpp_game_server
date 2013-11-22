#include "redisclient.h"

void test_cluster_dbsize(redis::client & c)
{
  redis::client::int_type count;
  for(size_t i=0; i < c.connections().size(); i++)
  {
    redis::client::int_type curSize = c.dbsize( c.connections()[i] );
    std::cerr << "DB#" << i << " contains " << curSize << " keys" << std::endl;
    count += curSize;
  }
}

boost::shared_ptr<redis::client> init_non_cluster_client()
{
  const char* c_host = getenv("REDIS_HOST");
  std::string host = "localhost";
  if(c_host)
    host = c_host;
  return boost::shared_ptr<redis::client>( new redis::client(host) );
}

boost::shared_ptr<redis::client> init_cluster_client()
{
  std::vector<redis::connection_data> redis_server;

  const char* c_host = getenv("REDIS_HOST");
  std::string host = "localhost";
  if(c_host)
    host = c_host;
  
  {
    redis::connection_data con;
    con.host = host;
    con.port = 6379;
    con.dbindex = 14;
    redis_server.push_back(con);
  }
  {
    redis::connection_data con;
    con.host = host;
    con.port = 6380;
    con.dbindex = 14;
    redis_server.push_back(con);
  }
  {
    redis::connection_data con;
    con.host = host;
    con.port = 6381;
    con.dbindex = 14;
    redis_server.push_back(con);
  }
}
