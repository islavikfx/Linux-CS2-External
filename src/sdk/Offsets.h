#pragma once
#include <cstdint>


// # pgrep -f cs2 sudo cat /proc/X/maps | grep libclient.so
// # python3 -c 'print(hex(0x00007876ca4da4f2 - 0x7876c8c00000))'
namespace Offsets {
    inline uintptr_t xray = 0x18da4f2; // # may 21, 2026
}


std::string xrayasm = R"(
Dump of assembler code from 0x7876ca4da4de to 0x7876ca4da506:
   0x00007876ca4da4de:	add    BYTE PTR [rbx-0x247ab800],cl
   0x00007876ca4da4e4:	sete   r12b
   0x00007876ca4da4e8:	test   eax,eax
   0x00007876ca4da4ea:	sete   al
   0x00007876ca4da4ed:	or     r12b,al
   0x00007876ca4da4f0:	je     0x7876ca4da508
   0x00007876ca4da4f2:	xor    eax,eax
   0x00007876ca4da4f4:	add    rsp,0x38
   0x00007876ca4da4f8:	pop    rbx
   0x00007876ca4da4f9:	pop    r12
   0x00007876ca4da4fb:	pop    r13
   0x00007876ca4da4fd:	pop    r14
   0x00007876ca4da4ff:	pop    r15
   0x00007876ca4da501:	pop    rbp
   0x00007876ca4da502:	ret
   0x00007876ca4da503:	nop    DWORD PTR [rax+rax*1+0x0]
End of assembler dump.
)";
