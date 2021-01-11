#
# Makefile
#

# set the executable name
EXEC=string

CC=gcc
CFLAGS+= -std=c99 -Wall -g
CFLAGS+= -Iinclude
LDLIBS:= -lm

ODIR:=obj

SRC := $(wildcard *.c)
HDR = $(wildcard *.h)

OBJS = $(patsubst %,$(ODIR)/%,$(SRC:.c=.o))


all: $(EXEC)

-include $(ODIR)/*.d

$(EXEC): $(OBJS)
	@for src in $(SRC) ; do clang-format -i $$src; done
	@for src in $(HDR) ; do clang-format -i $$src; done
	$(CC) -o $@ $^ $(LDFLAGS) $(LDLIBS)

$(ODIR)/%.o: %.c | $(ODIR)
	$(CC) $(CFLAGS) -c $< -o $@ -MMD -MF $(@:.o=.d)

$(ODIR):
	mkdir $@

clean:
	$(RM) $(EXEC)
	$(RM) -rf $(ODIR)
	$(RM) -f unittest.py

test: $(EXEC)
	baygon -v -t test.json ./$(EXEC)

format: main.c
	clang-format -i main.c

.PHONY:	clean all test
.DEFAULT: all
