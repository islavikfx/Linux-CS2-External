#pragma once
#include <cstdint>
#include <string>


namespace Offsets {
    inline uintptr_t xray = 0x1a0268f + 0x13; // # August 28, 2026
}


std::string xrayasm = R"(
Dump of assembler code from 0x718b68f5568f to 0x718b68f556b7:
   0x0000718b68f5568f:	mov    eax,DWORD PTR [rax]
   0x0000718b68f55691:	test   rbx,rbx
   0x0000718b68f55694:	sete   r12b
   0x0000718b68f55698:	test   eax,eax
   0x0000718b68f5569a:	sete   al
   0x0000718b68f5569d:	or     r12b,al
   0x0000718b68f556a0:	je     0x718b68f556b8
   // # 0x0000718b68f556a2:	xor    eax,eax (return nop, nop)
   0x0000718b68f556a4:	add    rsp,0x38
   0x0000718b68f556a8:	pop    rbx
   0x0000718b68f556a9:	pop    r12
   0x0000718b68f556ab:	pop    r13
   0x0000718b68f556ad:	pop    r14
   0x0000718b68f556af:	pop    r15
   0x0000718b68f556b1:	pop    rbp
   0x0000718b68f556b2:	ret
   0x0000718b68f556b3:	nop    DWORD PTR [rax+rax*1+0x0]
End of assembler dump.
)";


# // My launch options for Shitical-Strike 2 if someone need (Nvidia, No vulcan shaders, "-threads 13" - CPU 12/6, Set your own but +1);
# // __NV_PRIME_RENDER_OFFLOAD=1 __GLX_VENDOR_LIBRARY_NAME=nvidia __VK_LAYER_NV_optimus=NVIDIA_only %command% -vulkan -novid -tickrate 128 -threads 13 -nojoy -high -fullscreen +fps_max 0 +fps_max_menu 120 +fps_max_ui 120 +r_show_build_info false +r_dynamic 0 +cl_forcepreload 0 +cl_radar_square_always true +r_fullscreen_gamma 2.45 +viewmodel_offset_y -1.80 +viewmodel_offset_x 0.65 +viewmodel_fov 75 +sv_cheats true
