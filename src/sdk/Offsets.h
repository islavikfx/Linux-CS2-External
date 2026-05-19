#pragma once
#include <cstdint>


// # pgrep -f cs2 sudo cat /proc/X/maps | grep libclient.so
// # python3 -c 'print(hex(0x00007a9ef24da572 - 0x7a9ef0c00000))'
namespace Offsets {
    inline uintptr_t xray = 0x18da572; // # may 19, 2026
}


std::string xrayasm = R"(
Dump of assembler code from 0x7a9ef24da55e to 0x7a9ef24da586:
   0x00007a9ef24da55e:	add    BYTE PTR [rbx-0x247ab800],cl
   0x00007a9ef24da564:	sete   r12b
   0x00007a9ef24da568:	test   eax,eax
   0x00007a9ef24da56a:	sete   al
   0x00007a9ef24da56d:	or     r12b,al
   0x00007a9ef24da570:	je     0x7a9ef24da588
   0x00007a9ef24da572:	xor    eax,eax
   0x00007a9ef24da574:	add    rsp,0x38
   0x00007a9ef24da578:	pop    rbx
   0x00007a9ef24da579:	pop    r12
   0x00007a9ef24da57b:	pop    r13
   0x00007a9ef24da57d:	pop    r14
   0x00007a9ef24da57f:	pop    r15
   0x00007a9ef24da581:	pop    rbp
   0x00007a9ef24da582:	ret
   0x00007a9ef24da583:	nop    DWORD PTR [rax+rax*1+0x0]
End of assembler dump.
)";
