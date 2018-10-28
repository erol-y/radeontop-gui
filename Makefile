# The make-provided flags like MAKE and CC aren't set, on purpose.
# This is Linux-specific software, so we can depend on GNU make.

# Options:
#	amdgpu	enable amdgpu VRAM size and usage reporting, default off
#		because amdgpu requires libdrm >= 2.4.63
#   (*) 30 Sep 2017 For default, amdgpu is on
#
#	deskfile install GNOME .desktop file (default = 0).

PREFIX ?= usr
INSTALL ?= install
LIBDIR ?= lib
DOT_DESKTOP ?= share/applications

CXX = g++
LD = g++

debug ?= 0
amdgpu ?= 1
deskfile ?= 0

bin = radeontop-gui
binstall = radeontop-gui.v1
scrpt = radeontop-gui
gdesktop = radeontop-gui.desktop
src = $(filter-out ,$(wildcard *.cpp))
obj = $(src:.c=.o)
verh = version.h
SOURCEDIR = src

CFLAGS_SECTIONED = -ffunction-sections -fdata-sections
LDFLAGS_SECTIONED = -Wl,-gc-sections

CFLAGS ?= -Os
CFLAGS += -Wall -Wextra -pthread
CFLAGS += -I./include
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
	OUTDIR = out/bin/Debug
else
	OUTDIR = out/bin/Release
endif

ifeq ($(debug), 1)
	OUTOBJDIR = out/obj/Debug/src
else
	OUTOBJDIR = out/obj/Release/src
endif

OBJ_OUT = $(OUTOBJDIR)/GUIFrame.o $(OUTOBJDIR)/auth.o $(OUTOBJDIR)/cputop.o $(OUTOBJDIR)/cpudialog.o $(OUTOBJDIR)/detect.o $(OUTOBJDIR)/family_str.o $(OUTOBJDIR)/radeontop.o $(OUTOBJDIR)/rdt_guiApp.o $(OUTOBJDIR)/rdt_guiMain.o $(OUTOBJDIR)/ticks.o $(OUTOBJDIR)/conf.o $(OUTOBJDIR)/power.o $(OUTOBJDIR)/powergui.o $(OUTOBJDIR)/querydialog.o

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
LDFLAGS += `wx-config --libs`

.PHONY: all clean install uninstall dist

all: $(verh) $(bin)

$(obj): $(wildcard *.h) $(verh)

$(bin): $(OUTDIR) $(OUTOBJDIR) $(OBJ_OUT)

$(bin): $(obj)
	$(LD) -o $(OUTDIR)/$(bin) $(OBJ_OUT) $(LDFLAGS) $(LIBS)

$(OUTOBJDIR)/GUIFrame.o: $(SOURCEDIR)/GUIFrame.cpp
	$(CXX) $(CFLAGS) -c $(SOURCEDIR)/GUIFrame.cpp -o $(OUTOBJDIR)/GUIFrame.o

$(OUTOBJDIR)/auth.o: $(SOURCEDIR)/auth.cpp
	$(CXX) $(CFLAGS) -c $(SOURCEDIR)/auth.cpp -o $(OUTOBJDIR)/auth.o

$(OUTOBJDIR)/cputop.o: $(SOURCEDIR)/cputop.cpp
	$(CXX) $(CFLAGS) -c $(SOURCEDIR)/cputop.cpp -o $(OUTOBJDIR)/cputop.o

$(OUTOBJDIR)/cpudialog.o: $(SOURCEDIR)/cpudialog.cpp
	$(CXX) $(CFLAGS) -c $(SOURCEDIR)/cpudialog.cpp -o $(OUTOBJDIR)/cpudialog.o

$(OUTOBJDIR)/detect.o: $(SOURCEDIR)/detect.cpp
	$(CXX) $(CFLAGS) -c $(SOURCEDIR)/detect.cpp -o $(OUTOBJDIR)/detect.o

$(OUTOBJDIR)/family_str.o: $(SOURCEDIR)/family_str.cpp
	$(CXX) $(CFLAGS) -c $(SOURCEDIR)/family_str.cpp -o $(OUTOBJDIR)/family_str.o

$(OUTOBJDIR)/radeontop.o: $(SOURCEDIR)/radeontop.cpp
	$(CXX) $(CFLAGS) -c $(SOURCEDIR)/radeontop.cpp -o $(OUTOBJDIR)/radeontop.o

$(OUTOBJDIR)/rdt_guiApp.o: $(SOURCEDIR)/rdt_guiApp.cpp
	$(CXX) $(CFLAGS) -c $(SOURCEDIR)/rdt_guiApp.cpp -o $(OUTOBJDIR)/rdt_guiApp.o

$(OUTOBJDIR)/rdt_guiMain.o: $(SOURCEDIR)/rdt_guiMain.cpp
	$(CXX) $(CFLAGS) -c $(SOURCEDIR)/rdt_guiMain.cpp -o $(OUTOBJDIR)/rdt_guiMain.o

$(OUTOBJDIR)/ticks.o: $(SOURCEDIR)/ticks.cpp
	$(CXX) $(CFLAGS) -c $(SOURCEDIR)/ticks.cpp -o $(OUTOBJDIR)/ticks.o

$(OUTOBJDIR)/conf.o: $(SOURCEDIR)/conf.cpp
	$(CXX) $(CFLAGS) -c $(SOURCEDIR)/conf.cpp -o $(OUTOBJDIR)/conf.o

$(OUTOBJDIR)/power.o: $(SOURCEDIR)/power.cpp
	$(CXX) $(CFLAGS) -c $(SOURCEDIR)/power.cpp -o $(OUTOBJDIR)/power.o

$(OUTOBJDIR)/powergui.o: $(SOURCEDIR)/powergui.cpp
	$(CXX) $(CFLAGS) -c $(SOURCEDIR)/powergui.cpp -o $(OUTOBJDIR)/powergui.o

$(OUTOBJDIR)/querydialog.o: $(SOURCEDIR)/querydialog.cpp
	$(CXX) $(CFLAGS) -c $(SOURCEDIR)/querydialog.cpp -o $(OUTOBJDIR)/querydialog.o

clean:
	rm -f *.o $(OUTDIR)/$(bin) $(verh)
	- rm -rf out

.git:

$(verh): .git
	./getver.sh

.outbin:

$(OUTDIR): .outbin
	test -d $(OUTDIR) || mkdir -p $(OUTDIR)

$(OUTOBJDIR): .outbin
	test -d $(OUTOBJDIR) || mkdir -p $(OUTOBJDIR)

install: uninstall all
	$(INSTALL) -D -m755 $(OUTDIR)/$(bin) $(DESTDIR)/$(PREFIX)/sbin/$(binstall)
	$(INSTALL) -D -m755 $(scrpt) $(DESTDIR)/$(PREFIX)/sbin/$(scrpt)
ifeq ($(deskfile), 1)
	$(INSTALL) -D -m644 $(CURDIR)/data/$(gdesktop) $(DESTDIR)/$(PREFIX)/$(DOT_DESKTOP)/$(gdesktop)
endif

uninstall:
	- rm -f $(DESTDIR)/$(PREFIX)/sbin/$(binstall)
	- rm -f $(DESTDIR)/$(PREFIX)/sbin/$(scrpt)
	- rm -f $(DESTDIR)/$(PREFIX)/$(DOT_DESKTOP)/$(gdesktop)

dist: ver = $(shell git describe)
dist: name = $(bin)-$(ver)
dist: clean $(verh)
