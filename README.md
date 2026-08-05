## Linux CS2 External

WH memory patch for CS2 on Linux.

![Menu](https://github.com/islavikfx/Linux-CS2-External/blob/main/img/input.png?raw=true)

### Run CS2 and open terminal, type this:
```bash
sudo apt install build-essential cmake git libglfw3-dev libglew-dev libopengl-dev
cd ~
git clone https://github.com/islavikfx/Linux-CS2-External.git
cd Linux-CS2-External/
mkdir -p build
cd build/
cmake ..\\
make -j$(nproc)
./LinuxCS2
```
Run with sudo if doesnt work.

#### Changelog from 4 Aug 2026:
 
 [+] Updated Offsets.h/main.cpp for last version.

 [+] Updated CMake optimization.

The offset in Offsets.h may need to be updated over time.

Telegram contact: @islavikfx

Discord contact: @jeddy01759
