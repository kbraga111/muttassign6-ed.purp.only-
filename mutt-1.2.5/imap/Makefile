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

AUTOMAKE_OPTIONS = foreign

#GSSSOURCES = auth_gss.c

#SSLSOURCES = imap_ssl.c
#SSLHEADERS = imap_ssl.h

EXTRA_DIST = BUGS README TODO imap_ssl.c imap_ssl.h auth_gss.c

INCLUDES = -I$(top_srcdir) -I../intl

noinst_LIBRARIES = libimap.a
noinst_HEADERS = imap_private.h imap_socket.h md5.h message.h $(SSLHEADERS)

libimap_a_SOURCES = auth.c browse.c command.c imap.c imap.h md5c.c message.c 	socket.c util.c $(GSSSOURCES) $(SSLSOURCES)

mkinstalldirs = $(SHELL) $(top_srcdir)/mkinstalldirs
CONFIG_HEADER = ../config.h
CONFIG_CLEAN_FILES = 
LIBRARIES =  $(noinst_LIBRARIES)


DEFS = -DHAVE_CONFIG_H -I. -I$(srcdir) -I..
CPPFLAGS =  -I$(top_srcdir)/intl
LDFLAGS = 
LIBS = 
libimap_a_LIBADD = 
#libimap_a_OBJECTS =  auth.o browse.o \
#command.o imap.o md5c.o message.o socket.o \
#util.o auth_gss.o
#libimap_a_OBJECTS =  auth.o browse.o \
#command.o imap.o md5c.o message.o socket.o \
#util.o imap_ssl.o
libimap_a_OBJECTS =  auth.o browse.o \
command.o imap.o md5c.o message.o \
socket.o util.o
##libimap_a_OBJECTS =  auth.o browse.o \
##command.o imap.o md5c.o message.o socket.o \
##util.o auth_gss.o imap_ssl.o
AR = ar
CFLAGS = -Wall -pedantic -g -O2
COMPILE = $(CC) $(DEFS) $(INCLUDES) $(AM_CPPFLAGS) $(CPPFLAGS) $(AM_CFLAGS) $(CFLAGS)
CCLD = $(CC)
LINK = $(CCLD) $(AM_CFLAGS) $(CFLAGS) $(LDFLAGS) -o $@
HEADERS =  $(noinst_HEADERS)

DIST_COMMON =  README Makefile.am Makefile.in TODO


DISTFILES = $(DIST_COMMON) $(SOURCES) $(HEADERS) $(TEXINFOS) $(EXTRA_DIST)

TAR = tar
GZIP_ENV = --best
SOURCES = $(libimap_a_SOURCES)
OBJECTS = $(libimap_a_OBJECTS)

all: all-redirect
.SUFFIXES:
.SUFFIXES: .S .c .o .s
$(srcdir)/Makefile.in: Makefile.am $(top_srcdir)/configure.in $(ACLOCAL_M4) 
	cd $(top_srcdir) && $(AUTOMAKE) --foreign --include-deps imap/Makefile

Makefile: $(srcdir)/Makefile.in  $(top_builddir)/config.status
	cd $(top_builddir) \
	  && CONFIG_FILES=$(subdir)/$@ CONFIG_HEADERS= $(SHELL) ./config.status


mostlyclean-noinstLIBRARIES:

clean-noinstLIBRARIES:
	-test -z "$(noinst_LIBRARIES)" || rm -f $(noinst_LIBRARIES)

distclean-noinstLIBRARIES:

maintainer-clean-noinstLIBRARIES:

.c.o:
	$(COMPILE) -c $<

.s.o:
	$(COMPILE) -c $<

.S.o:
	$(COMPILE) -c $<

mostlyclean-compile:
	-rm -f *.o core *.core

clean-compile:

distclean-compile:
	-rm -f *.tab.c

maintainer-clean-compile:

libimap.a: $(libimap_a_OBJECTS) $(libimap_a_DEPENDENCIES)
	-rm -f libimap.a
	$(AR) cru libimap.a $(libimap_a_OBJECTS) $(libimap_a_LIBADD)
	$(RANLIB) libimap.a

tags: TAGS

ID: $(HEADERS) $(SOURCES) $(LISP)
	list='$(SOURCES) $(HEADERS)'; \
	unique=`for i in $$list; do echo $$i; done | \
	  awk '    { files[$$0] = 1; } \
	       END { for (i in files) print i; }'`; \
	here=`pwd` && cd $(srcdir) \
	  && mkid -f$$here/ID $$unique $(LISP)

TAGS:  $(HEADERS) $(SOURCES)  $(TAGS_DEPENDENCIES) $(LISP)
	tags=; \
	here=`pwd`; \
	list='$(SOURCES) $(HEADERS)'; \
	unique=`for i in $$list; do echo $$i; done | \
	  awk '    { files[$$0] = 1; } \
	       END { for (i in files) print i; }'`; \
	test -z "$(ETAGS_ARGS)$$unique$(LISP)$$tags" \
	  || (cd $(srcdir) && etags $(ETAGS_ARGS) $$tags  $$unique $(LISP) -o $$here/TAGS)

mostlyclean-tags:

clean-tags:

distclean-tags:
	-rm -f TAGS ID

maintainer-clean-tags:

distdir = $(top_builddir)/$(PACKAGE)-$(VERSION)/$(subdir)

subdir = imap

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
all-am: Makefile $(LIBRARIES) $(HEADERS)
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
mostlyclean-am:  mostlyclean-noinstLIBRARIES mostlyclean-compile \
		mostlyclean-tags mostlyclean-generic

mostlyclean: mostlyclean-am

clean-am:  clean-noinstLIBRARIES clean-compile clean-tags clean-generic \
		mostlyclean-am

clean: clean-am

distclean-am:  distclean-noinstLIBRARIES distclean-compile \
		distclean-tags distclean-generic clean-am

distclean: distclean-am

maintainer-clean-am:  maintainer-clean-noinstLIBRARIES \
		maintainer-clean-compile maintainer-clean-tags \
		maintainer-clean-generic distclean-am
	@echo "This command is intended for maintainers to use;"
	@echo "it deletes files that may require special tools to rebuild."

maintainer-clean: maintainer-clean-am

.PHONY: mostlyclean-noinstLIBRARIES distclean-noinstLIBRARIES \
clean-noinstLIBRARIES maintainer-clean-noinstLIBRARIES \
mostlyclean-compile distclean-compile clean-compile \
maintainer-clean-compile tags mostlyclean-tags distclean-tags \
clean-tags maintainer-clean-tags distdir info-am info dvi-am dvi check \
check-am installcheck-am installcheck install-exec-am install-exec \
install-data-am install-data install-am install uninstall-am uninstall \
all-redirect all-am all installdirs mostlyclean-generic \
distclean-generic clean-generic maintainer-clean-generic clean \
mostlyclean distclean maintainer-clean


# Tell versions [3.59,3.63) of GNU make to not export all variables.
# Otherwise a system limit (for SysV at least) may be exceeded.
.NOEXPORT:
