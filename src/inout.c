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

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int verbose = 2;

int writelog(int v, char *fmt, ...) {
	int n = 0;
	size_t size = 0;
	char *p = NULL;
	char *prefix = NULL;
	va_list ap;

	if (v > verbose)
		return 1;

	va_start(ap, fmt);
	n = vsnprintf(p, size, fmt, ap);
	va_end(ap);

	if (n < 0)
		return 0;

	size = (size_t) n + 1;
	p = malloc(size);
	if (p == NULL)
		return 0;

	va_start(ap, fmt);
	n = vsnprintf(p, size, fmt, ap);
	va_end(ap);

	if (n < 0) {
		free(p);
		return 0;
	}

	if (v == 0)
		prefix = "FATAL";
	else if (v == 1)
		prefix = "ERROR";
	else if (v == 2)
		prefix = "WARN";
	else if (v == 3)
		prefix = "INFO";
	else if (v == 4)
		prefix = "DEBUG";

	fprintf(stderr, "[%s]\t %s\n", prefix, p);
	free(p);
	return 1;
}

char *readfile(char *base, char *file) {
	char *data = malloc(513);
	char path[64];
	FILE *fd;

	memset(data, 0, 513);
	snprintf(path, 64, "%s/%s", base, file);
	writelog(4, "Opening file: '%s'", path);
	fd = fopen(path, "r");
	if (fd == NULL) {
		writelog(2, "Failed to open file '%s'", path);
		data[0] = '\0';
		return data;
	}

	if (fgets(data, 512, fd) == NULL) {
		writelog(2, "File contains no data '%s'", path);
		data[0] = '\0';
	}
	fclose(fd);
	return data;
}
