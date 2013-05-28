#include "gdsp_functionmanager_api.h"
#include "gdsp_functionmanager_impl.h"

const unsigned long gdsp_default_irq_jt_code[SIZEOF_DEFAULT_IRQ_JT_CODE] = {
  GDSP_32BITOPCODE(RTI_INSTR,NOP_INSTR),
  GDSP_32BITOPCODE(RTI_INSTR,NOP_INSTR),
  GDSP_32BITOPCODE(RTI_INSTR,NOP_INSTR),
  GDSP_32BITOPCODE(RTI_INSTR,NOP_INSTR),
  GDSP_32BITOPCODE(RTI_INSTR,NOP_INSTR),
  GDSP_32BITOPCODE(RTI_INSTR,NOP_INSTR)
};  


const unsigned long gdsp_context_save_code[SIZEOF_CONTEXT_SAVE_CODE] = {
  0xa0179fec ,                                                     // sp=sp+0x1ec, store d11,dm(sp +0x0
  0xa091a053 ,                                                     // store d9,dm(sp +0x1), store d8,dm(sp +0x2)
  0xa13da0d5 ,                                                     // store d10,dm(sp +0x3), store lr,dm(sp +0x4)
  0xa1a9a16d ,                                                     // store p6,dm(sp +0x5), store p4,dm(sp +0x6)
  0xa221a1e5 ,                                                     // store p2,dm(sp +0x7), store p0,dm(sp +0x8)
  0xa2a7a263 ,                                                     // store p1,dm(sp +0x9), store p3,dm(sp +0xa)
  0xa31da2eb ,                                                     // store p5,dm(sp +0xb), store l2,lm(sp +0xc)
  0xa41ba399 ,                                                     // store l0,lm(sp +0xe), store l1,lm(sp +0x10)
  0xb75fa49f ,                                                     // store l3,lm(sp +0x12), store isr,dm(--sp)
  0xb01ab77f ,                                                     // store ilr,dm(--sp), // d0=ls0
  //0xefb00000|ADDR_IRQ_JUMPTABLE + IRQ_NR*2 ,    // cnd=cmp_ne(&irq_jumptable,d0)
  0x0000 | CND_CMP_NEG, // Replace runtime
  0xba057fff ,                                                     // nop, jcar 0x5,cnd
  0x0001ffc0 ,                                                     // load d0,dm(sp +0x1),
  0x0c00e500 ,                                                     // d0=b_or(0xc,d0)
  0xffc1bc0e ,                                                     // jadr 0xe, store d0,
  0xb01b0001 ,                                                     // dm(sp +0x1), d0=ls1
  //0xefb00000|ADDR_IRQ_JUMPTABLE + IRQ_NR*2 ,    // cnd=cmp_ne(&irq_jumptable,d0)
  0x0000 | CND_CMP_NEG , // Replace runtime   // cnd=cmp_ne(&irq_jumptable,d0)
  0xba0b7fff ,                                                     // nop, jcar 0xb,cnd
  0x0001ffc0 ,                                                     // load d0,dm(sp +0x1)
  0xf300e4ff ,                                                     // d0=b_and(0xfff3,d0)
  0xffc17fff ,                                                     // nop, store d0,
  0xadc00001 ,                                                     // dm(sp +0x1), load d0,dm(sp)
  0xfe00e0ff ,                                                     // d0=add(0xfffe,d0)
  0xadc17fff ,                                                     // nop, store d0,dm(sp)
  0xb73e7fff ,                                                     // nop, load ilr,dm(sp++)
  0x7fffb71e ,                                                     // load isr,dm(sp++), nop
  0xb77db77d ,                                                     // store lr, dm(--sp), store lr, dm(--sp) // double store of lr to make sure it is stored 32bit aligned.
  0xb777b775 ,                                                     // store ls0, dm(--sp), store ls1, dm(--sp)
  0xb77bb779 ,                                                     // store le0, dm(--sp), store le1, dm(--sp)
  0xb773b771 ,                                                     // store lc0, dm(--sp), store lc1, dm(--sp)
  0xb741b75d ,                                                     // store sr, dm(--sp), store d0, dm(--sp)
  0x0001ffc0 ,                                                     // load d0, dm(sp+1) // fix LF bits in SR on stack
  0x0c00e500 ,                                                     // d0 = b_or(0x000C,d0)
  0xffc17fff ,                                                     // nop, store d0,
  0x81c00001 ,                                                     // dm(sp+1), load d0, dm(sp++)
  0x7fffb71c ,                                                     // load sr, dm(sp++), nop //extra NOP to make sure that context_save + fix_loopregs + loopregs_save end at 32bit aligned code address for SCP code 
  0xb77fb75f                                                       // store isr,dm(--sp), store ilr,dm(--sp)
};  

const unsigned long gdsp_context_restore_code[SIZEOF_CONTEXT_RESTORE_CODE] = {
  0xb73ebfde,                                                      // di, load ilr,dm(sp++)
  0x7fffb71e,                                                      // load isr,dm(sp++), nop
  0x81f081f2 ,                                                     // load lc1, dm(sp++), load lc0, dm(sp++)
  0x81f881fa ,                                                     // load le1, dm(sp++), load le0, dm(sp++)
  0x81f481f6 ,                                                     // load ls1, dm(sp++), load ls0, dm(sp++)
  0xb73cb73c ,                                                     // load lr, dm(sp++), load lr, dm(sp++)
  0xa0167fff ,                                                     // nop, load d11,dm(sp +0x0)
  0xa090a052 ,                                                     // load d9,dm(sp +0x1), load d8,dm(sp +0x2)
  0xa13ca0d4 ,                                                     // load d10,dm(sp +0x3),load lr,dm(sp +0x4)
  0xa1a8a16c ,                                                     // load p6,dm(sp +0x5), load p4,dm(sp +0x6)
  0xa220a1e4 ,                                                     // load p2,dm(sp +0x7), load p0,dm(sp +0x8)
  0xa2a6a262 ,                                                     // load p1,dm(sp +0x9), load p3,dm(sp +0xa)
  0xa31ca2ea ,                                                     // load p5,dm(sp +0xb), load l2,lm(sp +0xc)
  0xa41aa398 ,                                                     // load l0,lm(sp +0xe), load l1,lm(sp +0x10)
  0x9e14a49e ,                                                     // load l3,lm(sp +0x12), sp=sp+0x14  
  0x7fffdfff ,                                                      // rti | nop
};  
