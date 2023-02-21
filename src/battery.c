// dmenu-statusbar - a statusbar for dwm's dmenu
// Copyright (C) 2023  Quadsam
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "battery.h"
#include "file.h"
#include "smprintf.h"

int battery_present(char *base) {
	if (readfile(base, "present") == NULL)
		return 0;
	return 1;
}

int read_level(char *base) {
	int level;
	char *co = readfile(base, "capacity");

	sscanf(co, "%d", &level);
	return level;
}

char read_status(char *base) {
	char status;
	char *co = readfile(base, "status");

	if (!strncmp(co, "Discharging", 11)) {
		status = 'v';
	} else if(!strncmp(co, "Not charging", 12)) {
		status = ' ';
	} else if(!strncmp(co, "Full", 4)) {
		status = ' ';
	} else if(!strncmp(co, "Charging", 8)) {
		status = '^';
	} else {
		status = '?';
	}
	return status;
}

char *get_battery(int n) {
	char path[29];
	snprintf(path, 29, "/sys/class/power_supply/BAT%d", n);

	if (!battery_present(path))
		return "\0";

	int level = read_level(path);
	char status = read_status(path);

	return smprintf("| %d%%%c", level, status);
}

