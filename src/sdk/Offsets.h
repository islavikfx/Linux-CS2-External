#pragma once
#include <cstdint>

namespace Offsets {
    inline uintptr_t xray = 0x18949d2; // # mar 5, 2026
}

std::string xrayasm = R"(
Dump of assembler code from 0x72aa14e949be to 0x72aa14e949e6:
   0x000072aa14e949be:	add    BYTE PTR [rbx-0x247ab800],cl
   0x000072aa14e949c4:	sete   r12b
   0x000072aa14e949c8:	test   eax,eax
   0x000072aa14e949ca:	sete   al
   0x000072aa14e949cd:	or     r12b,al
   0x000072aa14e949d0:	je     0x72aa14e949e8
   0x000072aa14e949d2:	xor    eax,eax
   0x000072aa14e949d4:	add    rsp,0x38
   0x000072aa14e949d8:	pop    rbx
   0x000072aa14e949d9:	pop    r12
   0x000072aa14e949db:	pop    r13
   0x000072aa14e949dd:	pop    r14
   0x000072aa14e949df:	pop    r15
   0x000072aa14e949e1:	pop    rbp
   0x000072aa14e949e2:	ret
   0x000072aa14e949e3:	nop    DWORD PTR [rax+rax*1+0x0]
End of assembler dump.
)";