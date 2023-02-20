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

int test_battery(void)
{
	char *path = "/sys/class/power_supply/BAT0";
	char *co;

	co = readfile(path, "present");
	if (co == NULL) {
		free(co);
		return 1;
	} else if (co[0] != '1') {
		free(co);
		return 1;
	}

	free(co);
	return 0;
}

char *get_battery(void)
{
	char *path = "/sys/class/power_supply/BAT0";
	char *co, status;
	int level;

	level = -1;

	co = readfile(path, "capacity");
	if (co == NULL)
		return smprintf("");

	sscanf(co, "%d", &level);
	free(co);

	co = readfile(path, "status");
	if (!strncmp(co, "Discharging", 11)) {
		status = 'v';
	} else if(!strncmp(co, "Full", 4)) {
		status = '\0';
	} else if(!strncmp(co, "Charging", 8)) {
		status = '^';
	} else {
		status = '?';
	}
	free(co);

	if (level < 0)
		return smprintf("invalid");

	if (status == '\0')
		return smprintf("%d%%", level);

	return smprintf("%c%d%%", status, level);
}
