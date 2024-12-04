# FIFO_RING
Кольцевой буфер для FIFO (UART) и эмуляция для отладки

Ставим cmake

Debian/Ubuntu:
```bash
sudo apt update
sudo apt install cmake
```

CentOS/Fedora/RHEL:
```bash
sudo dnf install cmake
```

Arch/Manjaro
```bash
sudo pacman -S cmake
```

В папке проекта:
```bash
cmake -DCMAKE_BUILD_TYPE=Release -G "Unix Makefiles" -B build
cmake --build build
cmake --install build
./bin/sampleFFRG
```
По стандарту, эмулируется запись и считывание из буфера 10 значений, с и без rewrite.