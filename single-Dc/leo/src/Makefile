CC=g++
GITVERSION= "no-version"

CFLAGS= -g -std=c++11 -Wno-unused-result
CFLAGS+= -DGITVERSION=\"$(GITVERSION)\"

CFILES = $(shell find . -maxdepth 1 -name "*.cc")
HFILES = $(shell find . -maxdepth 1 -name "*.h")
OBJS = $(CFILES:.cc=.o)

main: $(CFILES) $(HFILES)
	$(CC) $(CFLAGS) -o main $(CFILES)

test: main
	./main ../../testcase/smallTestcase

clean: 
	rm -rf main
	rm -f $(OBJS) $(OBJS:.o=.d)
	rm -f *~
