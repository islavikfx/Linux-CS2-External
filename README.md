## Linux CS2 External

WH memory patch for Counter-Strike 2 on Linux.

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
Ignore errors that you may see. Run with sudo ./LinuxCS2 if doesnt work.

#### Changelog from 28 August 2026:

 [+] Removed FPS counter/Global update for menu logic.
 
 [+] Updated Offsets.h for last version.
 
 [+] Updated Menu UI/Optimizations.

The offset in Offsets.h may need to be updated over time.

Telegram & Discord: @jeddy01759
