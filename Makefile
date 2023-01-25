CC=clang
CXX=clang++

CFLAGS = -std=c++20

LIBS =
ALL_LIBS = -Wl,-whole-archive $(patsubst %,-l%,$(LIBS)) -Wl,-no-whole-archive

LPATH = -I.

OBJS = $(subst .cc,.o,$(wildcard *.cc))

# all: template

%.o: %.cc
	@echo [32m"CC "[m $(CFLAGS) [33m$<[m
	@$(CXX) $(CFLAGS) -o $@ -c $<

template: ${OBJS}
	@echo [31mBIN[m "   " [33m$@[m
	@$(CXX) $^ $(LPATH) $(LIBS) -Wl,-E -rdynamic -o $@


# do not automatically delete *.o
.PRECIOUS: %.o


run: clean template
	./template


clean:
	rm -rf *.o template
