# Generated automatically from Makefile.in by configure.
# Makefile.in generated automatically by automake 1.4 from Makefile.am

# Copyright (C) 1994, 1995-8, 1999 Free Software Foundation, Inc.
# This Makefile.in is free software; the Free Software Foundation
# gives unlimited permission to copy and/or distribute it,
# with or without modifications, as long as this notice is preserved.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY, to the extent permitted by law; without
# even the implied warranty of MERCHANTABILITY or FITNESS FOR A
# PARTICULAR PURPOSE.

# Add all your files here


SHELL = /bin/sh

srcdir = .
top_srcdir = ../../..
prefix = /usr
exec_prefix = ${prefix}

bindir = /usr/bin
sbindir = ${exec_prefix}/sbin
libexecdir = ${exec_prefix}/libexec
sysconfdir = ${prefix}/etc
sharedstatedir = ${prefix}/com
localstatedir = ${prefix}/var
libdir = ${exec_prefix}/lib
infodir = ${prefix}/info
mandir = ${prefix}/man
includedir = ${prefix}/include
oldincludedir = /usr/include

DESTDIR =

pkgdatadir = $(datadir)/zzplayer
pkglibdir = $(libdir)/zzplayer
pkgincludedir = $(includedir)/zzplayer

top_builddir = ../../..

ACLOCAL = aclocal
AUTOCONF = autoconf
AUTOMAKE = automake
AUTOHEADER = autoheader

INSTALL = /usr/bin/install -c
INSTALL_PROGRAM = ${INSTALL} $(AM_INSTALL_PROGRAM_FLAGS)
INSTALL_DATA = ${INSTALL} -m 644
INSTALL_SCRIPT = ${INSTALL_PROGRAM}
transform = s,x,x,

NORMAL_INSTALL = :
PRE_INSTALL = :
POST_INSTALL = :
NORMAL_UNINSTALL = :
PRE_UNINSTALL = :
POST_UNINSTALL = :
build_alias = i586-pc-linux-gnu
build_triplet = i586-pc-linux-gnu
host_alias = i586-pc-linux-gnu
host_triplet = i586-pc-linux-gnu
target_alias = i586-pc-linux-gnu
target_triplet = i586-pc-linux-gnu
CC = gcc
CPP = gcc -E
CXX = g++
GLINC = @GLINC@
GLLIB = @GLLIB@
GMSGFMT = /usr/bin/msgfmt
IDL = @IDL@
KDE_EXTRA_RPATH = 
KDE_INCLUDES = -I/usr/include/kde
KDE_LDFLAGS = -L/usr/lib
KDE_RPATH = -rpath $(kde_libraries) -rpath $(qt_libraries) -rpath $(x_libraries)
LD = /usr/bin/ld
LIBCOMPAT = 
LIBCRYPT = -lcrypt
LIBDL = @LIBDL@
LIBJPEG = @LIBJPEG@
LIBMICO = @LIBMICO@
LIBOBJS = @LIBOBJS@
LIBPTHREAD = @LIBPTHREAD@
LIBPYTHON = @LIBPYTHON@
LIBSOCKET = 
LIBTOOL = $(SHELL) $(top_builddir)/libtool
LIBUCB = 
LN_S = ln -s
MAKEINFO = /E/Programmation/ZZplayer/ZZplayer-0.4/missing makeinfo
MICO_INCLUDES = @MICO_INCLUDES@
MICO_LDFLAGS = @MICO_LDFLAGS@
MOC = /usr/lib/qt-1.44/bin/moc
MSGFMT = /usr/bin/msgfmt
NM = /usr/bin/nm -B
PACKAGE = zzplayer
PAMINC = @PAMINC@
PAMLIBPATHS = @PAMLIBPATHS@
PAMLIBS = @PAMLIBS@
PYTHONINC = @PYTHONINC@
PYTHONLIB = @PYTHONLIB@
QT_INCLUDES = -I/usr/lib/qt-1.44/include
QT_LDFLAGS = -L/usr/lib/qt-1.44/lib
RANLIB = ranlib
SDL_CFLAGS = -I/usr/include/SDL -D_REENTRANT
SDL_CONFIG = /usr/bin/sdl-config
SDL_LIBS = -L/usr/lib -lSDL -lpthread
USE_NLS = yes
VERSION = 0.4
XGETTEXT = /usr/bin/xgettext
XPMINC = @XPMINC@
XPMLIB = @XPMLIB@
X_EXTRA_LIBS = 
X_INCLUDES = -I/usr/X11R6/include
X_LDFLAGS = -L/usr/X11R6/lib
all_includes = -I/usr/include/kde -I/usr/lib/qt-1.44/include -I/usr/X11R6/include
all_libraries = -L/usr/lib -L/usr/lib/qt-1.44/lib -L/usr/X11R6/lib
install_root = 
kde_appsdir = /usr/share/applnk
kde_bindir = /usr/bin
kde_cgidir = /usr/lib/cgi-bin
kde_confdir = /usr/share/config
kde_datadir = /usr/share/apps
kde_htmldir = /usr/doc/kde/HTML
kde_icondir = /usr/share/icons
kde_includes = /usr/include/kde
kde_libraries = /usr/lib
kde_locale = /usr/share/locale
kde_mimedir = /usr/share/mimelnk
kde_minidir = /usr/share/icons/mini
kde_partsdir = /usr/lib/parts
kde_sounddir = /usr/share/sounds
kde_toolbardir = /usr/share/toolbar
kde_wallpaperdir = /usr/share/wallpapers
qt_includes = /usr/lib/qt-1.44/include
qt_libraries = /usr/lib/qt-1.44/lib
x_includes = /usr/X11R6/include
x_libraries = /usr/X11R6/lib

data_DATA = zzplayer.html zzplayer-1.html zzplayer-2.html zzplayer-3.html zzplayer.xpm

# This is where it will all be installed
datadir = $(kde_htmldir)/en/ZZplayer
mkinstalldirs = $(SHELL) $(top_srcdir)/mkinstalldirs
CONFIG_HEADER = ../../../config.h
CONFIG_CLEAN_FILES = 
DATA =  $(data_DATA)

DIST_COMMON =  Makefile.am Makefile.in


DISTFILES = $(DIST_COMMON) $(SOURCES) $(HEADERS) $(TEXINFOS) $(EXTRA_DIST)

TAR = gtar
GZIP_ENV = --best
all: all-redirect
.SUFFIXES:
$(srcdir)/Makefile.in: Makefile.am $(top_srcdir)/configure.in $(ACLOCAL_M4) 
	cd $(top_srcdir) && $(AUTOMAKE) --gnu zzplayer/doc/en/Makefile

Makefile: $(srcdir)/Makefile.in  $(top_builddir)/config.status $(BUILT_SOURCES)
	cd $(top_builddir) \
	  && CONFIG_FILES=$(subdir)/$@ CONFIG_HEADERS= $(SHELL) ./config.status


install-dataDATA: $(data_DATA)
	@$(NORMAL_INSTALL)
	$(mkinstalldirs) $(DESTDIR)$(datadir)
	@list='$(data_DATA)'; for p in $$list; do \
	  if test -f $(srcdir)/$$p; then \
	    echo " $(INSTALL_DATA) $(srcdir)/$$p $(DESTDIR)$(datadir)/$$p"; \
	    $(INSTALL_DATA) $(srcdir)/$$p $(DESTDIR)$(datadir)/$$p; \
	  else if test -f $$p; then \
	    echo " $(INSTALL_DATA) $$p $(DESTDIR)$(datadir)/$$p"; \
	    $(INSTALL_DATA) $$p $(DESTDIR)$(datadir)/$$p; \
	  fi; fi; \
	done

uninstall-dataDATA:
	@$(NORMAL_UNINSTALL)
	list='$(data_DATA)'; for p in $$list; do \
	  rm -f $(DESTDIR)$(datadir)/$$p; \
	done
tags: TAGS
TAGS:


distdir = $(top_builddir)/$(PACKAGE)-$(VERSION)/$(subdir)

subdir = zzplayer/doc/en

distdir: $(DISTFILES)
	here=`cd $(top_builddir) && pwd`; \
	top_distdir=`cd $(top_distdir) && pwd`; \
	distdir=`cd $(distdir) && pwd`; \
	cd $(top_srcdir) \
	  && $(AUTOMAKE) --include-deps --build-dir=$$here --srcdir-name=$(top_srcdir) --output-dir=$$top_distdir --gnu zzplayer/doc/en/Makefile
	@for file in $(DISTFILES); do \
	  d=$(srcdir); \
	  if test -d $$d/$$file; then \
	    cp -pr $$/$$file $(distdir)/$$file; \
	  else \
	    test -f $(distdir)/$$file \
	    || ln $$d/$$file $(distdir)/$$file 2> /dev/null \
	    || cp -p $$d/$$file $(distdir)/$$file || :; \
	  fi; \
	done
info-am:
info: info-am
dvi-am:
dvi: dvi-am
check-am: all-am
check: check-am
installcheck-am:
installcheck: installcheck-am
install-exec-am:
install-exec: install-exec-am

install-data-am: install-dataDATA
install-data: install-data-am

install-am: all-am
	@$(MAKE) $(AM_MAKEFLAGS) install-exec-am install-data-am
install: install-am
uninstall-am: uninstall-dataDATA
uninstall: uninstall-am
all-am: Makefile $(DATA)
all-redirect: all-am
install-strip:
	$(MAKE) $(AM_MAKEFLAGS) AM_INSTALL_PROGRAM_FLAGS=-s install
installdirs:
	$(mkinstalldirs)  $(DESTDIR)$(datadir)


mostlyclean-generic:

clean-generic:

distclean-generic:
	-rm -f Makefile $(CONFIG_CLEAN_FILES)
	-rm -f config.cache config.log stamp-h stamp-h[0-9]*

maintainer-clean-generic:
mostlyclean-am:  mostlyclean-generic

mostlyclean: mostlyclean-am

clean-am:  clean-generic mostlyclean-am

clean: clean-am

distclean-am:  distclean-generic clean-am
	-rm -f libtool

distclean: distclean-am

maintainer-clean-am:  maintainer-clean-generic distclean-am
	@echo "This command is intended for maintainers to use;"
	@echo "it deletes files that may require special tools to rebuild."

maintainer-clean: maintainer-clean-am

.PHONY: uninstall-dataDATA install-dataDATA tags distdir info-am info \
dvi-am dvi check check-am installcheck-am installcheck install-exec-am \
install-exec install-data-am install-data install-am install \
uninstall-am uninstall all-redirect all-am all installdirs \
mostlyclean-generic distclean-generic clean-generic \
maintainer-clean-generic clean mostlyclean distclean maintainer-clean


# Tell versions [3.59,3.63) of GNU make to not export all variables.
# Otherwise a system limit (for SysV at least) may be exceeded.
.NOEXPORT:
