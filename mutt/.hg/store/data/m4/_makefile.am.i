         g   f      }������������j#�����Ta�g���            uEXTRA_DIST = README

dist-hook:
	for i in $(srcdir)/*.m4 ; do \
		echo cp -p $$i $(distdir) ; \
	done
     g     *   d      �    ����vP�b�9���%�@�               @   `   		cp -f -p $$i $(distdir) ; \
