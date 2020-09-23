IMPLEMENTATION [arm && mp && pf_s32 && !arm_psci]:

#include "cpu.h"
#include "mem.h"
#include "mmio_register_block.h"
#include "kmem.h"
#include "mem_unit.h"

#include <cstdio>

PUBLIC static
void
Platform_control::boot_ap_cpus(Address phys_tramp_mp_addr)
{
  Mmio_register_block s(Kmem::mmio_remap(0x80000000, 8));
  s.r<64>(0) = phys_tramp_mp_addr;
  //s.r<64>(0xfff8) = phys_tramp_mp_addr;
  Mem::dsb();
  Mem_unit::clean_dcache();

  for (int i = 0; i < 4; ++i)
    {
      asm volatile("sev" : : : "memory");
      printf("-------------> waiting for cpu %d\n", i);
      while (!Cpu::online(Cpu_number(i)))
        {
          Mem::barrier();
          Proc::pause();
        }
      printf("=============> cpu %d appeared\n", i);
    }
}

// ------------------------------------------------------------------------
IMPLEMENTATION [arm && mp && pf_s32 && arm_psci]:

#include "cpu.h"
#include "mem.h"

#include <cstdio>

PUBLIC static
void
Platform_control::boot_ap_cpus(Address phys_tramp_mp_addr)
{
  for (int i = 0; i < 4; ++i)
    {
      unsigned coreid[4] = { 0x0, 0x1, 0x100, 0x101 };
      int r = cpu_on(coreid[i], phys_tramp_mp_addr);
      if (r)
        {
          if (r != Psci_already_on)
            printf("CPU%d boot-up error: %d\n", i, r);
          continue;
        }

      while (!Cpu::online(Cpu_number(i)))
        {
          Mem::barrier();
          Proc::pause();
        }
    }
}
