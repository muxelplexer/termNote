#!/bin/bash
export XDG_CONFIG_HOME=.
export XDG_DATA_HOME=.
echo -n "Check that termNote runs... "
bin/termNote > /dev/null && echo OK || exit 1
echo -n "Check that a helpful message is displayed at first run... "
[[ $(bin/termNote) = *"termNote --help"* ]] && echo OK || exit 1
echo -n "Check that adding notes works... "
bin/termNote -a "This is a test note!"
[[ $(bin/termNote -l) = *"This is a test note!"* ]] && echo OK || exit 1
echo -n "Check that deleting notes works... "
echo yes | bin/termNote -d 0 > /dev/null && echo OK || exit 1
echo "Running unit tests..."
make test
