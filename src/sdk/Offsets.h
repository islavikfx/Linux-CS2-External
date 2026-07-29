#pragma once
#include <cstdint>


// # unknown@unknown:~$ pgrep -f cs2
// # 4733
// # 4734
// # 4780
// # 4793
// # 4794
// # 4821
// # 4826
// # unknown@unknown:~$ sudo cat /proc/4826/maps | grep -e libclient.so
// # 752820a00000-752821663000 r--p 00000000 103:02 2097195                   /home/unknown/.var/app/com.valvesoftware.Steam/.local/share/Steam/steamapps/common/Counter-Strike Global Offensive/game/csgo/bin/linuxsteamrt64/libclient.so
// # 752821663000-752824cab000 r-xp 00c62000 103:02 2097195                   /home/unknown/.var/app/com.valvesoftware.Steam/.local/share/Steam/steamapps/common/Counter-Strike Global Offensive/game/csgo/bin/linuxsteamrt64/libclient.so
// # 752824cab000-752824f00000 r--p 042a9000 103:02 2097195                   /home/unknown/.var/app/com.valvesoftware.Steam/.local/share/Steam/steamapps/common/Counter-Strike Global Offensive/game/csgo/bin/linuxsteamrt64/libclient.so
// # 752824f00000-752824fac000 rw-p 044fd000 103:02 2097195                   /home/unknown/.var/app/com.valvesoftware.Steam/.local/share/Steam/steamapps/common/Counter-Strike Global Offensive/game/csgo/bin/linuxsteamrt64/libclient.so
// # unknown@unknown:~$ python3 -c 'print(hex(0x00007528223e4132 - 0x752820a00000))'
// # 0x19e4132
// # unknown@unknown:~$ 


namespace Offsets {
    inline uintptr_t xray = 0x19e4132; // # july 29, 2026
}


std::string xrayasm = R"(
Dump of assembler code from 0x7528223e411f to 0x7528223e4147:
   0x00007528223e411f:	mov    eax,DWORD PTR [rax]
   0x00007528223e4121:	test   rbx,rbx
   0x00007528223e4124:	sete   r12b
   0x00007528223e4128:	test   eax,eax
   0x00007528223e412a:	sete   al
   0x00007528223e412d:	or     r12b,al
   0x00007528223e4130:	je     0x7528223e4148
   0x00007528223e4132:	xor    eax,eax
   0x00007528223e4134:	add    rsp,0x38
   0x00007528223e4138:	pop    rbx
   0x00007528223e4139:	pop    r12
   0x00007528223e413b:	pop    r13
   0x00007528223e413d:	pop    r14
   0x00007528223e413f:	pop    r15
   0x00007528223e4141:	pop    rbp
   0x00007528223e4142:	ret
   0x00007528223e4143:	nop    DWORD PTR [rax+rax*1+0x0]
End of assembler dump.
)";


# // My launch options for linux cs2 if someone needs (nvidia, no vulcan shaders, "-threads 13" - CPU 12/6, set your own but +1)
# // __NV_PRIME_RENDER_OFFLOAD=1 __GLX_VENDOR_LIBRARY_NAME=nvidia %command% -novid -nojoy -tickrate 128 -threads 13 -vulkan -high +fps_max 240 +fps_max_menu 120 +fps_max_ui 120 +r_fullscreen_gamma 2.5 +r_show_build_info false +cl_radar_square_always true +viewmodel_offset_y -1.80 +viewmodel_offset_x 0.65 +viewmodel_fov 75 +sv_cheats true
