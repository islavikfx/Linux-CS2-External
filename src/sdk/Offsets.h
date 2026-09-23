#pragma once
#include <cstdint>
#include <string>


namespace Offsets {
    inline uintptr_t xray = 0x1a39130 + 0x14; // # September 23, 2026
}


std::string xrayasm = R"(
Dump of assembler code from 0x7d6fb0e6c130 to 0x7d6fb0e6c158:
   # // 0x00007d6fb0e6c130:	mov    r8d,DWORD PTR [rax+0x58] *(0x14 >)
   0x00007d6fb0e6c134:	test   r8d,r8d
   0x00007d6fb0e6c137:	sete   bl
   0x00007d6fb0e6c13a:	test   rsi,rsi
   0x00007d6fb0e6c13d:	sete   al
   0x00007d6fb0e6c140:	or     bl,al
   0x00007d6fb0e6c142:	je     0x7d6fb0e6c158
   # // 0x00007d6fb0e6c144:	xor    eax,eax *(return nop, nop)
   0x00007d6fb0e6c146:	add    rsp,0x28
   0x00007d6fb0e6c14a:	pop    rbx
   0x00007d6fb0e6c14b:	pop    r12
   0x00007d6fb0e6c14d:	pop    r13
   0x00007d6fb0e6c14f:	pop    r14
   0x00007d6fb0e6c151:	pop    r15
   0x00007d6fb0e6c153:	pop    rbp
   0x00007d6fb0e6c154:	ret
   0x00007d6fb0e6c155:	nop    DWORD PTR [rax]
End of assembler dump.
)";


# // My launch options for Shitical-Strike 2 if someone need (Nvidia, No vulcan shaders, "-threads 13" - CPU 12/6, Set your own but +1);
# // __NV_PRIME_RENDER_OFFLOAD=1 __GLX_VENDOR_LIBRARY_NAME=nvidia __VK_LAYER_NV_optimus=NVIDIA_only %command% -vulkan -novid -tickrate 128 -threads 13 -nojoy -high -fullscreen +fps_max 0 +fps_max_menu 120 +fps_max_ui 120 +r_show_build_info false +r_dynamic 0 +cl_forcepreload 0 +cl_radar_square_always true +r_fullscreen_gamma 2.45 +viewmodel_offset_y -1.80 +viewmodel_offset_x 0.65 +viewmodel_fov 75 +sv_cheats true
