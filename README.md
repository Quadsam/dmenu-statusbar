# dmenustatus

A statusbar for dmenu

**This package is still in early alpha and may not work on your system,
if you have any issues feel free to make an issue and I will try to help
to the best of my abilities. (Pull requests are welcome)**

## Building

- Clone the source repo:

``` bash
git clone https://github.com/Quadsam/dmenu-statusbar.git
```

- Build the package:

  - With the `bootstrap.sh` script provided:

  ``` bash
  ./bootstrap.sh
  make
  ```

  **Note:* pass `-s` to skip the `configure` step or pass any arguments
  you want to run `./configure` with to this script*

  - Or the regular way:

  ``` bash
  autoreconf --force --install --verbose
  ./configure
  make
  ```

- Install the package:

``` bash
make install
```

## License

``` license
dmenustatus - a statusbar for dwm's dmenu
Copyright (C) 2023  Quadsam

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Affero General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Affero General Public License for more details.

You should have received a copy of the GNU Affero General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
```
