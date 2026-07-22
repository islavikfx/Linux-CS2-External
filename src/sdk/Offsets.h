#pragma once
#include <cstdint>


// # unknown@unknown:~$ pgrep -f cs2
// # 6177
// # 6178
// # 6220
// # 6233
// # 6234
// # 6261
// # 6266
// # unknown@unknown:~$ sudo cat /proc/6266/maps | grep libclient.so
// # 7192aca00000-7192ad663000 r--p 00000000 103:02 1966415                   /home/unknown/.var/app/com.valvesoftware.Steam/.local/share/Steam/steamapps/common/Counter-Strike Global Offensive/game/csgo/bin/linuxsteamrt64/libclient.so
// # 7192ad663000-7192b0cac000 r-xp 00c62000 103:02 1966415                   /home/unknown/.var/app/com.valvesoftware.Steam/.local/share/Steam/steamapps/common/Counter-Strike Global Offensive/game/csgo/bin/linuxsteamrt64/libclient.so
// # 7192b0cac000-7192b0f01000 r--p 042aa000 103:02 1966415                   /home/unknown/.var/app/com.valvesoftware.Steam/.local/share/Steam/steamapps/common/Counter-Strike Global Offensive/game/csgo/bin/linuxsteamrt64/libclient.so
// # 7192b0f01000-7192b0fac000 rw-p 044fe000 103:02 1966415                   /home/unknown/.var/app/com.valvesoftware.Steam/.local/share/Steam/steamapps/common/Counter-Strike Global Offensive/game/csgo/bin/linuxsteamrt64/libclient.so
// # unknown@unknown:~$ python3 -c 'print(hex(0x00007192ae3e45b2 - 0x7192aca00000))'
// # 0x19e45b2
// # unknown@unknown:~$ 

namespace Offsets {
    inline uintptr_t xray = 0x19e45b2; // # july 22, 2026
}


std::string xrayasm = R"(
Dump of assembler code from 0x7192ae3e459f to 0x7192ae3e45c7:
   0x00007192ae3e459f:	mov    eax,DWORD PTR [rax]
   0x00007192ae3e45a1:	test   rbx,rbx
   0x00007192ae3e45a4:	sete   r12b
   0x00007192ae3e45a8:	test   eax,eax
   0x00007192ae3e45aa:	sete   al
   0x00007192ae3e45ad:	or     r12b,al
   0x00007192ae3e45b0:	je     0x7192ae3e45c8
   0x00007192ae3e45b2:	xor    eax,eax
   0x00007192ae3e45b4:	add    rsp,0x38
   0x00007192ae3e45b8:	pop    rbx
   0x00007192ae3e45b9:	pop    r12
   0x00007192ae3e45bb:	pop    r13
   0x00007192ae3e45bd:	pop    r14
   0x00007192ae3e45bf:	pop    r15
   0x00007192ae3e45c1:	pop    rbp
   0x00007192ae3e45c2:	ret
   0x00007192ae3e45c3:	nop    DWORD PTR [rax+rax*1+0x0]
End of assembler dump.
)";


# // My launch options for linux cs2 if someone needs (nvidia, no vulcan shaders, "-threads 13" - CPU 12/6, set your own but +1)
# // __NV_PRIME_RENDER_OFFLOAD=1 __GLX_VENDOR_LIBRARY_NAME=nvidia %command% -novid -nojoy -tickrate 128 -threads 13 -vulkan -high +fps_max 240 +fps_max_menu 120 +fps_max_ui 120 +r_fullscreen_gamma 2.5 +r_show_build_info false +cl_radar_square_always true +viewmodel_offset_y -1.80 +viewmodel_offset_x 0.65 +viewmodel_fov 75 +sv_cheats true
