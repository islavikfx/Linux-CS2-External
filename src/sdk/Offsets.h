#pragma once
#include <cstdint>


// # pgrep -f cs2; sudo cat /proc/X/maps | grep libclient.so; python3 -c 'print(hex(0x79f8de49c8e2 - 0x79f8dcc00000))'
namespace Offsets {
    inline uintptr_t xray = 0x189c8e2; // # may 2, 2026
}


std::string xrayasm = R"(
Dump of assembler code from 0x79f8de49c8cf to 0x79f8de49c8f7:
   0x000079f8de49c8cf:	mov    eax,DWORD PTR [rax]
   0x000079f8de49c8d1:	test   rbx,rbx
   0x000079f8de49c8d4:	sete   r12b
   0x000079f8de49c8d8:	test   eax,eax
   0x000079f8de49c8da:	sete   al
   0x000079f8de49c8dd:	or     r12b,al
   0x000079f8de49c8e0:	je     0x79f8de49c8f8
   0x000079f8de49c8e2:	xor    eax,eax
   0x000079f8de49c8e4:	add    rsp,0x38
   0x000079f8de49c8e8:	pop    rbx
   0x000079f8de49c8e9:	pop    r12
   0x000079f8de49c8eb:	pop    r13
   0x000079f8de49c8ed:	pop    r14
   0x000079f8de49c8ef:	pop    r15
   0x000079f8de49c8f1:	pop    rbp
   0x000079f8de49c8f2:	ret
   0x000079f8de49c8f3:	nop    DWORD PTR [rax+rax*1+0x0]
End of assembler dump.
)";
