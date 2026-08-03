#pragma once
#include <cstdint>


// # user@user:~$ pgrep -f cs2
// # 6042
// # 6043
// # 6044
// # 6102
// # 6134
// # 6139
// # user@user:~$ sudo cat /proc/6139/maps | grep -e libclient.so
// # [sudo] password for user:             
// # 76a0ef57a000-76a0f01dd000 r--p 00000000 00:3d 14837003                   /home/user/.local/share/Steam/steamapps/common/Counter-Strike Global Offensive/game/csgo/bin/linuxsteamrt64/libclient.so
// # 76a0f01dd000-76a0f3826000 r-xp 00c62000 00:3d 14837003                   /home/user/.local/share/Steam/steamapps/common/Counter-Strike Global Offensive/game/csgo/bin/linuxsteamrt64/libclient.so
// # 76a0f3826000-76a0f3a7b000 r--p 042aa000 00:3d 14837003                   /home/user/.local/share/Steam/steamapps/common/Counter-Strike Global Offensive/game/csgo/bin/linuxsteamrt64/libclient.so
// # 76a0f3a7b000-76a0f3b26000 rw-p 044fe000 00:3d 14837003                   /home/user/.local/share/Steam/steamapps/common/Counter-Strike Global Offensive/game/csgo/bin/linuxsteamrt64/libclient.so
// # user@user:~$ 0x000076a0f0f5e1a2
// # 0x000076a0f0f5e1a2: command not found
// # user@user:~$ python3 -c 'print(hex(0x000076a0f0f5e1a2 - 0x76a0ef57a000))'
// # 0x19e41a2
// # user@user:~$ 



namespace Offsets {
    inline uintptr_t xray = 0x19e41a2; // # Aug 4, 2026
}


std::string xrayasm = R"(
Dump of assembler code from 0x76a0f0f5e18f to 0x76a0f0f5e1b7:
   0x000076a0f0f5e18f:	mov    eax,DWORD PTR [rax]
   0x000076a0f0f5e191:	test   rbx,rbx
   0x000076a0f0f5e194:	sete   r12b
   0x000076a0f0f5e198:	test   eax,eax
   0x000076a0f0f5e19a:	sete   al
   0x000076a0f0f5e19d:	or     r12b,al
   0x000076a0f0f5e1a0:	je     0x76a0f0f5e1b8
   0x000076a0f0f5e1a2:	xor    eax,eax
   0x000076a0f0f5e1a4:	add    rsp,0x38
   0x000076a0f0f5e1a8:	pop    rbx
   0x000076a0f0f5e1a9:	pop    r12
   0x000076a0f0f5e1ab:	pop    r13
   0x000076a0f0f5e1ad:	pop    r14
   0x000076a0f0f5e1af:	pop    r15
   0x000076a0f0f5e1b1:	pop    rbp
   0x000076a0f0f5e1b2:	ret
   0x000076a0f0f5e1b3:	nop    DWORD PTR [rax+rax*1+0x0]
End of assembler dump.
)";


# // My launch options for linux CS2 if someone needs (nvidia, no vulcan shaders, "-threads 13" - CPU 12/6, set your own but +1)
# // __NV_PRIME_RENDER_OFFLOAD=1 __GLX_VENDOR_LIBRARY_NAME=nvidia __VK_LAYER_NV_optimus=NVIDIA_only %command% -vulkan -novid -tickrate 128 -threads 13 -nojoy -high -fullscreen +fps_max 0 +fps_max_menu 120 +fps_max_ui 120 +r_show_build_info false +r_dynamic 0 +cl_forcepreload 0 +cl_radar_square_always true +r_fullscreen_gamma 2.45 +viewmodel_offset_y -1.80 +viewmodel_offset_x 0.65 +viewmodel_fov 75 +sv_cheats true
