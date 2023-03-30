#!/usr/bin/env sh
if ! autoreconf --install --verbose;then
printf 'Unable to find autoreconf from GNU autotools!\n'
printf 'Please install autotools and try again.\n'
exit 1
fi
