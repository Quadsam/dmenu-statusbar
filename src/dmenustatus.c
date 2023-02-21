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
#include <unistd.h>
#include <X11/Xlib.h>
#include "battery.h"
#include "date.h"
#include "file.h"
#include "smprintf.h"
#include "temp.h"


char *time_fmt = "%I:%M:%S %p";
char *date_fmt = "%m/%d/%Y";
char *cpu_temp_path = "/sys/devices/virtual/thermal/thermal_zone9";
int running = 1;

static Display *display;

void setstatus(char *str)
{
	XStoreName(display, DefaultRootWindow(display), str);
	XSync(display, False);
}

int main(void)
{
	char *status = malloc(128);
	char *ctime;
	char *cdate;
	char *temp = malloc(8);
	char *batt;

	if (!(display = XOpenDisplay(NULL))) {
		fprintf(stderr, "dwmstatus: cannot open display.\n");
		return 1;
	}

	while(running) {
		ctime = get_time(time_fmt);
		cdate = get_time(date_fmt);
		temp = get_temp(cpu_temp_path);
		batt = get_battery(0);

		status = smprintf(" %s | %s | %s ", ctime, cdate, temp);
//		strcpy(status, ctime);
//		strcat(status, cdate);
//		strcat(status, temp);
		strcat(status, batt);

		setstatus(status);
		sleep(1);
	}

	free(ctime);
	free(cdate);
	free(temp);
	free(status);
	XCloseDisplay(display);
	return 0;
}
