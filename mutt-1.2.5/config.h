/* config.h.  Generated automatically by configure.  */
/* config.h.in.  Generated automatically from configure.in by autoheader.  */

/* Define if using alloca.c.  */
/* #undef C_ALLOCA */

/* Define to empty if the keyword does not work.  */
/* #undef const */

/* Define to one of _getb67, GETB67, getb67 for Cray-2 and Cray-YMP systems.
   This function is required for alloca.c support on those systems.  */
/* #undef CRAY_STACKSEG_END */

/* Define if you have alloca, as a function or macro.  */
#define HAVE_ALLOCA 1

/* Define if you have <alloca.h> and it should be used (not on Ultrix).  */
#define HAVE_ALLOCA_H 1

/* Define if you have a working `mmap' system call.  */
/* #undef HAVE_MMAP */

/* Define as __inline if that's what the C compiler calls it.  */
/* #undef inline */

/* Define to `long' if <sys/types.h> doesn't define.  */
/* #undef off_t */

/* Define to `int' if <sys/types.h> doesn't define.  */
/* #undef pid_t */

/* Define if you need to in order for stat and other things to work.  */
/* #undef _POSIX_SOURCE */

/* Define as the return type of signal handlers (int or void).  */
#define RETSIGTYPE void

/* Define to `unsigned' if <sys/types.h> doesn't define.  */
/* #undef size_t */

/* If using the C implementation of alloca, define if you know the
   direction of stack growth for your system; otherwise it will be
   automatically deduced at run-time.
 STACK_DIRECTION > 0 => grows toward higher addresses
 STACK_DIRECTION < 0 => grows toward lower addresses
 STACK_DIRECTION = 0 => direction of growth unknown
 */
/* #undef STACK_DIRECTION */

/* Define if you have the ANSI C header files.  */
#define STDC_HEADERS 1

/* Define if `sys_siglist' is declared by <signal.h>.  */
#define SYS_SIGLIST_DECLARED 1

/* Is this the international version? */
#define SUBVERSION "i"

/* Where to put l10n data */
#define MUTTLOCALEDIR "/usr/local/share/locale"

/* Enable debugging info */
/* #undef DEBUG */

/* What is your domain name? */
/* #undef DOMAIN */

/* use dotlocking to lock mailboxes? */
#define USE_DOTLOCK 1

/* use an external dotlocking program? */
#define DL_STANDALONE 1

/* use flock() to lock mailboxes? */
/* #undef USE_FLOCK */

/* Use fcntl() to lock folders? */
#define USE_FCNTL 1

/*
 * Define if you have problems with mutt not detecting new/old mailboxes
 * over NFS.  Some NFS implementations incorrectly cache the attributes
 * of small files.
 */
/* #undef NFS_ATTRIBUTE_HACK */

/* Do you want support for the POP3 protocol? (--enable-pop) */
/* #undef USE_POP */

/* Do you want support for the IMAP protocol? (--enable-imap) */
/* #undef USE_IMAP */

/* Do you want support for IMAP GSSAPI authentication? (--with-gss) */
/* #undef USE_GSS */

/* Do you have the Heimdal version of Kerberos V? (for gss support) */
/* #undef HAVE_HEIMDAL */

/* Do you want support for SSL? (--enable-ssl) */
/* #undef USE_SSL */

/* Avoid SSL routines which used patent-encumbered RC5 algorithms */
/* #undef NO_RC5 */

/* Avoid SSL routines which used patent-encumbered IDEA algorithms */
/* #undef NO_IDEA */

/* Avoid SSL routines which used patent-encumbered RSA algorithms */
/* #undef NO_RSA */

/*
 * Is mail spooled to the user's home directory?  If defined, MAILPATH should
 * be set to the filename of the spool mailbox relative the the home
 * directory.
 * use: configure --with-homespool=FILE
 */
/* #undef HOMESPOOL */

/* Where new mail is spooled */
#define MAILPATH "/var/mail"

/* Where to find sendmail on your system */
#define SENDMAIL "/usr/sbin/sendmail"

/* Do you want PGP support (--enable-pgp)? */
#define HAVE_PGP 1

/* Where to find ispell on your system? */
/* #undef ISPELL */

/* Should Mutt run setgid "mail" ? */
#define USE_SETGID 1

/* Does your curses library support color? */
#define HAVE_COLOR 1

/* Compiling with SLang instead of curses/ncurses? */
/* #undef USE_SLANG_CURSES */

/* program to use for shell commands */
#define EXECSHELL "/bin/sh"

/* The "buffy_size" feature */
/* #undef BUFFY_SIZE */

/* The result of isprint() is unreliable? */
/* #undef LOCALES_HACK */

/* Enable exact regeneration of email addresses as parsed?  NOTE: this requires
   significant more memory when defined. */
/* #undef EXACT_ADDRESS */

/* Does your system have the snprintf() call? */
#define HAVE_SNPRINTF 1

/* Does your system have the vsnprintf() call? */
#define HAVE_VSNPRINTF 1

/* Does your system have the fchdir() call? */
#define HAVE_FCHDIR 1

/* Define if your locale.h file contains LC_MESSAGES.  */
#define HAVE_LC_MESSAGES 1

/* Define to 1 if NLS is requested.  */
#define ENABLE_NLS 1

/* Define as 1 if you have catgets and don't want to use GNU gettext.  */
/* #undef HAVE_CATGETS */

/* Define as 1 if you have gettext and don't want to use GNU gettext.  */
#define HAVE_GETTEXT 1

/* Do we have stpcpy? */
#define HAVE_STPCPY 1

/* Use the included regex.c? */
/* #undef USE_GNU_REGEX */

/* Where's mixmaster located? */
/* #undef MIXMASTER */

/* Where are the character set definitions located? */
#define CHARMAPS_DIR "/usr/local/share/mutt/charmaps"

/* Define to `int' if <signal.h> doesn't define.  */
/* #undef sig_atomic_t */

/* The number of bytes in a long.  */
#define SIZEOF_LONG 8

/* Define if you have the __argz_count function.  */
#define HAVE___ARGZ_COUNT 1

/* Define if you have the __argz_next function.  */
#define HAVE___ARGZ_NEXT 1

/* Define if you have the __argz_stringify function.  */
#define HAVE___ARGZ_STRINGIFY 1

/* Define if you have the dcgettext function.  */
#define HAVE_DCGETTEXT 1

/* Define if you have the fchdir function.  */
#define HAVE_FCHDIR 1

/* Define if you have the fgetpos function.  */
#define HAVE_FGETPOS 1

/* Define if you have the ftruncate function.  */
#define HAVE_FTRUNCATE 1

/* Define if you have the getcwd function.  */
#define HAVE_GETCWD 1

/* Define if you have the getpagesize function.  */
#define HAVE_GETPAGESIZE 1

/* Define if you have the memmove function.  */
#define HAVE_MEMMOVE 1

/* Define if you have the munmap function.  */
#define HAVE_MUNMAP 1

/* Define if you have the putenv function.  */
#define HAVE_PUTENV 1

/* Define if you have the RAND_egd function.  */
/* #undef HAVE_RAND_EGD */

/* Define if you have the RAND_status function.  */
/* #undef HAVE_RAND_STATUS */

/* Define if you have the regcomp function.  */
#define HAVE_REGCOMP 1

/* Define if you have the setegid function.  */
#define HAVE_SETEGID 1

/* Define if you have the setenv function.  */
#define HAVE_SETENV 1

/* Define if you have the setlocale function.  */
#define HAVE_SETLOCALE 1

/* Define if you have the setrlimit function.  */
#define HAVE_SETRLIMIT 1

/* Define if you have the srand48 function.  */
#define HAVE_SRAND48 1

/* Define if you have the stpcpy function.  */
#define HAVE_STPCPY 1

/* Define if you have the strcasecmp function.  */
#define HAVE_STRCASECMP 1

/* Define if you have the strchr function.  */
#define HAVE_STRCHR 1

/* Define if you have the strdup function.  */
#define HAVE_STRDUP 1

/* Define if you have the strerror function.  */
#define HAVE_STRERROR 1

/* Define if you have the strftime function.  */
#define HAVE_STRFTIME 1

/* Define if you have the <argz.h> header file.  */
#define HAVE_ARGZ_H 1

/* Define if you have the <getopt.h> header file.  */
#define HAVE_GETOPT_H 1

/* Define if you have the <limits.h> header file.  */
#define HAVE_LIMITS_H 1

/* Define if you have the <locale.h> header file.  */
#define HAVE_LOCALE_H 1

/* Define if you have the <malloc.h> header file.  */
#define HAVE_MALLOC_H 1

/* Define if you have the <ncurses.h> header file.  */
/* #undef HAVE_NCURSES_H */

/* Define if you have the <nl_types.h> header file.  */
#define HAVE_NL_TYPES_H 1

/* Define if you have the <stdarg.h> header file.  */
#define HAVE_STDARG_H 1

/* Define if you have the <string.h> header file.  */
#define HAVE_STRING_H 1

/* Define if you have the <sysexits.h> header file.  */
#define HAVE_SYSEXITS_H 1

/* Define if you have the <sys/ioctl.h> header file.  */
#define HAVE_SYS_IOCTL_H 1

/* Define if you have the <sys/param.h> header file.  */
#define HAVE_SYS_PARAM_H 1

/* Define if you have the <sys/resource.h> header file.  */
#define HAVE_SYS_RESOURCE_H 1

/* Define if you have the <sys/time.h> header file.  */
#define HAVE_SYS_TIME_H 1

/* Define if you have the <unistd.h> header file.  */
#define HAVE_UNISTD_H 1

/* Define if you have the crypto library (-lcrypto).  */
/* #undef HAVE_LIBCRYPTO */

/* Define if you have the i library (-li).  */
/* #undef HAVE_LIBI */

/* Define if you have the intl library (-lintl).  */
/* #undef HAVE_LIBINTL */

/* Define if you have the nsl library (-lnsl).  */
/* #undef HAVE_LIBNSL */

/* Define if you have the socket library (-lsocket).  */
/* #undef HAVE_LIBSOCKET */

/* Define if you have the ssl library (-lssl).  */
/* #undef HAVE_LIBSSL */

/* Define if you have the termlib library (-ltermlib).  */
/* #undef HAVE_LIBTERMLIB */

/* Define if you have the x library (-lx).  */
/* #undef HAVE_LIBX */

/* Name of package */
#define PACKAGE "mutt"

/* Version number of package */
#define VERSION "1.2.5"

/* Define if compiler has function prototypes */
#define PROTOTYPES 1

/* Define if you have start_color, as a function or macro.  */
#define HAVE_START_COLOR 1

/* Define if you have typeahead, as a function or macro.  */
#define HAVE_TYPEAHEAD 1

/* Define if you have bkgdset, as a function or macro.  */
#define HAVE_BKGDSET 1

/* Define if you have curs_set, as a function or macro.  */
#define HAVE_CURS_SET 1

/* Define if you have meta, as a function or macro.  */
#define HAVE_META 1

/* Define if you have use_default_colors, as a function or macro.  */
#define HAVE_USE_DEFAULT_COLORS 1

/* Define if you have resizeterm, as a function or macro.  */
#define HAVE_RESIZETERM 1

