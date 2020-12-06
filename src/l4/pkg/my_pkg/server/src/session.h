#ifndef _SESSION_H_
#define _SESSION_H_

#include <l4/sys/capability>
#include <l4/sys/cxx/ipc_iface>
#include <l4/sys/cxx/ipc_array>


enum {
  SUCCESS,
  FAIL 
};

struct Msg : L4::Kobject_t<Msg, L4::Kobject>
{
  L4_INLINE_RPC(int, printBff, (L4::Ipc::String<> buff)); 

  typedef L4::Typeid::Rpcs<printBff_t> Rpcs;
};

#endif //end of session-header
