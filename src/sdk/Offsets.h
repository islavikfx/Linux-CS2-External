#pragma once
#include <cstdint>


// # pgrep -f cs2
// # sudo cat /proc/3618/maps | grep libclient.so
// # 715a07600000-715a081e2000 r--p 00000000 103:02 14817991 /home/unknown/.steam/debian-installation/steamapps/common/Counter-Strike Global Offensive/game/csgo/bin/linuxsteamrt64/libclient.so
// # python3 -c 'print(hex(0x00007876ca4da4f2 - 0x7876c8c00000))'
namespace Offsets {
    inline uintptr_t xray = 0x189fa72; // # may 24, 2026
}


std::string xrayasm = R"(
Dump of assembler code from 0x715a08e9fa5e to 0x715a08e9fa86:
   0x0000715a08e9fa5e:	add    BYTE PTR [rbx-0x247ab800],cl
   0x0000715a08e9fa64:	sete   r12b
   0x0000715a08e9fa68:	test   eax,eax
   0x0000715a08e9fa6a:	sete   al
   0x0000715a08e9fa6d:	or     r12b,al
   0x0000715a08e9fa70:	je     0x715a08e9fa88
   0x0000715a08e9fa72:	xor    eax,eax
   0x0000715a08e9fa74:	add    rsp,0x38
   0x0000715a08e9fa78:	pop    rbx
   0x0000715a08e9fa79:	pop    r12
   0x0000715a08e9fa7b:	pop    r13
   0x0000715a08e9fa7d:	pop    r14
   0x0000715a08e9fa7f:	pop    r15
   0x0000715a08e9fa81:	pop    rbp
   0x0000715a08e9fa82:	ret
   0x0000715a08e9fa83:	nop    DWORD PTR [rax+rax*1+0x0]
End of assembler dump.
)";
