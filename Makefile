# File:          Makefile
# Authors:       Jonathan Wang
# Created:       10 May 2023
#----------------------------------------------------------------------------
# Use the clang compiler
CC = clang


# Set compilation flags
#   -ansi       check syntax against the American National Standard for C
#   -g          include debugging information
#   -Wall       report all warnings
#   -std=gnu99  use the GNU extensions of the C99 standard
CFLAGS = -ansi -g -Wall -std=gnu99


#----------------------------------------------------------------------------
# build rules:
#
# Each rule takes the following form  (Note there MUST be a tab,
# as opposed to several spaces, preceding each command.
#
# target_name:  dependency_list
#        command(s)

all: homestats

# List program components, what they depend on, and how to compile or link each


homestats: homestats.o homestats-test.o
	$(CC) $(CFLAGS) -o homestats homestats.o homestats-test.o


homestats.o: homestats.c homestats.h
	$(CC) $(CFLAGS) -c homestats.c


homestats-test.o: homestats-test.c homestats.h
	$(CC) $(CFLAGS) -c homestats-test.c


#----------------------------------------------------------------------------
# cleanup rules: To invoke this command, type "make clean".
# Use this target to clean up your directory, deleting (without warning) 
#   the built program, object files, old emacs source versions, and core dumps.


clean:
	rm -f homestats homestats.o homestats.o