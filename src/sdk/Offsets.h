#pragma once
#include <cstdint>


# // unknown@unknown:~$ pgrep -f cs2
# // 33298
# // 33299
# // 33345
# // 33358
# // 33359
# // 33386
# // 33391
# // unknown@unknown:~$ sudo cat /proc/33391/maps | grep libclient.so
# // [sudo] password for unknown:             
# // 7e897f600000-7e89801e2000 r--p 00000000 103:02 14816745                  /home/unknown/.var/app/com.valvesoftware.Steam/.local/share/Steam/steamapps/common/Counter-Strike Global Offensive/game/csgo/bin/linuxsteamrt64/libclient.so
# // 7e89801e2000-7e8983765000 r-xp 00be1000 103:02 14816745                  /home/unknown/.var/app/com.valvesoftware.Steam/.local/share/Steam/steamapps/common/Counter-Strike Global Offensive/game/csgo/bin/linuxsteamrt64/libclient.so
# // 7e8983765000-7e898399d000 r--p 04163000 103:02 14816745                  /home/unknown/.var/app/com.valvesoftware.Steam/.local/share/Steam/steamapps/common/Counter-Strike Global Offensive/game/csgo/bin/linuxsteamrt64/libclient.so
# // 7e898399d000-7e8983a6f000 rw-p 0439a000 103:02 14816745                  /home/unknown/.var/app/com.valvesoftware.Steam/.local/share/Steam/steamapps/common/Counter-Strike Global Offensive/game/csgo/bin/linuxsteamrt64/libclient.so
# // unknown@unknown:~$ python3 -c 'print(hex(0x00007e8980e9fe32 - 0x7e897f600000))'
# // 0x189fe32
# // unknown@unknown:~$ 
namespace Offsets {
    inline uintptr_t xray = 0x189fe32; // # july 7, 2026
}


std::string xrayasm = R"(
Dump of assembler code from 0x7e8980e9fe1e to 0x7e8980e9fe46:
   0x00007e8980e9fe1e:	add    BYTE PTR [rbx-0x247ab800],cl
   0x00007e8980e9fe24:	sete   r12b
   0x00007e8980e9fe28:	test   eax,eax
   0x00007e8980e9fe2a:	sete   al
   0x00007e8980e9fe2d:	or     r12b,al
   0x00007e8980e9fe30:	je     0x7e8980e9fe48
   0x00007e8980e9fe32:	xor    eax,eax
   0x00007e8980e9fe34:	add    rsp,0x38
   0x00007e8980e9fe38:	pop    rbx
   0x00007e8980e9fe39:	pop    r12
   0x00007e8980e9fe3b:	pop    r13
   0x00007e8980e9fe3d:	pop    r14
   0x00007e8980e9fe3f:	pop    r15
   0x00007e8980e9fe41:	pop    rbp
   0x00007e8980e9fe42:	ret
   0x00007e8980e9fe43:	nop    DWORD PTR [rax+rax*1+0x0]
End of assembler dump.
)";
