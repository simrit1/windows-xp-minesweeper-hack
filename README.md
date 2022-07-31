# Windows XP Minesweeper Hack
<img src="https://user-images.githubusercontent.com/40394063/111699953-1e439580-887c-11eb-98c1-5b03a59f044e.png" width=300px>

The mine-plow is an original name of Windows XP Minesweeper Hack so don't be confuse at file name(mine-plow-1.0-x64.exe)  
I made this hack for just a educational purpose only. as you know reverse engineering is fun.  
If you have any technical question, leave a Q&A to below link.  

https://github.com/andrewbae/windows-xp-minesweeper-hack/discussions/new?category=q-a

# Getting started
## Download
https://github.com/andrewbae/Windows-XP-Minesweeper-Hack/releases/tag/1.0
## Usage
### Disable the entire mines
  ![ezgif com-gif-maker](https://user-images.githubusercontent.com/40394063/111704023-dcb5e900-8881-11eb-93d6-153535d4c67c.gif)  
### Reset the timer
 ![ezgif com-gif-maker (1)](https://user-images.githubusercontent.com/40394063/111704518-9d3bcc80-8882-11eb-9bec-25ed9a6a110f.gif)

# Contribution

Report issues or open pull requests with improvements  
## Build Instruction
### Prerequisites
* CMake 3.12+
* Linux - minGW 
* Windows - Visual Studio(MSVC)

### Windows based

```shall
$ git clone https://github.com/andrewbae/mine-plow.git
$ cd mine-plow && mkdir build 
$ cmake . -D CMAKE_CXX_COMPILER="MSVC" -Bbuild
$ cmake --build build/
```
### Linux based
```shall
$ git clone https://github.com/andrewbae/mine-plow.git
$ cd mine-plow && mkdir build 
$ cmake . -D CMAKE_CXX_COMPILER="x86_64-w64-mingw32-g++" -Bbuild
$ cmake --build build/
```
