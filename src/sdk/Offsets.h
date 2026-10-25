#pragma once
#include <cstdint>
#include <string>


namespace Offsets {

    inline uintptr_t xray = 0x1a3ae24;
    inline uintptr_t cross = 0x1bf00a3;
    inline constexpr const char* datee = "25 October 2026.";
}

namespace Patchs {

    inline uint8_t xray_off[]  = {0x31, 0xc0};
    inline uint8_t xray_set[]  = {0x90, 0x90}; // # nop; nop
    inline uint8_t cross_off[] = {0x0f, 0xb7, 0x05, 0x86, 0xe7, 0xdb, 0x02};
    inline uint8_t cross_set[] = {0x66, 0xb8, 0x01, 0x00, 0x90, 0x90, 0x90}; // # mov ax, 1; nop; nop; nop
    inline constexpr size_t xray_len  = sizeof(xray_off);
    inline constexpr size_t cross_len = sizeof(cross_off);
}


std::string asmm = R"(
Dump of assembler code from 0x7fc474e61e10 to 0x7fc474e61e38:
   0x00007fc474e61e10:	mov    r8d,DWORD PTR [rax+0x58]
   0x00007fc474e61e14:	test   r8d,r8d
   0x00007fc474e61e17:	sete   bl
   0x00007fc474e61e1a:	test   rsi,rsi
   0x00007fc474e61e1d:	sete   al
   0x00007fc474e61e20:	or     bl,al
   0x00007fc474e61e22:	je     0x7fc474e61e38
   // 0x00007fc474e61e24:	xor    eax,eax
   0x00007fc474e61e26:	add    rsp,0x28
   0x00007fc474e61e2a:	pop    rbx
   0x00007fc474e61e2b:	pop    r12
   0x00007fc474e61e2d:	pop    r13
   0x00007fc474e61e2f:	pop    r14
   0x00007fc474e61e31:	pop    r15
   0x00007fc474e61e33:	pop    rbp
   0x00007fc474e61e34:	ret
   0x00007fc474e61e35:	nop    DWORD PTR [rax]
End of assembler dump.
Dump of assembler code from 0x7fc4750170a3 to 0x7fc4750170cb:
   // 0x00007fc4750170a3:	movzx  eax,WORD PTR [rip+0x2dbe786]
   0x00007fc4750170aa:	mov    WORD PTR [rbx],ax
   0x00007fc4750170ad:	mov    eax,0x1
   0x00007fc4750170b2:	mov    rbx,QWORD PTR [rbp-0x8]
   0x00007fc4750170b6:	leave
   0x00007fc4750170b7:	ret
   0x00007fc4750170b8:	nop    DWORD PTR [rax+rax*1+0x0]
   0x00007fc4750170c0:	xor    eax,eax
   0x00007fc4750170c2:	ret
   0x00007fc4750170c3:	int3
   0x00007fc4750170c4:	int3
End of assembler dump.)";
