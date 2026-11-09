GCC_FLAGS= -Wall -Wextra -Werror -pedantic --std=c99
EXEC_FLAGS= -02
DEBUG_FLAGS= -fsanitize=address -g

LDLIBS= -lm -lX11 -ljansson
STATICLIBS= raylib/src/libraylib.a
TGT=out
TESTS=src/tests

install:
	mkdir $(TGT)
	mkdir $(TESTS)
	# run the tests and bla bla bla

cmtests:
	gcc $(GCC_FLAGS) $(DEBUG_FLAGS) $(STATICLIBS) $(TESTS)/files/files.c  -o $(TGT)/tests/files/files.to

test:
	$(TGT)/tests/files/files.to

check:
	gcc -fsyntaxonly src/main.c

debug:
	gcc -fsanitize=address -g src/types/request.c src/types/kve.c src/types/sizeI.c src/main.c $(STATICLIBS) $(LDLIBS) -o $(TGT)/dbg
make:
	gcc $(GCC_FLAGS) $(STATICLIBS) src/types/request.c  src/main.c -o test.e

unsafemake:
	gcc $(STATICLIBS) src/types/request.c  src/main.c -o test.e

clear:
	rm $(TGT)/*
