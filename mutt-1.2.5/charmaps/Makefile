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


SHELL = /bin/sh

srcdir = .
top_srcdir = ..
prefix = /usr/local
exec_prefix = ${prefix}

bindir = ${exec_prefix}/bin
sbindir = ${exec_prefix}/sbin
libexecdir = ${exec_prefix}/libexec
datadir = ${prefix}/share
sysconfdir = ${prefix}/etc
sharedstatedir = ${prefix}/com
localstatedir = ${prefix}/var
libdir = /usr/local/lib/mutt
infodir = ${prefix}/info
mandir = ${prefix}/man
includedir = ${prefix}/include
oldincludedir = /usr/include

DESTDIR =

pkgdatadir = $(datadir)/mutt
pkglibdir = $(libdir)/mutt
pkgincludedir = $(includedir)/mutt

top_builddir = ..

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
host_alias = x86_64-unknown-linux-gnu
host_triplet = 
CATALOGS =  de.gmo ru.gmo it.gmo es.gmo uk.gmo fr.gmo pl.gmo nl.gmo cs.gmo id.gmo sk.gmo ko.gmo el.gmo zh_TW.Big5.gmo pt_BR.gmo eo.gmo gl.gmo sv.gmo da.gmo
CATOBJEXT = .gmo
CC = gcc
CPP = gcc -E
DATADIRNAME = share
DBX = no
DEBUGGER = /usr/bin/gdb
DOTLOCK_GROUP = mail
DOTLOCK_PERMISSION = 2755
DOTLOCK_TARGET = mutt_dotlock
GDB = /usr/bin/gdb
GENCAT = 
GMOFILES =  de.gmo ru.gmo it.gmo es.gmo uk.gmo fr.gmo pl.gmo nl.gmo cs.gmo id.gmo sk.gmo ko.gmo el.gmo zh_TW.Big5.gmo pt_BR.gmo eo.gmo gl.gmo sv.gmo da.gmo
GMSGFMT = /usr/bin/msgfmt
GT_NO = 
GT_YES = #YES#
INCLUDE_LOCALE_H = #include <locale.h>
INSTOBJEXT = .mo
INTLDEPS = 
INTLLIBS = 
INTLOBJS = 
ISPELL = no
LIBIMAP = 
LIBIMAPDEPS = 
MAKEINFO = /home/basedkyle/muttrepo/mutt-1.2.5/missing makeinfo
MKINSTALLDIRS = ./mkinstalldirs
MSGFMT = /usr/bin/msgfmt
MUTTLIBS =  -lcurses
MUTTLOCALEDIR = /usr/local/share/locale
MUTT_LIB_OBJECTS =  pgp.o pgpinvoke.o pgpkey.o pgplib.o gnupgparse.o resize.o
OPS = $(srcdir)/OPS $(srcdir)/OPS.PGP
PACKAGE = mutt
PGPAUX_TARGET = pgpring
POFILES =  de.po ru.po it.po es.po uk.po fr.po pl.po nl.po cs.po id.po sk.po ko.po el.po zh_TW.Big5.po pt_BR.po eo.po gl.po sv.po da.po
POSUB = po
RANLIB = ranlib
SDB = no
SENDMAIL = /usr/sbin/sendmail
SUBVERSION = i
U = 
USE_INCLUDED_LIBINTL = no
USE_NLS = yes
VERSION = 1.2.5
charmaps = /usr/local/share/mutt/charmaps
docdir = /usr/local/doc/mutt
l = 
libdir = /usr/local/lib/mutt
sharedir = /usr/local/share/mutt

noinst_DATA = charmap_notice
mkinstalldirs = $(SHELL) $(top_srcdir)/mkinstalldirs
CONFIG_HEADER = ../config.h
CONFIG_CLEAN_FILES = 
DATA =  $(noinst_DATA)

DIST_COMMON =  Makefile.am Makefile.in


DISTFILES = $(DIST_COMMON) $(SOURCES) $(HEADERS) $(TEXINFOS) $(EXTRA_DIST)

TAR = tar
GZIP_ENV = --best
all: all-redirect
.SUFFIXES:
$(srcdir)/Makefile.in: Makefile.am $(top_srcdir)/configure.in $(ACLOCAL_M4) 
	cd $(top_srcdir) && $(AUTOMAKE) --gnu --include-deps charmaps/Makefile

Makefile: $(srcdir)/Makefile.in  $(top_builddir)/config.status
	cd $(top_builddir) \
	  && CONFIG_FILES=$(subdir)/$@ CONFIG_HEADERS= $(SHELL) ./config.status

tags: TAGS
TAGS:


distdir = $(top_builddir)/$(PACKAGE)-$(VERSION)/$(subdir)

subdir = charmaps

distdir: $(DISTFILES)
	@for file in $(DISTFILES); do \
	  d=$(srcdir); \
	  if test -d $$d/$$file; then \
	    cp -pr $$d/$$file $(distdir)/$$file; \
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

install-data-am:
install-data: install-data-am

install-am: all-am
	@$(MAKE) $(AM_MAKEFLAGS) install-exec-am install-data-am
install: install-am
uninstall-am:
uninstall: uninstall-am
all-am: Makefile $(DATA)
all-redirect: all-am
install-strip:
	$(MAKE) $(AM_MAKEFLAGS) AM_INSTALL_PROGRAM_FLAGS=-s install
installdirs:


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

distclean: distclean-am

maintainer-clean-am:  maintainer-clean-generic distclean-am
	@echo "This command is intended for maintainers to use;"
	@echo "it deletes files that may require special tools to rebuild."

maintainer-clean: maintainer-clean-am

.PHONY: tags distdir info-am info dvi-am dvi check check-am \
installcheck-am installcheck install-exec-am install-exec \
install-data-am install-data install-am install uninstall-am uninstall \
all-redirect all-am all installdirs mostlyclean-generic \
distclean-generic clean-generic maintainer-clean-generic clean \
mostlyclean distclean maintainer-clean


charmap_notice:
	@echo ; echo "For charmap support, please read INSTALL" ; echo

# Tell versions [3.59,3.63) of GNU make to not export all variables.
# Otherwise a system limit (for SysV at least) may be exceeded.
.NOEXPORT:
