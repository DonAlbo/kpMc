PKGDIR ?= ../..
L4DIR  ?= $(PKGDIR)/../..

TARGET                = ex_task_server ex_task_client

SRC_CC_ex_task_server = server.cc
SRC_CC_ex_task_client = client.cc

REQUIRES_LIBS         = cxx_libc_io cxx_io
DEPENDS_PKGS          = $(REQUIRES_LIBS)

include $(L4DIR)/mk/prog.mk
