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
#include <X11/Xlib.h>
#include "battery.h"
#include "inout.h"
#include "utils.h"

static Display *display;
int running = 1;

void setstatus(char *str) {
	XStoreName(display, DefaultRootWindow(display), str);
	XSync(display, False);
}

int main(void) {
	char *status = malloc(64);
	char *datetime_buff;
	char *cputemp_buff;
	char *battery_buff;

	if (!(display = XOpenDisplay(NULL))) {
		fprintf(stderr, "Cannot open display");
		return 1;
	}

	while(running) {
		datetime_buff = datetime();
		cputemp_buff = cputemp(9);
		battery_buff = battery(0);
		strcpy(status, datetime_buff);
		strcat(status, cputemp_buff);
		strcat(status, battery_buff);
		writelog(4, "Setting status: '%s'", status);
		setstatus(status);
//		sleep(1);
		running = 0;
	}
	free(datetime_buff);
	free(cputemp_buff);
	free(battery_buff);
	free(status);
	XCloseDisplay(display);
	return 0;
}
