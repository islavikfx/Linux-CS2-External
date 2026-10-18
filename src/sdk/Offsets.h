#pragma once
#include <cstdint>
#include <string>


namespace Offsets {

    inline uintptr_t xray = 0x1a39c44;
    inline uintptr_t cross = 0x1beea63;
    inline constexpr const char* datee = "18 October 2026.";
}

namespace Patchs {

    inline uint8_t xray_off[]  = {0x31, 0xc0};
    inline uint8_t xray_set[]  = {0x90, 0x90}; // # nop; nop
    inline uint8_t cross_off[] = {0x0f, 0xb7, 0x05, 0xc6, 0xe1, 0xdb, 0x02};
    inline uint8_t cross_set[] = {0x66, 0xb8, 0x01, 0x00, 0x90, 0x90, 0x90}; // # mov ax, 1; nop; nop; nop
    inline constexpr size_t xray_len  = sizeof(xray_off);
    inline constexpr size_t cross_len = sizeof(cross_off);
}


std::string asmm = R"(
Dump of assembler code from 0x7dc8e8e61c30 to 0x7dc8e8e61c58:
   0x00007dc8e8e61c30:	mov    r8d,DWORD PTR [rax+0x58]
   0x00007dc8e8e61c34:	test   r8d,r8d
   0x00007dc8e8e61c37:	sete   bl
   0x00007dc8e8e61c3a:	test   rsi,rsi
   0x00007dc8e8e61c3d:	sete   al
   0x00007dc8e8e61c40:	or     bl,al
   0x00007dc8e8e61c42:	je     0x7dc8e8e61c58
   // 0x00007dc8e8e61c44:	xor    eax,eax
   0x00007dc8e8e61c46:	add    rsp,0x28
   0x00007dc8e8e61c4a:	pop    rbx
   0x00007dc8e8e61c4b:	pop    r12
   0x00007dc8e8e61c4d:	pop    r13
   0x00007dc8e8e61c4f:	pop    r14
   0x00007dc8e8e61c51:	pop    r15
   0x00007dc8e8e61c53:	pop    rbp
   0x00007dc8e8e61c54:	ret
   0x00007dc8e8e61c55:	nop    DWORD PTR [rax]
End of assembler dump.
Dump of assembler code from 0x7dc8e9016a63 to 0x7dc8e9016a8b:
   // 0x00007dc8e9016a63:	movzx  eax,WORD PTR [rip+0x2dbe1c6]
   0x00007dc8e9016a6a:	mov    WORD PTR [rbx],ax
   0x00007dc8e9016a6d:	mov    eax,0x1
   0x00007dc8e9016a72:	mov    rbx,QWORD PTR [rbp-0x8]
   0x00007dc8e9016a76:	leave
   0x00007dc8e9016a77:	ret
   0x00007dc8e9016a78:	nop    DWORD PTR [rax+rax*1+0x0]
   0x00007dc8e9016a80:	xor    eax,eax
   0x00007dc8e9016a82:	ret
   0x00007dc8e9016a83:	int3
   0x00007dc8e9016a84:	int3
   0x00007dc8e9016a85:	int3
   0x00007dc8e9016a86:	int3
   0x00007dc8e9016a87:	int3
   0x00007dc8e9016a88:	int3
   0x00007dc8e9016a89:	int3
   0x00007dc8e9016a8a:	int3
End of assembler dump.)";
