.PHONY: all clean
all: bin/libtor-detector.so bin/cli

CFLAGS=-Wall -Werror -Wextra -pedantic -pedantic-errors -g -D_POSIX_C_SOURCE=200809L
%.so: private CFLAGS += -shared -fPIC

clean:
	-rm -r bin

bin/:
	-mkdir bin/

bin/libtor-detector.so: tor-detector.c tor-detector.h | bin/
	$(COMPILE.c) tor-detector.c $(OUTPUT_OPTION)
	@echo "built library at bin/libtor-detector.so"

bin/cli: private LDLIBS += -ltor-detector
bin/cli: private LDFLAGS += -L bin
bin/cli: bin/libtor-detector.so main.c tor-detector.h | bin/
	$(LINK.c) main.c $(LDLIBS) $(OUTPUT_OPTION)
	@echo "built demo application at bin/cli"

