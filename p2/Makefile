# We're using the default rules for make, but we're using
# these variables to get them to do exactly what we want.
CC = gcc
CFLAGS = -g -Wall -std=c99
LDLIBS = -lm

# This is a common trick.  All is the first target, so it's the
# default.  We use it to build both of the executables we want.
all: hlight voronoi

hlight: hlight.o

voronoi: voronoi.o

# Another common trick, a clean rule to remove temporary files, or
# files we could easily rebuild.
clean:
	rm -f hlight hlight.o
	rm -f voronoi voronoi.o
	rm -f output.txt
	rm -f output.ppm
