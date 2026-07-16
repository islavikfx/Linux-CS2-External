#pragma once
#include <cstdint>


// # unknown@unknown:~$ 0x000074608e3e43f2
// # 0x000074608e3e43f2: command not found
// # unknown@unknown:~$ pgrep -f cs2
// # 4126
// # 4127
// # 4168
// # 4181
// # 4182
// # 4209
// # 4214
// # unknown@unknown:~$ sudo cat /proc/4214/maps | grep libclient.so
// # [sudo] password for unknown:             
// # 74608ca00000-74608d663000 r--p 00000000 103:02 14811294                  /home/unknown/.var/app/com.valvesoftware.Steam/.local/share/Steam/steamapps/common/Counter-Strike Global Offensive/game/csgo/bin/linuxsteamrt64/libclient.so
// # 74608d663000-746090cab000 r-xp 00c62000 103:02 14811294                  /home/unknown/.var/app/com.valvesoftware.Steam/.local/share/Steam/steamapps/common/Counter-Strike Global Offensive/game/csgo/bin/linuxsteamrt64/libclient.so
// # 746090cab000-746090f00000 r--p 042a9000 103:02 14811294                  /home/unknown/.var/app/com.valvesoftware.Steam/.local/share/Steam/steamapps/common/Counter-Strike Global Offensive/game/csgo/bin/linuxsteamrt64/libclient.so
// # 746090f00000-746090fab000 rw-p 044fd000 103:02 14811294                  /home/unknown/.var/app/com.valvesoftware.Steam/.local/share/Steam/steamapps/common/Counter-Strike Global Offensive/game/csgo/bin/linuxsteamrt64/libclient.so
// # unknown@unknown:~$ python3 -c 'print(hex(0x000074608e3e43f2 - 0x74608ca00000))'
// # 0x19e43f2
// # unknown@unknown:~$ 

namespace Offsets {
    inline uintptr_t xray = 0x19e43f2; // # july 16, 2026
}


std::string xrayasm = R"(
Dump of assembler code from 0x74608e3e43df to 0x74608e3e4407:
   0x000074608e3e43df:	mov    eax,DWORD PTR [rax]
   0x000074608e3e43e1:	test   rbx,rbx
   0x000074608e3e43e4:	sete   r12b
   0x000074608e3e43e8:	test   eax,eax
   0x000074608e3e43ea:	sete   al
   0x000074608e3e43ed:	or     r12b,al
   0x000074608e3e43f0:	je     0x74608e3e4408
   0x000074608e3e43f2:	xor    eax,eax
   0x000074608e3e43f4:	add    rsp,0x38
   0x000074608e3e43f8:	pop    rbx
   0x000074608e3e43f9:	pop    r12
   0x000074608e3e43fb:	pop    r13
   0x000074608e3e43fd:	pop    r14
   0x000074608e3e43ff:	pop    r15
   0x000074608e3e4401:	pop    rbp
   0x000074608e3e4402:	ret
   0x000074608e3e4403:	nop    DWORD PTR [rax+rax*1+0x0]
End of assembler dump.
)";


# // My launch options for linux cs2 if someone needs (nvidia, no vulcan shaders, "-threads 13" - CPU 12/6, set your own but +1)
# // __NV_PRIME_RENDER_OFFLOAD=1 __GLX_VENDOR_LIBRARY_NAME=nvidia %command% -novid -nojoy -tickrate 128 -threads 13 -vulkan -high +fps_max 240 +fps_max_menu 120 +r_fullscreen_gamma 3.3 +r_show_build_info false +cl_radar_square_always true +viewmodel_offset_y -1.80 +viewmodel_offset_x 0.65 +viewmodel_fov 75 +sv_cheats true
