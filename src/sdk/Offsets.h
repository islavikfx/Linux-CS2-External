#pragma once
#include <cstdint>
#include <string>


namespace Offsets {
    inline uintptr_t xray = 0x1a3a964 + 0x0; // # September 26, 2026
}


std::string xrayasm = R"(
Dump of assembler code from 0x76e3f4e69950 to 0x76e3f4e69978:
   0x000076e3f4e69950:	mov    r8d,DWORD PTR [rax+0x58]
   0x000076e3f4e69954:	test   r8d,r8d
   0x000076e3f4e69957:	sete   bl
   0x000076e3f4e6995a:	test   rsi,rsi
   0x000076e3f4e6995d:	sete   al
   0x000076e3f4e69960:	or     bl,al
   0x000076e3f4e69962:	je     0x76e3f4e69978
   // 0x000076e3f4e69964:	xor    eax,eax
   0x000076e3f4e69966:	add    rsp,0x28
   0x000076e3f4e6996a:	pop    rbx
   0x000076e3f4e6996b:	pop    r12
   0x000076e3f4e6996d:	pop    r13
   0x000076e3f4e6996f:	pop    r14
   0x000076e3f4e69971:	pop    r15
   0x000076e3f4e69973:	pop    rbp
   0x000076e3f4e69974:	ret
   0x000076e3f4e69975:	nop    DWORD PTR [rax]
rax=0x248b8e8b600
rbx=0x249481bb000
rcx=0x7ffd41034120
rdx=0x7ffd41034130
rsi=0x2490c9db000
rdi=0x249481bb000
rbp=0x7ffd410340c0
rsp=0x7ffd41034070
rip=0x76e3f4e69954
r8=0x1
r9=0x7ffd41034128
r10=0x0
r11=0x9
r12=0x76e3f79363c8
r13=0x2490c9db000
r14=0x7ffd4103412c
r15=0x7ffd4103411f
End of assembler dump.
76e3f342f000-76e3f409f000 r--p 00000000 00:3d 14555348 ../bin/linuxsteamrt64/libclient.so
python3 -c 'print(hex(0x000076e3f4e69964 - 0x76e3f342f000))'
0x1a3a964)";
