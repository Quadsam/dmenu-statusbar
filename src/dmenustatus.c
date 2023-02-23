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

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <X11/Xlib.h>
#include "battery.h"
#include "inout.h"
#include "utils.h"

Display *display;
int running = 1;

int main(void) {
	display = XOpenDisplay(NULL);
	if (display == NULL) {
		writelog(0, "Cannot open display");
		return 1;
	}

	char *status = malloc(42);
	char *datetime_buff = NULL;
	char *cputemp_buff = NULL;
	char *battery_buff = NULL;

	signal(SIGHUP, handle_signal);
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);
	signal(SIGTERM, handle_signal);
	writelog(3, "PID: %d", getpid());
	while(running) {
		memset(status, 0, 42);
		datetime_buff = datetime();
		cputemp_buff = cputemp(9);
		battery_buff = battery(0);
		strcpy(status, datetime_buff);
		strcat(status, cputemp_buff);
		strcat(status, battery_buff);
		writelog(4, "Setting status: '%s'", status);
		setstatus(status);
		sleep(1);
//		running = 0;
	}
	writelog(3, "Cleaning up...");
	writelog(4, "Freeing buffers");
	free(datetime_buff);
	free(cputemp_buff);
	free(battery_buff);
	free(status);
	writelog(4, "Closing display");
	XCloseDisplay(display);
	writelog(2, "Quitting");
	return 0;
}
