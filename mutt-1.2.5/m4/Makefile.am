## Process this file with automake to produce Makefile.in -*-Makefile-*-

##m4-files-begin
EXTRA_DIST = README Makefile.am.in \
funcdecl.m4 \
gettext.m4 \
lcmessage.m4 \
progtest.m4
##m4-files-end

Makefile.am: Makefile.am.in
	rm -f $@ $@t
	sed -n '1,/^##m4-files-begin/p' Makefile.am.in > $@t
	( (echo EXTRA_DIST = README Makefile.am.in | tr '\012' @); \
	  (echo *.m4|tr ' ' @) ) \
	  |sed 's/@$$/%/;s/@/ \\@/g' |tr @% '\012\012' \
	  >> $@t
	sed -n '/^##m4-files-end/,$$p' Makefile.am.in >> $@t
	chmod a-w $@t
	mv $@t $@
