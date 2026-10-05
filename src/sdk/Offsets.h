#pragma once
#include <cstdint>
#include <string>


namespace Offsets {

    inline uintptr_t xray = 0x1a37744;
    inline uintptr_t cross = 0x1be9223;
}

namespace Patchs {

    inline uint8_t xray_off[]  = {0x31, 0xc0}; // xor eax, eax
    inline uint8_t xray_set[]  = {0x90, 0x90}; // nop; nop
    inline uint8_t cross_off[] = {0x0f, 0xb7, 0x05, 0x26, 0xbc, 0xdb, 0x02}; // movzx eax, WORD PTR [rip+0x2dbbc26]
    inline uint8_t cross_set[] = {0x66, 0xb8, 0x01, 0x00, 0x90, 0x90, 0x90}; // mov ax, 1; nop; nop; nop
    inline constexpr size_t xray_len  = sizeof(xray_off);
    inline constexpr size_t cross_len = sizeof(cross_off);
}


// # October 5, 2026
std::string asmm = R"(
// spec_show_xray;
Dump of assembler code from 0x7ba774e67730 to 0x7ba774e67758:
   0x00007ba774e67730:	mov    r8d,DWORD PTR [rax+0x58]
   0x00007ba774e67734:	test   r8d,r8d
   0x00007ba774e67737:	sete   bl
   0x00007ba774e6773a:	test   rsi,rsi
   0x00007ba774e6773d:	sete   al
   0x00007ba774e67740:	or     bl,al
   0x00007ba774e67742:	je     0x7ba774e67758
   // 0x00007ba774e67744:	xor    eax,eax
   0x00007ba774e67746:	add    rsp,0x28
   0x00007ba774e6774a:	pop    rbx
   0x00007ba774e6774b:	pop    r12
   0x00007ba774e6774d:	pop    r13
   0x00007ba774e6774f:	pop    r14
   0x00007ba774e67751:	pop    r15
   0x00007ba774e67753:	pop    rbp
   0x00007ba774e67754:	ret
   0x00007ba774e67755:	nop    DWORD PTR [rax]
End of assembler dump.
// crosshair;
Dump of assembler code from 0x7820e5019223 to 0x7820e501924b:
   // 0x00007820e5019223:	movzx  eax,WORD PTR [rip+0x2dbbc26]
   0x00007820e501922a:	mov    WORD PTR [rbx],ax
   0x00007820e501922d:	mov    eax,0x1
   0x00007820e5019232:	mov    rbx,QWORD PTR [rbp-0x8]
   0x00007820e5019236:	leave
   0x00007820e5019237:	ret
   0x00007820e5019238:	nop    DWORD PTR [rax+rax*1+0x0]
   0x00007820e5019240:	xor    eax,eax
   0x00007820e5019242:	ret
   0x00007820e5019243:	int3
   0x00007820e5019244:	int3
   0x00007820e5019245:	int3
   0x00007820e5019246:	int3
   0x00007820e5019247:	int3
   0x00007820e5019248:	int3
   0x00007820e5019249:	int3
   0x00007820e501924a:	int3
End of assembler dump.
)";
