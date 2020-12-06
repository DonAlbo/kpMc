#include <l4/re/env>
#include <l4/re/util/cap_alloc>
#include <l4/re/util/object_registry>
#include <l4/re/util/br_manager>
#include <l4/sys/cxx/ipc_epiface>

#include <cstdio>

#include <l4/sys/cxx/ipc_string>
#include <l4/cxx/string.h>
#include <l4/cxx/iostream>

#include "session.h"


static L4Re::Util::Registry_server<L4Re::Util::Br_manager_hooks> server;

class Log_server : public L4::Epiface_t<Log_server, Msg>
{
  public:
    int op_printBff(Msg::Rights, L4::Ipc::String<> bff)
    {
      printf("Here is a message.\n");
      printf("The length is %ld\n", bff.length - 1);
      L4::String str_cp { bff.data};
      L4::cout << str_cp << "\n";

      return SUCCESS;
    }
};

int main()
{
  static Log_server logger;
  if (!server.registry()->register_obj(&logger, "logger_svr").is_valid())
  {
    printf("Could not register service for logging messages.\n");
    return FAIL;
  }
  printf("Messages sent to logger service will be printed in console.\n");

  //Wain loop
  server.loop();

  return SUCCESS;
  
}
