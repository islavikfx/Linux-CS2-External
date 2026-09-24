#pragma once
#include <cstdint>
#include <string>


namespace Offsets {
    inline uintptr_t xray = 0x1a39244 + 0x0; // # September 24, 2026
}


std::string xrayasm = R"(
Dump of assembler code from 0x7a95b4e6c230 to 0x7a95b4e6c258:
   0x00007a95b4e6c230:	mov    r8d,DWORD PTR [rax+0x58]
   0x00007a95b4e6c234:	test   r8d,r8d
   0x00007a95b4e6c237:	sete   bl
   0x00007a95b4e6c23a:	test   rsi,rsi
   0x00007a95b4e6c23d:	sete   al
   0x00007a95b4e6c240:	or     bl,al
   0x00007a95b4e6c242:	je     0x7a95b4e6c258
   0x00007a95b4e6c244:	xor    eax,eax
   0x00007a95b4e6c246:	add    rsp,0x28
   0x00007a95b4e6c24a:	pop    rbx
   0x00007a95b4e6c24b:	pop    r12
   0x00007a95b4e6c24d:	pop    r13
   0x00007a95b4e6c24f:	pop    r14
   0x00007a95b4e6c251:	pop    r15
   0x00007a95b4e6c253:	pop    rbp
   0x00007a95b4e6c254:	ret
   0x00007a95b4e6c255:	nop    DWORD PTR [rax]
End of assembler dump.
rax=0x3274aebb4c8
rbx=0x327e3597000
rcx=0x7ffd689a11d0
rdx=0x7ffd689a11e0
rsi=0x327de821000
rdi=0x327e3597000
rbp=0x7ffd689a1170
rsp=0x7ffd689a1120
rip=0x7a95b4e6c234
r8=0x1
r9=0x7ffd689a11d8
r10=0x0
r11=0x9
r12=0x7a95b79366a8
r13=0x327de821000
r14=0x7ffd689a11dc
r15=0x7ffd689a11cf)";
