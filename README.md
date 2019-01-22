# termNote

## About

termNote is going to be a full fledged terminal notes application with funcionality for adding and removing Notes, implenting times for it to be due and notfiy the User and make it customizable with a Config file.

* * *

## Prerequisites

You will need to have atleast these things:

-   `cmake 3.6`
-   `gcc 7+`
-   `argp`
-   `libnotify`

* * *

## Installation

### Arch

Either install it directly from the AUR or use an AUR helper like trizen\
```bash
trizen -S termNote-git
```

### Nix

```bash
nix-shell -p 'import (builtins.fetchGit {url="https://github.com/Terodom/termNote"; ref="master";})'
```

or

```bash
git clone https://github.com/Terodom/termNote
cd termNote 
nix-build
```

### Source

```bash
git clone https://github.com/Terodom/termNote.git
cd termNote
cmake .
make
```
This will install it to /usr/local/bin/

* * *

## Checklist

- [x]   List Notes
- [x]   Add Notes
- [x]   Remove Notes
- [x]   Add Functionality of Due Dates
- [ ]   Make Config File
