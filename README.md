# termNote ![](https://travis-ci.org/Terodom/termNote.svg?branch=master)

## About

termNote is currently being refactored and rewritten to leverage modern C++ capabilities.
The ability to set due-dates and the noted service have been cut for now but will be readded on a later date.

* * *

## Prerequisites

You will need to have atleast these things:

-   `cmake 3.12`
-   `argp`
-	`C++20 compliant compiler`

* * *

## Installation

### Arch

Either install it directly from the AUR or use an AUR helper like trizen
```bash
trizen -S termNote-git
```

### Source

```bash
git clone https://github.com/Terodom/termNote.git
cd termNote/bin
cmake ..
make intall
```
This will install it to /usr/local/bin/

* * *

## Usage
### `termNote` (The main utility)
`termNote` is used to manipulate (`--add -a`, `--delete -d`, `--list -l`, `--show -s`) notes.
Entries are kept in `$XDG_DATA_HOME/termNote/notes` (or `$HOME/.termNote/notes` if you don't use XDG). Default option is `--list`.

* * *

## Checklist

- [x]   List Notes
- [x]   Add Notes
- [x]   Remove Notes
- [ ]   Add Functionality of Due Dates
- [ ]   Make Config File
