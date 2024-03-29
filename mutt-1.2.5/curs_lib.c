/*
 * Copyright (C) 1996-2000 Michael R. Elkins <me@cs.hmc.edu>
 * 
 *     This program is free software; you can redistribute it and/or modify
 *     it under the terms of the GNU General Public License as published by
 *     the Free Software Foundation; either version 2 of the License, or
 *     (at your option) any later version.
 * 
 *     This program is distributed in the hope that it will be useful,
 *     but WITHOUT ANY WARRANTY; without even the implied warranty of
 *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *     GNU General Public License for more details.
 * 
 *     You should have received a copy of the GNU General Public License
 *     along with this program; if not, write to the Free Software
 *     Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111, USA.
 */ 

#include "mutt.h"
#include "mutt_menu.h"
#include "mutt_curses.h"
#include "pager.h"

#include <termios.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>

/* not possible to unget more than one char under some curses libs, and it
 * is impossible to unget function keys in SLang, so roll our own input
 * buffering routines.
 */
static size_t UngetCount = 0;
static size_t UngetBufLen = 0;
static event_t *KeyEvent;

void mutt_refresh (void)
{
  /* don't refresh when we are waiting for a child. */
  if (option (OPTKEEPQUIET))
    return;

  /* don't refresh in the middle of macros unless necessary */
  if (UngetCount && !option (OPTFORCEREFRESH))
    return;

  /* else */
  refresh ();
}

event_t mutt_getch (void)
{
  int ch;
  event_t err = {-1, OP_NULL }, ret;

  if (UngetCount)
    return (KeyEvent[--UngetCount]);

  SigInt = 0;

#ifdef KEY_RESIZE
  /* ncurses 4.2 sends this when the screen is resized */
  ch = KEY_RESIZE;
  while (ch == KEY_RESIZE)
#endif /* KEY_RESIZE */
    ch = getch ();

  if (SigInt)
    mutt_query_exit ();

  if(ch == ERR)
    return err;
  
  if ((ch & 0x80) && option (OPTMETAKEY))
  {
    /* send ALT-x as ESC-x */
    ch &= ~0x80;
    mutt_ungetch (ch, 0);
    ret.ch = '\033';
    ret.op = 0;
    return ret;
  }

  ret.ch = ch;
  ret.op = 0;
  return (ch == ctrl ('G') ? err : ret);
}

int _mutt_get_field (/* const */ char *field, char *buf, size_t buflen, int complete, int multiple, char ***files, int *numfiles)
{
  int ret;
  int len = mutt_strlen (field); /* in case field==buffer */

  do
  {
    CLEARLINE (LINES-1);
    addstr (field);
    mutt_refresh ();
    ret = _mutt_enter_string ((unsigned char *) buf, buflen, LINES-1, len, complete, multiple, files, numfiles);
  }
  while (ret == 1);
  CLEARLINE (LINES-1);
  return (ret);
}

int mutt_get_password (char *msg, char *buf, size_t buflen)
{
  int rc;

  CLEARLINE (LINES-1);
  addstr (msg);
  rc = mutt_enter_string ((unsigned char *) buf, buflen, LINES - 1, mutt_strlen (msg), M_PASS);
  CLEARLINE (LINES-1);
  return (rc);
}

void mutt_clear_error (void)
{
  Errorbuf[0] = 0;
  if (!option(OPTNOCURSES))
    CLEARLINE (LINES-1);
}

void mutt_edit_file (const char *editor, const char *data)
{
  char cmd[LONG_STRING];
  
  endwin ();
  mutt_expand_file_fmt (cmd, sizeof (cmd), editor, data);
  if (mutt_system (cmd) == -1)
    mutt_error (_("Error running \"%s\"!"), cmd);
  keypad (stdscr, TRUE);
  clearok (stdscr, TRUE);
}

int mutt_yesorno (const char *msg, int def)
{
  event_t ch;
  unsigned char *yes = (unsigned char *) _("yes");
  unsigned char *no = (unsigned char *) _("no");
  
  CLEARLINE(LINES-1);
  printw("%s ([%c]/%c): ", msg, def ? *yes : *no,
	 def ? *no : *yes);
  FOREVER
  {
    mutt_refresh ();
    ch = mutt_getch ();
    if (ch.ch == -1) return(-1);
    if (CI_is_return (ch.ch))
      break;
    else if (tolower(ch.ch) == tolower(*yes))
    {
      def = 1;
      break;
    }
    else if (tolower(ch.ch) == tolower(*no))
    {
      def = 0;
      break;
    }
    else
    {
      BEEP();
    }
  }
  addstr ((char *) (def ? yes : no));
  mutt_refresh ();
  return (def);
}

/* this function is called when the user presses the abort key */
void mutt_query_exit (void)
{
  mutt_flushinp ();
  curs_set (1);
  if (Timeout)
    timeout (-1); /* restore blocking operation */
  if (mutt_yesorno (_("Exit Mutt?"), 1) == 1)
  {
    endwin ();
    exit (0);
  }
  mutt_clear_error();
  mutt_curs_set (-1);
  SigInt = 0;
}

static void clean_error_buf(void)
{
  char *s;
  for(s = Errorbuf; *s; s++)
  {
    if(!IsPrint(*s))
      *s = '.';
  }
}

void mutt_curses_error (const char *fmt, ...)
{
  va_list ap;

  va_start (ap, fmt);
  vsnprintf (Errorbuf, sizeof (Errorbuf), fmt, ap);
  va_end (ap);
  
  dprint (1, (debugfile, "%s\n", Errorbuf));
  Errorbuf[ (COLS < sizeof (Errorbuf) ? COLS : sizeof (Errorbuf)) - 2 ] = 0;
  clean_error_buf();

  if (!option (OPTKEEPQUIET))
  {
    BEEP ();
    SETCOLOR (MT_COLOR_ERROR);
    mvaddstr (LINES-1, 0, Errorbuf);
    clrtoeol ();
    SETCOLOR (MT_COLOR_NORMAL);
    mutt_refresh ();
  }

  set_option (OPTMSGERR);
}

void mutt_message (const char *fmt, ...)
{
  va_list ap;

  va_start (ap, fmt);
  vsnprintf (Errorbuf, sizeof (Errorbuf), fmt, ap);
  va_end (ap);

  Errorbuf[ (COLS < sizeof (Errorbuf) ? COLS : sizeof (Errorbuf)) - 2 ] = 0;
  clean_error_buf();

  if (!option (OPTKEEPQUIET))
  {
    SETCOLOR (MT_COLOR_MESSAGE);
    mvaddstr (LINES - 1, 0, Errorbuf);
    clrtoeol ();
    SETCOLOR (MT_COLOR_NORMAL);
    mutt_refresh ();
  }

  unset_option (OPTMSGERR);
}

void mutt_show_error (void)
{
  if (option (OPTKEEPQUIET))
    return;
  
  SETCOLOR (option (OPTMSGERR) ? MT_COLOR_ERROR : MT_COLOR_MESSAGE);
  CLEARLINE (LINES-1);
  addstr (Errorbuf);
  SETCOLOR (MT_COLOR_NORMAL);
}

void mutt_endwin (const char *msg)
{
  if (!option (OPTNOCURSES))
  {
    CLEARLINE (LINES - 1);
    
    attrset (A_NORMAL);
    mutt_refresh ();
    endwin ();
  }
  
  if (msg && *msg)
    puts (msg);
}

void mutt_perror (const char *s)
{
  char *p = strerror (errno);

  dprint (1, (debugfile, "%s: %s (errno = %d)\n", s, 
      p ? p : "unknown error", errno));
  mutt_error ("%s: %s (errno = %d)", s, p ? p : _("unknown error"), errno);
}

int mutt_any_key_to_continue (const char *s)
{
  struct termios t;
  struct termios old;
  int f, ch;

  f = open ("/dev/tty", O_RDONLY);
  tcgetattr (f, &t);
  memcpy ((void *)&old, (void *)&t, sizeof(struct termios)); /* save original state */
  t.c_lflag &= ~(ICANON | ECHO);
  t.c_cc[VMIN] = 1;
  t.c_cc[VTIME] = 0;
  tcsetattr (f, TCSADRAIN, &t);
  fflush (stdout);
  if (s)
    fputs (s, stdout);
  else
    fputs (_("Press any key to continue..."), stdout);
  fflush (stdout);
  ch = fgetc (stdin);
  fflush (stdin);
  tcsetattr (f, TCSADRAIN, &old);
  close (f);
  fputs ("\r\n", stdout);
  mutt_clear_error ();
  return (ch);
}

int mutt_do_pager (const char *banner,
		   const char *tempfile,
		   int do_color,
		   pager_t *info)
{
  int rc;
  
  if (!Pager || mutt_strcmp (Pager, "builtin") == 0)
    rc = mutt_pager (banner, tempfile, do_color, info);
  else
  {
    char cmd[STRING];
    
    endwin ();
    mutt_expand_file_fmt (cmd, sizeof(cmd), Pager, tempfile);
    if (mutt_system (cmd) == -1)
    {
      mutt_error (_("Error running \"%s\"!"), cmd);
      rc = -1;
    }
    else
      rc = 0;
    mutt_unlink (tempfile);
  }

  return rc;
}

int _mutt_enter_fname (const char *prompt, char *buf, size_t blen, int *redraw, int buffy, int multiple, char ***files, int *numfiles)
{
  event_t ch;

  mvaddstr (LINES-1, 0, (char *) prompt);
  addstr (_(" ('?' for list): "));
  if (buf[0])
    addstr (buf);
  clrtoeol ();
  mutt_refresh ();

  ch = mutt_getch();
  if (ch.ch == -1)
  {
    CLEARLINE (LINES-1);
    return (-1);
  }
  else if (ch.ch == '?')
  {
    mutt_refresh ();
    buf[0] = 0;
    _mutt_select_file (buf, blen, 0, multiple, files, numfiles);
    *redraw = REDRAW_FULL;
  }
  else
  {
    char *pc = safe_malloc (mutt_strlen (prompt) + 3);

    sprintf (pc, "%s: ", prompt);
    mutt_ungetch (ch.op ? 0 : ch.ch, ch.op ? ch.op : 0);
    if (_mutt_get_field (pc, buf, blen, (buffy ? M_EFILE : M_FILE) | M_CLEAR, multiple, files, numfiles)
	!= 0)
      buf[0] = 0;
    MAYBE_REDRAW (*redraw);
    FREE (&pc);
  }

  return 0;
}

void mutt_ungetch (int ch, int op)
{
  event_t tmp;

  tmp.ch = ch;
  tmp.op = op;

  if (UngetCount >= UngetBufLen)
    safe_realloc ((void **) &KeyEvent, (UngetBufLen += 128) * sizeof(event_t));

  KeyEvent[UngetCount++] = tmp;
}

void mutt_flushinp (void)
{
  UngetCount = 0;
  flushinp ();
}

#if (defined(USE_SLANG_CURSES) || defined(HAVE_CURS_SET))
/* The argument can take 3 values:
 * -1: restore the value of the last call
 *  0: make the cursor invisible
 *  1: make the cursor visible
 */
void mutt_curs_set (int cursor)
{
  static int SavedCursor = 1;
  
  if (cursor < 0)
    cursor = SavedCursor;
  else
    SavedCursor = cursor;
  
  curs_set (cursor);
}
#endif

int mutt_multi_choice (char *prompt, char *letters)
{
  event_t ch;
  int choice;
  char *p;

  mvaddstr (LINES - 1, 0, prompt);
  clrtoeol ();
  FOREVER
  {
    mutt_refresh ();
    ch  = mutt_getch ();
    if (ch.ch == -1 || CI_is_return (ch.ch))
    {
      choice = -1;
      break;
    }
    else
    {
      p = strchr (letters, ch.ch);
      if (p)
      {
	choice = p - letters + 1;
	break;
      }
      else if (ch.ch <= '9' && ch.ch > '0')
      {
	choice = ch.ch - '0';
	if (choice <= mutt_strlen (letters))
	  break;
      }
    }
    BEEP ();
  }
  CLEARLINE (LINES - 1);
  mutt_refresh ();
  return choice;
}
