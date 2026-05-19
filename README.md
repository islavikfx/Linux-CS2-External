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
sudo ./Linux-CS2
```

#### Changelog from 19 May 2026:
 [+] Added blood WH glow when you hit enemy (with new CS2 update).
 
 [+] Updated Offsets.h for last version.

Youtube video: https://youtu.be/M0zOoZ9-VBs

The offset in Offsets.h may need to be updated over time.

t.me/islavikhome
