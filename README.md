## Linux CS2 External

Simple memory patch for CS2 on Linux.

![Menu](https://github.com/islavikfx/Linux-CS2-External/blob/main/img/input.png?raw=true)

### Run CS2 and open terminal, type this commands:
```bash
sudo apt install build-essential cmake git libglfw3-dev libglew-dev libopengl-dev
cd ~
git clone https://github.com/islavikfx/Linux-CS2-External.git
cd Linux-CS2-External/
mkdir -p build
cd build/
cmake ..
make -j$(nproc)
./Linux-CS2-External
```

Run with sudo if it doesnt work. The offset in Offsets.h may need to be updated over time.
