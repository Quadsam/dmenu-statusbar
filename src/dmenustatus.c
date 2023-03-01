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

int verbose = 2;
int running = 1;
int testing = 0;

int main(int argc, char **argv) {
	parse_args(argc, argv);
	if (!open_display())
		return 1;

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
		if (testing)
			running = 0;
		else
			sleep(1);
	}
	writelog(4, "Cleaning up...");
	writelog(4, "Freeing buffers");
	free(datetime_buff);
	free(cputemp_buff);
	free(battery_buff);
	free(status);
	writelog(4, "Closing display");
	XCloseDisplay(display);
	writelog(3, "Quitting");
	return 0;
}
