# termNote - A simple CLI based note manager written in C++

## About

termNote is a terminal based note manager written in C++23.
Some of the aspired feature are:

- Create, Add, Update, Delete and List Notes
- Import/Export your note into various data formats (.csv, .json)
- Utility daemon for desktop notifications based on times set in the note

* * *

## To-Do
- [ ] Re-Implement noted behaviour
    - termNote
        - [ ] Save due dates with note's
    - noted
        - [ ] Implement daemon that checks notes for due dates.
        - [ ] Implement libnotify support.
- [ ] TUI / GUI?
- [ ] sqlite backend
- [ ] note groups

## Prerequisites

The following library options have been tested and will be supported. If other configurations can be guaranteed to work this list will be updated.
Generally any C++23 conforming compiler should work.

- `cmake 3.24`
- `clang-17` or `gcc13`
- `catch2`

* * *

## Installation

Go over to the [releases](https://github.com/muxelplexer/termNote/releases) and fetch the latest version.

No up to date binary or package manager releases are provided at the moment. Please follow the instructions to build termNote instead.

```bash
git clone https://github.com/Terodom/termNote.git
cd termNote
cmake -B build
make
```
