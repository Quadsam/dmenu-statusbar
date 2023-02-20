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

include config.mk

SRC	:= $(wildcard src/*.c)
OBJ	:= ${SRC:%.c=%.o}

.PHONY: all clean dist info install uninstall

all .DEFAULT: info ${NAME}

clean:
	$(RM) -f ${NAME} ${OBJ} ${NAME}-${VERSION}.src.tar.zst

dist: info LICENSE
	mkdir -p ${NAME}-${VERSION}
	cp config.mk Makefile src LICENSE ${NAME}-${VERSION}
	tar cO ${NAME}-${VERSION} | zstd -c19 >${NAME}-${VERSION}.src.tar.zst
	rm -rf ${NAME}-${VERSION}

info:
	@echo "${NAME} v${VERSION} $(BUILD)"
	@echo "CFLAGS:    ${CFLAGS}"
	@echo "LDFLAGS:   ${LDFLAGS}"
	@echo "Prefix:    ${PREFIX}"
	@echo ""

install: all LICENSE
	install -Dm755 ${NAME} ${DESTDIR}${PREFIX}/bin/${NAME}
	install -Dm644 LICENSE ${DESTDIR}${PREFIX}/share/licenses/${NAME}/LICENSE

uninstall:
	rm -f ${DESTDIR}/${PREFIX}/bin/${NAME}

${NAME}: ${OBJ}
	${CC} ${LDFLAGS} -o $@ $^

.c.o:
	${CC} ${CFLAGS} -c -o $@ $<

$(OBJ): config.mk
