# termNote - A simple CLI based note manager written in C++

## About

termNote is a terminal based note manager written in C++23.
Some of the aspired feature are:

- Create, Add, Update, Delete and List Notes
- Import/Export your note into various data formats (.csv, .json)
- Utility daemon for desktop notifications based on times set in the note

* * *

## Prerequisites

The following library options have been tested and will be supported. If other configurations can be guaranteed to work this list will be updated.

- `cmake 3.24`
- `clang-17`
- `catch2`

* * *

## Installation

No up to date binary or package manager releases are provided at the moment. Please follow the instructions to build termNote instead.

```bash
git clone https://github.com/Terodom/termNote.git
cd termNote
mkdir build
cd build
cmake ..
make
```
