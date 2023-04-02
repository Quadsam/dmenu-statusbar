# Binary program being built
bin_PROGRAMS        = dmenustatus
noinst_HEADERS      = battery.h dmenustatus.h inout.h utils.h

# Sources for building the program
dmenustatus_SOURCES = battery.c dmenustatus.c inout.c utils.c

# Compiler flags to use during build
dmenustatus_CFLAGS  = -Wall -Werror -Wformat -pedantic
dmenustatus_LDFLAGS = @X_LIBS@
