# dmenu-statusbar - a statusbar for dwm's dmenu
# Copyright (C) 2023  Quadsam
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU Affero General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU Affero General Public License for more details.
#
# You should have received a copy of the GNU Affero General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

NAME		:= dmenustatus
VERSION		:= 0.5.0
DEBUG		:= true

INCS		:= -Iinclude
LIBS		:= -lX11
FLAGS		:=  -Wall -pedantic
CFLAGS		:= $(FLAGS) ${INCS}
LDFLAGS		:= $(FLAGS) ${LIBS}

PREFIX		:= /usr/local
MANPREFIX	:= ${PREFIX}/share/man

ifeq "$(DEBUG)" "true"
CFLAGS		+= -g
BUILD		+= debug
else
BUILD		+= release
endif
