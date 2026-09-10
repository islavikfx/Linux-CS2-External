#pragma once
#include <cstdint>
#include <string>


namespace Offsets {
    inline uintptr_t xray = 0x1a08c4f + 0x13; // # September 10, 2026
}


std::string xrayasm = R"(
Dump of assembler code from 0x7649a0f53c4f to 0x7649a0f53c77:
   // # 0x00007649a0f53c4f:	mov    eax,DWORD PTR [rax]
   0x00007649a0f53c51:	test   rbx,rbx
   0x00007649a0f53c54:	sete   r12b
   0x00007649a0f53c58:	test   eax,eax
   0x00007649a0f53c5a:	sete   al
   0x00007649a0f53c5d:	or     r12b,al
   0x00007649a0f53c60:	je     0x7649a0f53c78
   // # 0x00007649a0f53c62:	xor    eax,eax (return nop, nop)
   0x00007649a0f53c64:	add    rsp,0x38
   0x00007649a0f53c68:	pop    rbx
   0x00007649a0f53c69:	pop    r12
   0x00007649a0f53c6b:	pop    r13
   0x00007649a0f53c6d:	pop    r14
   0x00007649a0f53c6f:	pop    r15
   0x00007649a0f53c71:	pop    rbp
   0x00007649a0f53c72:	ret
   0x00007649a0f53c73:	nop    DWORD PTR [rax+rax*1+0x0]
End of assembler dump.
)";


# // My launch options for Shitical-Strike 2 if someone need (Nvidia, No vulcan shaders, "-threads 13" - CPU 12/6, Set your own but +1);
# // __NV_PRIME_RENDER_OFFLOAD=1 __GLX_VENDOR_LIBRARY_NAME=nvidia __VK_LAYER_NV_optimus=NVIDIA_only %command% -vulkan -novid -tickrate 128 -threads 13 -nojoy -high -fullscreen +fps_max 0 +fps_max_menu 120 +fps_max_ui 120 +r_show_build_info false +r_dynamic 0 +cl_forcepreload 0 +cl_radar_square_always true +r_fullscreen_gamma 2.45 +viewmodel_offset_y -1.80 +viewmodel_offset_x 0.65 +viewmodel_fov 75 +sv_cheats true
