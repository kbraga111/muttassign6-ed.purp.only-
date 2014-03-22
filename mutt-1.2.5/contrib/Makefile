# Generated automatically from Makefile.in by configure.
# $Id: Makefile.in,v 1.12 2000/03/30 09:08:47 roessler Exp $

SHELL=/bin/sh

PACKAGE=mutt
VERSION=1.2.5

prefix=/usr/local
exec_prefix=${prefix}
bindir=${exec_prefix}/bin
libdir=/usr/local/lib/mutt
mandir=${prefix}/man
sharedir=/usr/local/share/mutt
srcdir=.
docdir=/usr/local/doc/mutt
top_srcdir=..
top_builddir=..
INSTALL=/usr/bin/install -c


subdir=contrib

SAMPLES=Mush.rc Pine.rc gpg.rc pgp2.rc pgp5.rc pgp6.rc Tin.rc \
	sample.muttrc  sample.mailcap sample.muttrc-tlr

DISTFILES= Makefile.in language.txt language50.txt  \
	patch.slang-1.2.2.keypad.1	\
	$(SAMPLES)

all clean:

distclean:
	-rm -f Makefile

install:
	$(top_srcdir)/mkinstalldirs $(DESTDIR)$(docdir)/samples
	for f in $(SAMPLES) ; do \
		$(INSTALL) -m 644 $(srcdir)/$$f $(DESTDIR)$(docdir)/samples ;	\
	done

maintainer-clean: distclean

Makefile: ../config.status Makefile.in
	cd .. \
	  && CONFIG_FILES=$(subdir)/$@ CONFIG_HEADERS= $(SHELL) ./config.status

distdir = ../$(PACKAGE)-$(VERSION)/$(subdir)
dist distdir: Makefile $(DISTFILES)
	for file in $(DISTFILES) ; do				\
		ln $(srcdir)/$$file $(distdir) 2> /dev/null 	\
			|| cp -p $(srcdir)/$$file $(distdir); 	\
	done
			
