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

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inout.h"

char *datetime(void) {
	char *buff = malloc(64);
	char ctime[16];
	char cdate[16];
	time_t timep = time(NULL);
	struct tm *tm;

	tm = localtime(&timep);
	if (tm == NULL) {
		writelog(1, "localtime() returned nothing!");
		strcpy(buff, " ERROR ");
		return buff;
	}

	if (!strftime(ctime, sizeof(ctime)-1, "%I:%M:%S %p", tm)) {
		writelog(1, "strftime() returned an error when retriving time");
		strcpy(buff, " ERROR ");
		return buff;
	}
	writelog(3, "Found time: '%s'", ctime);

	if (!strftime(cdate, sizeof(cdate)-1, "%m/%d/%Y", tm)) {
		writelog(1, "strftime returned an error when retriving date");
		strcpy(buff, " ERROR ");
		return buff;
	}
	writelog(3, "Found date: '%s'", cdate);

	snprintf(buff, 64, " %s | %s ", ctime, cdate);
	return buff;
}

char *cputemp(int n) {
	char *temperature = malloc(12);
    char path[43];
    snprintf(path, 43, "/sys/devices/virtual/thermal/thermal_zone%d", n);

	char *fd = readfile(path, "temp");
	if (fd == NULL) {
		writelog(2, "Unable to read temperature");
		strcpy(temperature, "");
	} else {
		snprintf(temperature, 12, "| %02.0f°C ", atof(fd) / 1000);
		writelog(3, "Temperature: '%02.0f°C'", atof(fd) / 1000);
	}
	free(fd);
	return temperature;
}
