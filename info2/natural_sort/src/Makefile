#
# Makefile
#

# set the executable name
EXEC=app

CC=gcc
CFLAGS+= -std=c11 -Wall -g
CFLAGS+= -Iinclude -I/usr/local/include/
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

.PHONY:	clean all test
.DEFAULT: all
