## Linux CS2 External

WH memory patch for CS2 on Linux.

![Menu](https://github.com/islavikfx/Linux-CS2-External/blob/main/img/input.png?raw=true)

### Run CS2 and open terminal, type this:
```bash
sudo apt install build-essential cmake git libglfw3-dev libglew-dev libopengl-dev
cd ~
git clone https://github.com/islavikfx/Linux-CS2-External.git
cd Linux-CS2-External/
mkdir -p build && cd build/
cmake ..
make -j$(nproc)
sudo ./LinuxCS2
```

#### Changelog from 16 July 2026:
 
 [+] Updated Offsets.h for last version.

Youtube video: https://youtu.be/M0zOoZ9-VBs

The offset in Offsets.h may need to be updated over time.

Channel: t.me/islavikhome

Community: discord.gg/VTM7NK7wzp

Telegram & Discord contact: @islavikfx
