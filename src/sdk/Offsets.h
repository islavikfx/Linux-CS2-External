#pragma once
#include <cstdint>


// # pgrep -f cs2; sudo cat /proc/X/maps | grep libclient.so; python3 -c 'print(hex(0x73a8d649b8f2 - 0x73a8d4c00000))'
namespace Offsets {
    inline uintptr_t xray = 0x189b8f2; // # may 8, 2026
}


std::string xrayasm = R"(
Dump of assembler code from 0x73a8d649b8df to 0x73a8d649b907:
   0x000073a8d649b8df:	mov    eax,DWORD PTR [rax]
   0x000073a8d649b8e1:	test   rbx,rbx
   0x000073a8d649b8e4:	sete   r12b
   0x000073a8d649b8e8:	test   eax,eax
   0x000073a8d649b8ea:	sete   al
   0x000073a8d649b8ed:	or     r12b,al
   0x000073a8d649b8f0:	je     0x73a8d649b908
   0x000073a8d649b8f2:	xor    eax,eax
   0x000073a8d649b8f4:	add    rsp,0x38
   0x000073a8d649b8f8:	pop    rbx
   0x000073a8d649b8f9:	pop    r12
   0x000073a8d649b8fb:	pop    r13
   0x000073a8d649b8fd:	pop    r14
   0x000073a8d649b8ff:	pop    r15
   0x000073a8d649b901:	pop    rbp
   0x000073a8d649b902:	ret
   0x000073a8d649b903:	nop    DWORD PTR [rax+rax*1+0x0]
End of assembler dump.
)";
