.PHONY: debug release

APP = BasicApp
COMMON = -Wall -Werror -o $(APP).elf $(APP).cpp -lX11

debug:
	clang++ -g -Og $(COMMON)

release:
	clang++ -O3 -DNDEBUG $(COMMON)
