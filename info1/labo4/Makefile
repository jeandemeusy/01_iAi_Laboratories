#
# Makefile
#

# set the executable name
EXEC=app

CC=gcc
CFLAGS+= -std=c99 -Wall -g
CFLAGS+= -Iinclude
LDLIBS:= -lm

ODIR:=obj

SRC := $(wildcard *.c)
OBJS = $(patsubst %,$(ODIR)/%,$(SRC:.c=.o))

all: $(EXEC)

-include $(ODIR)/*.d

$(EXEC): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS) $(LDLIBS)

$(ODIR)/%.o: %.c | $(ODIR)
	$(CC) $(CFLAGS) -c $< -o $@ -MMD -MF $(@:.o=.d)

$(ODIR):
	mkdir $@

clean:
	$(RM) $(EXEC)
	$(RM) -rf $(ODIR)
	$(RM) -f unittest.py

test: all
	rm -f ~/unittest.py
	wget -P ~  https://raw.githubusercontent.com/Info1-TIN-A-2020-2021/unittest/master/unittest.py
	python3 ~/unittest.py -i t.json

.PHONY:	clean all test
.DEFAULT: all
