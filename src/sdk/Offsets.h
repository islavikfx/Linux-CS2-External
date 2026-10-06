#pragma once
#include <cstdint>
#include <string>


namespace Offsets {

    inline uintptr_t xray = 0x1a37d44;
    inline uintptr_t cross = 0x1be9823;
}

namespace Patchs {

    inline uint8_t xray_off[]  = {0x31, 0xc0}; // # xor eax, eax
    inline uint8_t xray_set[]  = {0x90, 0x90}; // # nop; nop
    inline uint8_t cross_off[] = {0x0f, 0xb7, 0x05, 0xa6, 0xed, 0xdb, 0x02}; // # movzx eax,WORD PTR [rip+0x2dbeda6] 
    inline uint8_t cross_set[] = {0x66, 0xb8, 0x01, 0x00, 0x90, 0x90, 0x90}; // # mov ax, 1; nop; nop; nop
    inline constexpr size_t xray_len  = sizeof(xray_off);
    inline constexpr size_t cross_len = sizeof(cross_off);
}


// # October 5/6, 2026
std::string asmm = R"(
Dump of assembler code from 0x7c4ae4e64d30 to 0x7c4ae4e64d58:
   0x00007c4ae4e64d30:	mov    r8d,DWORD PTR [rax+0x58]
   0x00007c4ae4e64d34:	test   r8d,r8d
   0x00007c4ae4e64d37:	sete   bl
   0x00007c4ae4e64d3a:	test   rsi,rsi
   0x00007c4ae4e64d3d:	sete   al
   0x00007c4ae4e64d40:	or     bl,al
   0x00007c4ae4e64d42:	je     0x7c4ae4e64d58
   // 0x00007c4ae4e64d44:	xor    eax,eax
   0x00007c4ae4e64d46:	add    rsp,0x28
   0x00007c4ae4e64d4a:	pop    rbx
   0x00007c4ae4e64d4b:	pop    r12
   0x00007c4ae4e64d4d:	pop    r13
   0x00007c4ae4e64d4f:	pop    r14
   0x00007c4ae4e64d51:	pop    r15
   0x00007c4ae4e64d53:	pop    rbp
   0x00007c4ae4e64d54:	ret
   0x00007c4ae4e64d55:	nop    DWORD PTR [rax]
End of assembler dump.
Dump of assembler code from 0x7a98fd016823 to 0x7a98fd01684b:
   // 0x00007a98fd016823:	movzx  eax,WORD PTR [rip+0x2dbeda6]        # 0x7a98ffdd55d0
   0x00007a98fd01682a:	mov    WORD PTR [rbx],ax
   0x00007a98fd01682d:	mov    eax,0x1
   0x00007a98fd016832:	mov    rbx,QWORD PTR [rbp-0x8]
   0x00007a98fd016836:	leave
   0x00007a98fd016837:	ret
   0x00007a98fd016838:	nop    DWORD PTR [rax+rax*1+0x0]
   0x00007a98fd016840:	xor    eax,eax
   0x00007a98fd016842:	ret
   0x00007a98fd016843:	int3
   0x00007a98fd016844:	int3
   0x00007a98fd016845:	int3
   0x00007a98fd016846:	int3
   0x00007a98fd016847:	int3
   0x00007a98fd016848:	int3
   0x00007a98fd016849:	int3
   0x00007a98fd01684a:	int3
End of assembler dump.)";
