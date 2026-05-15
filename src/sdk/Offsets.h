#pragma once
#include <cstdint>


// # pgrep -f cs2 sudo cat /proc/X/maps | grep libclient.so
// # python3 -c 'print(hex(0x000070f06249d1f2 - 0x70f060c00000))'
namespace Offsets {
    inline uintptr_t xray = 0x189d1f2; // # may 15, 2026
}


std::string xrayasm = R"(
Dump of assembler code from 0x70f06249d1df to 0x70f06249d207:
   0x000070f06249d1df:	mov    eax,DWORD PTR [rax]
   0x000070f06249d1e1:	test   rbx,rbx
   0x000070f06249d1e4:	sete   r12b
   0x000070f06249d1e8:	test   eax,eax
   0x000070f06249d1ea:	sete   al
   0x000070f06249d1ed:	or     r12b,al
   0x000070f06249d1f0:	je     0x70f06249d208
   0x000070f06249d1f2:	xor    eax,eax
   0x000070f06249d1f4:	add    rsp,0x38
   0x000070f06249d1f8:	pop    rbx
   0x000070f06249d1f9:	pop    r12
   0x000070f06249d1fb:	pop    r13
   0x000070f06249d1fd:	pop    r14
   0x000070f06249d1ff:	pop    r15
   0x000070f06249d201:	pop    rbp
   0x000070f06249d202:	ret
   0x000070f06249d203:	nop    DWORD PTR [rax+rax*1+0x0]
End of assembler dump.
)";
