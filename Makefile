.PHONY: all lib cli clean
all: lib cli

clean:
	rm -r bin

bin/:
	mkdir bin/

lib: bin/libtor-detector.so
	echo "built library at bin/libtor-detector.so"

bin/libtor-detector.so: bin/ tor-detector.c tor-detector.h
	gcc -Wall -Werror -Wextra -c tor-detector.c -shared -fPIC -o bin/libtor-detector.so

bin/cli: lib main.c tor-detector.h
	gcc -L bin main.c -ltor-detector -o bin/cli

cli: bin/cli
	echo "built demo application at bin/cli"
