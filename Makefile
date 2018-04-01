# The make-provided flags like MAKE and CC aren't set, on purpose.
# This is Linux-specific software, so we can depend on GNU make.

# Options:
#	amdgpu	enable amdgpu VRAM size and usage reporting, default off
#		because amdgpu requires libdrm >= 2.4.63
#   (*) 30 Sep 2017 For default, amdgpu is on

PREFIX ?= usr
INSTALL ?= install
LIBDIR ?= lib

debug ?= 0
amdgpu ?= 1

bin = radeontop-gui
binstall = radeontop-gui.v1
scrpt = radeontop-gui
src = $(filter-out ,$(wildcard *.cpp))
obj = $(src:.c=.o)
verh = version.h

CFLAGS_SECTIONED = -ffunction-sections -fdata-sections
LDFLAGS_SECTIONED = -Wl,-gc-sections

CFLAGS ?= -Os
CFLAGS += -Wall -Wextra -pthread
CFLAGS += -Iinclude
CFLAGS += $(CFLAGS_SECTIONED)
CFLAGS += $(shell pkg-config --cflags pciaccess)
CFLAGS += $(shell pkg-config --cflags libdrm)

ifeq ($(debug), 1)
  CFLAGS += `wx-config --debug=yes --cflags`
else
  CFLAGS += `wx-config --cflags`
endif

ifeq ($(amdgpu), 1)
	CFLAGS += -DENABLE_AMDGPU=1
endif

ifeq ($(debug), 1)
	OUTDIR = bin/Debug
else
	OUTDIR = bin/Release
endif

ifeq ($(debug), 1)
	OUTOBJDIR = obj/Debug
else
	OUTOBJDIR = obj/Release
endif

ifndef plain
ifeq ($(debug), 1)
	CFLAGS += -g
else ifndef nostrip
	CFLAGS += -s
endif
endif

LDFLAGS ?= -Wl,-O2
LDFLAGS += $(LDFLAGS_SECTIONED)
LIBS += $(shell pkg-config --libs pciaccess)
LIBS += $(shell pkg-config --libs libdrm)
LDFLAGS += -lcpufreq
LDFLAGS +=	`wx-config --libs`

.PHONY: all clean install uninstall dist

all: $(bin)

$(obj): $(wildcard *.h) $(verh)

$(bin): $(OUTDIR)

$(bin): $(obj)
	$(CXX) -o $(OUTDIR)/$(bin) $(obj) $(CFLAGS) $(LDFLAGS) $(LIBS)

clean:
	rm -f *.o $(OUTDIR)/$(bin)

.git:

$(verh): .git
	./getver.sh

.outbin:

$(OUTDIR): .outbin
	test -d $(OUTDIR) || mkdir -p $(OUTDIR)

$(OUTOBJDIR): .outbin
	test -d $(OUTOBJDIR) || mkdir -p $(OUTOBJDIR)

install: all
	$(INSTALL) -D -m755 $(OUTDIR)/$(bin) $(DESTDIR)/$(PREFIX)/sbin/$(binstall)
	$(INSTALL) -D -m755 $(scrpt) $(DESTDIR)/$(PREFIX)/sbin/$(scrpt)

uninstall:
	rm -f $(DESTDIR)/$(PREFIX)/sbin/$(binstall)
	rm -f $(DESTDIR)/$(PREFIX)/sbin/$(scrpt)

dist: ver = $(shell git describe)
dist: name = $(bin)-$(ver)
dist: clean $(verh)
	sed -i '/\t\.\/getver.sh/d' Makefile
	cd .. && \
	ln -s $(bin) $(name) && \
	tar -h --numeric-owner --exclude-vcs -cvf - $(name) | pigz -9 > /tmp/$(name).tgz && \
	rm $(name)
	advdef -z4 /tmp/$(name).tgz
	git checkout Makefile
	cd /tmp && sha1sum $(name).tgz > $(name).tgz.sha1
