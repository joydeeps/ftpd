#include "server.h"
#include "monitor.h"

int main()
{
  myftp::Server server;
  myftp::Monitor monitor(&server);

  return 0;
}
