#pragma once
#include <cstdint>
#include <string>


namespace Offsets {

    inline uintptr_t xray = 0x1a3c064;
    inline uintptr_t cross = 0x1bf12e3;
    inline constexpr const char* datee = "30 October 2026.";
}

namespace Patchs {

    inline uint8_t xray_off[]  = {0x31, 0xc0};
    inline uint8_t xray_set[]  = {0x90, 0x90}; // # nop; nop
    inline uint8_t cross_off[] = {0x0f, 0xb7, 0x05, 0xc6, 0xfd, 0xdb, 0x02};
    inline uint8_t cross_set[] = {0x66, 0xb8, 0x01, 0x00, 0x90, 0x90, 0x90}; // # mov ax, 1; nop; nop; nop
    inline constexpr size_t xray_len  = sizeof(xray_off);
    inline constexpr size_t cross_len = sizeof(cross_off);
}


std::string asmm = R"(Dump of assembler code from 0x7081fce60050 to 0x7081fce60078:
   0x00007081fce60050:	mov    r8d,DWORD PTR [rax+0x58]
   0x00007081fce60054:	test   r8d,r8d
   0x00007081fce60057:	sete   bl
   0x00007081fce6005a:	test   rsi,rsi
   0x00007081fce6005d:	sete   al
   0x00007081fce60060:	or     bl,al
   0x00007081fce60062:	je     0x7081fce60078
   // 0x00007081fce60064:	xor    eax,eax
   0x00007081fce60066:	add    rsp,0x28
   0x00007081fce6006a:	pop    rbx
   0x00007081fce6006b:	pop    r12
   0x00007081fce6006d:	pop    r13
   0x00007081fce6006f:	pop    r14
   0x00007081fce60071:	pop    r15
   0x00007081fce60073:	pop    rbp
   0x00007081fce60074:	ret
   0x00007081fce60075:	nop    DWORD PTR [rax]
End of assembler dump.
Dump of assembler code from 0x72d0810152e3 to 0x72d08101530b:
   // 0x000072d0810152e3:	movzx  eax,WORD PTR [rip+0x2dbfdc6]        # 0x72d083dd50b0
   0x000072d0810152ea:	mov    WORD PTR [rbx],ax
   0x000072d0810152ed:	mov    eax,0x1
   0x000072d0810152f2:	mov    rbx,QWORD PTR [rbp-0x8]
   0x000072d0810152f6:	leave
   0x000072d0810152f7:	ret
   0x000072d0810152f8:	nop    DWORD PTR [rax+rax*1+0x0]
   0x000072d081015300:	xor    eax,eax
   0x000072d081015302:	ret
   0x000072d081015303:	int3
   0x000072d081015304:	int3
   0x000072d081015305:	int3
   0x000072d081015306:	int3
   0x000072d081015307:	int3
   0x000072d081015308:	int3
   0x000072d081015309:	int3
   0x000072d08101530a:	int3
End of assembler dump.
// 0x0f, 0xb7, 0x05, 0xff, 0x00, 0x00, 0x00 - rdx FF)";
