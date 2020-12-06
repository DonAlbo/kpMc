#include <l4/sys/err.h>
#include <l4/sys/types.h>
#include <l4/re/env>
#include <l4/re/util/cap_alloc>

#include <cstdio>

#include <l4/sys/cxx/ipc_string>
#include <l4/cxx/string.h>
#include <l4/cxx/iostream>

#include "session.h"


int main()
{
    printf("I want the server to receive the string:\n");
    L4::String str {"Hello"};
    L4::cout << str << "\n";
    L4::Ipc::String<> str_cp{str.p_str()};
    printf("\n");

    L4::Cap<Msg> server = L4Re::Env::env()->get_cap<Msg>("logger_svr");
    if (!server.is_valid())
    {
      printf("Logging server not accessible.\n");
      return FAIL; 
    }
    else
       printf("Logging server accessible.\n");

    if (server->printBff(str_cp) < SUCCESS )
    {
      printf("Failed to send packet.\n");
      return FAIL;
    }

    return SUCCESS;
}
