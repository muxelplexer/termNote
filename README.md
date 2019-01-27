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
-   `catch2`

* * *

## Installation

### Arch

Either install it directly from the AUR or use an AUR helper like trizen
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

#### Tests
Run `./test.sh` in any POSIX-copmliant shell to run tests. This is done automatically when built with Nix.

* * *

## Usage
### `termNote` (The main utility)
`termNote` is used to manipulate (`--add -a`, `--delete -d`, `--list -l`, `--show -s`) notes.
Entries are kept in `$XDG_DATA_HOME/termNote/notes` (or `$HOME/.termNote/notes` if you don't use XDG). Configuration is (going to) be kept in `$XDG_CONFIG_HOME/termNote/config`. Default option is `--list`.
### `noted` (The note daemon)
`noted` is a notification daemon that uses `libnotify` to send you messages about due dates. It tries to guess what date and time you've meant (see #8 #15 for details). It forks by default (meaning it's safe to use in startup scripts), but you can make it stay in foreground by using `-f`. `-v` is mostly used for debugging.

* * *

## Checklist

- [x]   List Notes
- [x]   Add Notes
- [x]   Remove Notes
- [x]   Add Functionality of Due Dates
- [ ]   Make Config File
