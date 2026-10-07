## Linux CS2 External

External menu for Shitical-Strike 2 on Linux.

![Menu](https://github.com/islavikfx/Linux-CS2-External/blob/main/img/input.png?raw=true)

### Run CS2 and open terminal, type this:
```bash
sudo apt install build-essential cmake g++ git libglfw3-dev libglew-dev libopengl-dev
cd ~
git clone https://github.com/islavikfx/Linux-CS2-External.git
cd Linux-CS2-External/
mkdir -p build
cd build/
cmake ..\\
make -j$(nproc)
./LinuxCS2
```

If you doesn't see wallhack glow then try to press "X" on keyboard.

#### Changelog from 5/6 October 2026:
 
 [+] Added new feature "Always Crosshair";

 [+] Updated Offsets.h for last version;

 [+] Optimized compile options;

 [+] Updated menu UI/Logic.

The offsets in Offsets.h may need to be updated over game updates.

Telegram & Discord: @islavikfx
