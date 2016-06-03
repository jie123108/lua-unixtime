SRC := src/lua-unixtime.c
BIN := unixtime.so

all: $(BIN)

$(BIN): $(SRC)
	gcc -O2 -fPIC -shared -I/usr/include/lua5.1 -Isrc/ -o $@ $^

install: all
	install -m 755 $(BIN) $(DESTDIR)/usr/local/lib/lua/5.1/unixtime.so

test: install
	lua test/date.lua

clean:
	rm src/lua-unixtime.o $(BIN)

.PHONY: all install clean test
.SILENT:
