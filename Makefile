.PHONY: all clean
all: bin/libtor-detector.so bin/cli

# Note to maintainers: Edit .vscode/c_cpp_properties.json when you change the defines.
CFLAGS=-Wall -Werror -Wextra -pedantic -pedantic-errors -g -D_POSIX_C_SOURCE=200809L -D__USE_GNU -D_GNU_SOURCE -std=c17
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

