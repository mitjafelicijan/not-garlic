UNAME := $(shell uname)
MAN_ROOT := /usr/share/man

CC       = clang
CFLAGS   =
LDLIBS   = -lm -lcurl
INCLUDES =

# MacOS specific
ifeq ($(UNAME), Darwin)
endif

# Linux specific
ifeq ($(UNAME), Linux)
endif

# Debug options (DEBUG=1 make clone)
ifeq ($(DEBUG), 1)
CFLAGS += -W -ggdb
endif

garlic: clean main.c
	$(CC) -o garlic main.c $(CFLAGS) $(INCLUDES) $(LDLIBS)

clean:
	-rm garlic
