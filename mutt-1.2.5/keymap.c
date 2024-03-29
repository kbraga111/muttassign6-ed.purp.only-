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
#include "keymap.h"
#include "mapping.h"

#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "functions.h"

struct mapping_t Menus[] = {
 { "alias",	MENU_ALIAS },
 { "attach",	MENU_ATTACH },
 { "browser",	MENU_FOLDER },
 { "compose",	MENU_COMPOSE },
 { "editor",	MENU_EDITOR },
 { "index",	MENU_MAIN },
 { "pager",	MENU_PAGER },
 { "postpone",	MENU_POST },


#ifdef HAVE_PGP
 { "pgp",	MENU_PGP },
#endif  
  
#ifdef MIXMASTER
  { "mix", 	MENU_MIX },
#endif
  

 { "query",	MENU_QUERY },
 { "generic",	MENU_GENERIC },
 { NULL,	0 }
};

#define mutt_check_menu(s) mutt_getvaluebyname(s, Menus)

static struct mapping_t KeyNames[] = {
  { "<PageUp>",	KEY_PPAGE },
  { "<PageDown>",	KEY_NPAGE },
  { "<Up>",	KEY_UP },
  { "<Down>",	KEY_DOWN },
  { "<Right>",	KEY_RIGHT },
  { "<Left>",	KEY_LEFT },
  { "<Delete>",	KEY_DC },
  { "<BackSpace>",KEY_BACKSPACE },
  { "<Insert>",	KEY_IC },
  { "<Home>",	KEY_HOME },
  { "<End>",	KEY_END },
#ifdef KEY_ENTER
  { "<Enter>",	KEY_ENTER },
#endif
  { "<Return>",	M_ENTER_C },
  { "<Esc>",	'\033' },
  { "<Tab>",	'\t' },
  { "<Space>",	' ' },
  { NULL,	0 }
};

/* contains the last key the user pressed */
int LastKey;

struct keymap_t *Keymaps[MENU_MAX];

static struct keymap_t *allocKeys (int len, keycode_t *keys)
{
  struct keymap_t *p;

  p = safe_calloc (1, sizeof (struct keymap_t));
  p->len = len;
  p->keys = safe_malloc (len * sizeof (keycode_t));
  memcpy (p->keys, keys, len * sizeof (keycode_t));
  return (p);
}

static int parse_fkey(char *s)
{
  char *t;
  int n = 0;

  if(s[0] != '<' || tolower(s[1]) != 'f')
    return -1;

  for(t = s + 2; *t && isdigit((unsigned char) *t); t++)
  {
    n *= 10;
    n += *t - '0';
  }

  if(*t != '>')
    return -1;
  else
    return n;
}

static int parsekeys (char *str, keycode_t *d, int max)
{
  int n, len = max;
  char buff[SHORT_STRING];
  char c;
  char *s, *t;

  strfcpy(buff, str, sizeof(buff));
  s = buff;
  
  while (*s && len)
  {
    *d = '\0';
    if(*s == '<' && (t = strchr(s, '>')))
    {
      t++; c = *t; *t = '\0';
      
      if ((n = mutt_getvaluebyname (s, KeyNames)) != -1)
      {
	s = t;
	*d = n;
      }
      else if ((n = parse_fkey(s)) > 0)
      {
	s = t;
	*d = KEY_F (n);
      }
      
      *t = c;
    }

    if(!*d)
    {
      *d = *s;
      s++;
    }
    d++;
    len--;
  }

  return (max - len);
}

/* insert a key sequence into the specified map.  the map is sorted by ASCII
 * value (lowest to highest)
 */
void km_bind (char *s, int menu, int op, char *macro, char *descr)
{
  struct keymap_t *map, *tmp, *last = NULL, *next;
  keycode_t buf[MAX_SEQ];
  int len, pos = 0, lastpos = 0;

  len = parsekeys (s, buf, MAX_SEQ);

  map = allocKeys (len, buf);
  map->op = op;
  map->macro = safe_strdup (macro);
  map->descr = safe_strdup (descr);

  tmp = Keymaps[menu];

  while (tmp)
  {
    if (pos >= len || pos >= tmp->len)
    {
      /* map and tmp match, but have different lengths, so overwrite */
      do
      {
	len = tmp->eq;
	next = tmp->next;
	FREE (&tmp->macro);
	FREE (&tmp->keys);
	FREE (&tmp->descr);
	FREE (&tmp);
	tmp = next;
      }
      while (tmp && len >= pos);
      map->eq = len;
      break;
    }
    else if (buf[pos] == tmp->keys[pos])
      pos++;
    else if (buf[pos] < tmp->keys[pos])
    {
      /* found location to insert between last and tmp */
      map->eq = pos;
      break;
    }
    else /* buf[pos] > tmp->keys[pos] */
    {
      last = tmp;
      lastpos = pos;
      if (pos > tmp->eq)
	pos = tmp->eq;
      tmp = tmp->next;
    }
  }

  map->next = tmp;
  if (last)
  {
    last->next = map;
    last->eq = lastpos;
  }
  else
    Keymaps[menu] = map;
}

void km_bindkey (char *s, int menu, int op)
{
  km_bind (s, menu, op, NULL, NULL);
}

static int get_op (struct binding_t *bindings, const char *start, size_t len)
{
  int i;

  for (i = 0; bindings[i].name; i++)
  {
    if (!mutt_strncasecmp (start, bindings[i].name, len) &&   
	mutt_strlen (bindings[i].name) == len)
      return bindings[i].op;
  }

  return OP_NULL;
}

static char *get_func (struct binding_t *bindings, int op)
{
  int i;

  for (i = 0; bindings[i].name; i++)
  {
    if (bindings[i].op == op)
      return bindings[i].name;
  }

  return NULL;
}

static void push_string (char *s)
{
  char *pp, *p = s + mutt_strlen (s) - 1;
  size_t l;
  int i, op = OP_NULL;

  while (p >= s)
  {
    /* if we see something like "<PageUp>", look to see if it is a real
       function name and return the corresponding value */
    if (*p == '>')
    {
      for (pp = p - 1; pp >= s && *pp != '<'; pp--)
	;
      if (pp >= s)
      {
	if ((i = parse_fkey (pp)) > 0)
	{
	  mutt_ungetch (KEY_F (i), 0);
	  p = pp - 1;
	  continue;
	}

	l = p - pp + 1;
	for (i = 0; KeyNames[i].name; i++)
	{
	  if (!mutt_strncasecmp (pp, KeyNames[i].name, l))
	    break;
	}
	if (KeyNames[i].name)
	{
	  /* found a match */
	  mutt_ungetch (KeyNames[i].value, 0);
	  p = pp - 1;
	  continue;
	}

	/* See if it is a valid command
	 * skip the '<' and the '>' when comparing */
	for (i = 0; Menus[i].name; i++)
	{
	  struct binding_t *binding = km_get_table (Menus[i].value);
	  if (binding)
	  {
	    op = get_op (binding, pp + 1, l - 2);
	    if (op != OP_NULL)
	      break;
	  }
	}

	if (op != OP_NULL)
	{
	  mutt_ungetch (0, op);
	  p = pp - 1;
	  continue;
	}
      }
    }
    mutt_ungetch (*p--, 0);
  }
}

static int retry_generic (int menu, keycode_t *keys, int keyslen, int lastkey)
{
  if (menu != MENU_EDITOR && menu != MENU_GENERIC && menu != MENU_PAGER)
  {
    if (lastkey)
      mutt_ungetch (lastkey, 0);
    for (; keyslen; keyslen--)
      mutt_ungetch (keys[keyslen - 1], 0);
    return (km_dokey (MENU_GENERIC));
  }
  if (menu != MENU_EDITOR)
  {
    /* probably a good idea to flush input here so we can abort macros */
    mutt_flushinp ();
  }
  return OP_NULL;
}

/* return values:
 *	>0		function to execute
 *	OP_NULL		no function bound to key sequence
 *	-1		error occured while reading input
 */
int km_dokey (int menu)
{
  event_t tmp;
  struct keymap_t *map = Keymaps[menu];
  int pos = 0;
  int n = 0;
  int i;

  if (!map)
    return (retry_generic (menu, NULL, 0, 0));

  FOREVER
  {
    /* ncurses doesn't return on resized screen when timeout is set to zero */
    if (menu != MENU_EDITOR)
      timeout ((Timeout > 0 ? Timeout : 60) * 1000);

    tmp = mutt_getch();

    if (menu != MENU_EDITOR)
      timeout (-1); /* restore blocking operation */

    LastKey = tmp.ch;
    if (LastKey == -1)
      return -1;

    /* do we have an op already? */
    if (tmp.op)
    {
      char *func = NULL;
      struct binding_t *bindings;

      /* is this a valid op for this menu? */
      if ((bindings = km_get_table (menu)) &&
	  (func = get_func (bindings, tmp.op)))
	return tmp.op;

      if (menu == MENU_EDITOR && get_func (OpEditor, tmp.op))
	return tmp.op;

      if (menu != MENU_EDITOR && menu != MENU_PAGER)
      {
	/* check generic menu */
	bindings = OpGeneric; 
	if ((func = get_func (bindings, tmp.op)))
	  return tmp.op;
      }

      /* Sigh. Valid function but not in this context.
       * Find the literal string and push it back */
      for (i = 0; Menus[i].name; i++)
      {
	bindings = km_get_table (Menus[i].value);
	if (bindings)
	{
	  func = get_func (bindings, tmp.op);
	  if (func)
	  {
	    /* careful not to feed the <..> as one token. otherwise 
	    * push_string() will push the bogus op right back! */
	    mutt_ungetch ('>', 0);
	    push_string (func);
	    mutt_ungetch ('<', 0);
	    break;
	  }
	}
      }
      /* continue to chew */
      if (func)
	continue;
    }

    /* Nope. Business as usual */
    while (LastKey > map->keys[pos])
    {
      if (pos > map->eq || !map->next)
	return (retry_generic (menu, map->keys, pos, LastKey));
      map = map->next;
    }

    if (LastKey != map->keys[pos])
      return (retry_generic (menu, map->keys, pos, LastKey));

    if (++pos == map->len)
    {

      if (map->op != OP_MACRO)
	return map->op;

      if (n++ == 10)
      {
	mutt_flushinp ();
	mutt_error _("Macro loop detected.");
	return -1;
      }

      push_string (map->macro);
      map = Keymaps[menu];
      pos = 0;
    }
  }

  /* not reached */
}

static void create_bindings (struct binding_t *map, int menu)
{
  int i;

  for (i = 0 ; map[i].name ; i++)
    if (map[i].seq)
      km_bindkey (map[i].seq, menu, map[i].op);
}

char *km_keyname (int c)
{
  static char buf[10];
  char *p;

  if ((p = mutt_getnamebyvalue (c, KeyNames)))
    return p;

  if (c < 256 && c > -128 && iscntrl ((unsigned char) c))
  {
    if (c < 0)
      c += 256;

    if (c < 128)
    {
      buf[0] = '^';
      buf[1] = (c + '@') & 0x7f;
      buf[2] = 0;
    }
    else
      snprintf (buf, sizeof (buf), "\\%d%d%d", c >> 6, (c >> 3) & 7, c & 7);
  }
  else if (c >= KEY_F0 && c < KEY_F(256)) /* this maximum is just a guess */
    sprintf (buf, "<F%d>", c - KEY_F0);
  else if (IsPrint (c))
    snprintf (buf, sizeof (buf), "%c", (unsigned char) c);
  else
    snprintf (buf, sizeof (buf), "\\x%hx", (unsigned short) c);
  return (buf);
}

int km_expand_key (char *s, size_t len, struct keymap_t *map)
{
  size_t l;
  int p = 0;

  if (!map)
    return (0);

  FOREVER
  {
    strfcpy (s, km_keyname (map->keys[p]), len);
    len -= (l = mutt_strlen (s));

    if (++p >= map->len || !len)
      return (1);

    s += l;
  }

  /* not reached */
}

struct keymap_t *km_find_func (int menu, int func)
{
  struct keymap_t *map = Keymaps[menu];

  for (; map; map = map->next)
    if (map->op == func)
      break;
  return (map);
}

void km_init (void)
{
  memset (Keymaps, 0, sizeof (struct keymap_t *) * MENU_MAX);

  create_bindings (OpAttach, MENU_ATTACH);
  create_bindings (OpBrowser, MENU_FOLDER);
  create_bindings (OpCompose, MENU_COMPOSE);
  create_bindings (OpMain, MENU_MAIN);
  create_bindings (OpPager, MENU_PAGER);
  create_bindings (OpPost, MENU_POST);
  create_bindings (OpQuery, MENU_QUERY);



#ifdef HAVE_PGP
  create_bindings (OpPgp, MENU_PGP);
#endif

#ifdef MIXMASTER
  create_bindings (OpMix, MENU_MIX);
  
  km_bindkey ("<space>", MENU_MIX, OP_GENERIC_SELECT_ENTRY);
  km_bindkey ("h", MENU_MIX, OP_MIX_CHAIN_PREV);
  km_bindkey ("l", MENU_MIX, OP_MIX_CHAIN_NEXT);
#endif
  
  /* bindings for the line editor */
  create_bindings (OpEditor, MENU_EDITOR);
  
  km_bindkey ("<up>", MENU_EDITOR, OP_EDITOR_HISTORY_UP);
  km_bindkey ("<down>", MENU_EDITOR, OP_EDITOR_HISTORY_DOWN);
  km_bindkey ("<left>", MENU_EDITOR, OP_EDITOR_BACKWARD_CHAR);
  km_bindkey ("<right>", MENU_EDITOR, OP_EDITOR_FORWARD_CHAR);
  km_bindkey ("<home>", MENU_EDITOR, OP_EDITOR_BOL);
  km_bindkey ("<end>", MENU_EDITOR, OP_EDITOR_EOL);
  km_bindkey ("<backspace>", MENU_EDITOR, OP_EDITOR_BACKSPACE);
  km_bindkey ("<delete>", MENU_EDITOR, OP_EDITOR_BACKSPACE);
  km_bindkey ("\177", MENU_EDITOR, OP_EDITOR_BACKSPACE);
  
  /* generic menu keymap */
  create_bindings (OpGeneric, MENU_GENERIC);
  
  km_bindkey ("<home>", MENU_GENERIC, OP_FIRST_ENTRY);
  km_bindkey ("<end>", MENU_GENERIC, OP_LAST_ENTRY);
  km_bindkey ("<pagedown>", MENU_GENERIC, OP_NEXT_PAGE);
  km_bindkey ("<pageup>", MENU_GENERIC, OP_PREV_PAGE);
  km_bindkey ("<right>", MENU_GENERIC, OP_NEXT_PAGE);
  km_bindkey ("<left>", MENU_GENERIC, OP_PREV_PAGE);
  km_bindkey ("<up>", MENU_GENERIC, OP_PREV_ENTRY);
  km_bindkey ("<down>", MENU_GENERIC, OP_NEXT_ENTRY);
  km_bindkey ("1", MENU_GENERIC, OP_JUMP);
  km_bindkey ("2", MENU_GENERIC, OP_JUMP);
  km_bindkey ("3", MENU_GENERIC, OP_JUMP);
  km_bindkey ("4", MENU_GENERIC, OP_JUMP);
  km_bindkey ("5", MENU_GENERIC, OP_JUMP);
  km_bindkey ("6", MENU_GENERIC, OP_JUMP);
  km_bindkey ("7", MENU_GENERIC, OP_JUMP);
  km_bindkey ("8", MENU_GENERIC, OP_JUMP);
  km_bindkey ("9", MENU_GENERIC, OP_JUMP);

  km_bindkey ("<enter>", MENU_GENERIC, OP_GENERIC_SELECT_ENTRY);

  /* Miscellaneous extra bindings */
  
  km_bindkey (" ", MENU_MAIN, OP_DISPLAY_MESSAGE);
  km_bindkey ("<up>", MENU_MAIN, OP_MAIN_PREV_UNDELETED);
  km_bindkey ("<down>", MENU_MAIN, OP_MAIN_NEXT_UNDELETED);
  km_bindkey ("J", MENU_MAIN, OP_NEXT_ENTRY);
  km_bindkey ("K", MENU_MAIN, OP_PREV_ENTRY);
  km_bindkey ("x", MENU_MAIN, OP_EXIT);

  km_bindkey ("<enter>", MENU_MAIN, OP_DISPLAY_MESSAGE);

  km_bindkey ("x", MENU_PAGER, OP_EXIT);
  km_bindkey ("i", MENU_PAGER, OP_EXIT);
  km_bindkey ("<backspace>", MENU_PAGER, OP_PREV_LINE);
  km_bindkey ("<pagedown>", MENU_PAGER, OP_NEXT_PAGE);
  km_bindkey ("<pageup>", MENU_PAGER, OP_PREV_PAGE);
  km_bindkey ("<up>", MENU_PAGER, OP_MAIN_PREV_UNDELETED);
  km_bindkey ("<right>", MENU_PAGER, OP_MAIN_NEXT_UNDELETED);
  km_bindkey ("<down>", MENU_PAGER, OP_MAIN_NEXT_UNDELETED);
  km_bindkey ("<left>", MENU_PAGER, OP_MAIN_PREV_UNDELETED);
  km_bindkey ("<home>", MENU_PAGER, OP_PAGER_TOP);
  km_bindkey ("<end>", MENU_PAGER, OP_PAGER_BOTTOM);
  km_bindkey ("1", MENU_PAGER, OP_JUMP);
  km_bindkey ("2", MENU_PAGER, OP_JUMP);
  km_bindkey ("3", MENU_PAGER, OP_JUMP);
  km_bindkey ("4", MENU_PAGER, OP_JUMP);
  km_bindkey ("5", MENU_PAGER, OP_JUMP);
  km_bindkey ("6", MENU_PAGER, OP_JUMP);
  km_bindkey ("7", MENU_PAGER, OP_JUMP);
  km_bindkey ("8", MENU_PAGER, OP_JUMP);
  km_bindkey ("9", MENU_PAGER, OP_JUMP);

  km_bindkey ("<enter>", MENU_PAGER, OP_NEXT_LINE);
  
  km_bindkey ("<return>", MENU_ALIAS, OP_GENERIC_SELECT_ENTRY);
  km_bindkey ("<enter>",  MENU_ALIAS, OP_GENERIC_SELECT_ENTRY);
  km_bindkey ("<space>", MENU_ALIAS, OP_TAG);

  km_bindkey ("<enter>", MENU_ATTACH, OP_VIEW_ATTACH);
  km_bindkey ("<enter>", MENU_COMPOSE, OP_VIEW_ATTACH);

  /* edit-to (default "t") hides generic tag-entry in Compose menu
     This will bind tag-entry to  "T" in the Compose menu */
  km_bindkey ("T", MENU_COMPOSE, OP_TAG);
}

void km_error_key (int menu)
{
  char buf[SHORT_STRING];
  struct keymap_t *key;

  if(!(key = km_find_func(menu, OP_HELP)))
    key = km_find_func(MENU_GENERIC, OP_HELP);
  
  if(!(km_expand_key(buf, sizeof(buf), key)))
  {
    mutt_error _("Key is not bound.");
    return;
  }

  /* make sure the key is really the help key in this menu */
  push_string (buf);
  if (km_dokey (menu) != OP_HELP)
  {
    mutt_error _("Key is not bound.");
    return;
  }

  mutt_error (_("Key is not bound.  Press '%s' for help."), buf);
  return;
}

int mutt_parse_push (BUFFER *buf, BUFFER *s, unsigned long data, BUFFER *err)
{
  int r = 0;

  mutt_extract_token (buf, s, M_TOKEN_CONDENSE);
  if (MoreArgs (s))
  {
    strfcpy (err->data, _("push: too many arguments"), err->dsize);
    r = -1;
  }
  else
    push_string (buf->data);
  return (r);
}

/* expects to see: <menu-string> <key-string> */
char *parse_keymap (int *menu, BUFFER *s, BUFFER *err)
{
  BUFFER buf;

  memset (&buf, 0, sizeof (buf));

  /* menu name */
  mutt_extract_token (&buf, s, 0);
  if (MoreArgs (s))
  {
    if ((*menu = mutt_check_menu (buf.data)) == -1)
    {
      snprintf (err->data, err->dsize, _("%s: no such menu"), buf.data);
    }
    else
    {
      /* key sequence */
      mutt_extract_token (&buf, s, 0);

      if (!*buf.data)
      {
	strfcpy (err->data, _("null key sequence"), err->dsize);
      }
      else if (MoreArgs (s))
	return (buf.data);
    }
  }
  else
  {
    strfcpy (err->data, _("too few arguments"), err->dsize);
  }
  FREE (&buf.data);
  return (NULL);
}

static int
try_bind (char *key, int menu, char *func, struct binding_t *bindings)
{
  int i;
  
  for (i = 0; bindings[i].name; i++)
    if (mutt_strcmp (func, bindings[i].name) == 0)
    {
      km_bindkey (key, menu, bindings[i].op);
      return (0);
    }
  return (-1);
}

struct binding_t *km_get_table (int menu)
{
  switch (menu)
  {
    case MENU_MAIN:
      return OpMain;
    case MENU_GENERIC:
      return OpGeneric;
    case MENU_COMPOSE:
      return OpCompose;
    case MENU_PAGER:
      return OpPager;
    case MENU_POST:
      return OpPost;
    case MENU_FOLDER:
      return OpBrowser;
    case MENU_ATTACH:
      return OpAttach;
    case MENU_EDITOR:
      return OpEditor;
    case MENU_QUERY:
      return OpQuery;



#ifdef HAVE_PGP
    case MENU_PGP:
      return OpPgp;
#endif


#ifdef MIXMASTER
    case MENU_MIX:
      return OpMix;
#endif

  }
  return NULL;
}

/* bind menu-name '<key_sequence>' function-name */
int mutt_parse_bind (BUFFER *buf, BUFFER *s, unsigned long data, BUFFER *err)
{
  struct binding_t *bindings = NULL;
  char *key;
  int menu, r = 0;

  if ((key = parse_keymap (&menu, s, err)) == NULL)
    return (-1);

  /* function to execute */
  mutt_extract_token (buf, s, 0);
  if (MoreArgs (s))
  {
    strfcpy (err->data, _("bind: too many arguments"), err->dsize);
    r = -1;
  }
  else if (mutt_strcasecmp ("noop", buf->data) == 0)
    km_bindkey (key, menu, OP_NULL); /* the `unbind' command */
  else
  {
    /* First check the "generic" list of commands */
    if (menu == MENU_PAGER || menu == MENU_EDITOR || menu == MENU_GENERIC ||
	try_bind (key, menu, buf->data, OpGeneric) != 0)
    {
      /* Now check the menu-specific list of commands (if they exist) */
      bindings = km_get_table (menu);
      if (bindings && try_bind (key, menu, buf->data, bindings) != 0)
      {
	snprintf (err->data, err->dsize, _("%s: no such function in map"), buf->data);
	r = -1;
      }
    }
  }
  FREE (&key);
  return (r);
}

/* macro <menu> <key> <macro> <description> */
int mutt_parse_macro (BUFFER *buf, BUFFER *s, unsigned long data, BUFFER *err)
{
  int menu, r = -1;
  char *seq = NULL;
  char *key;

  if ((key = parse_keymap (&menu, s, err)) == NULL)
    return (-1);

  mutt_extract_token (buf, s, M_TOKEN_CONDENSE);
  /* make sure the macro sequence is not an empty string */
  if (!*buf->data)
  {
    strfcpy (err->data, _("macro: empty key sequence"), err->dsize);
  }
  else
  {
    if (MoreArgs (s))
    {
      seq = strdup (buf->data);
      mutt_extract_token (buf, s, M_TOKEN_CONDENSE);

      if (MoreArgs (s))
      {
	strfcpy (err->data, _("macro: too many arguments"), err->dsize);
      }
      else
      {
	km_bind (key, menu, OP_MACRO, seq, buf->data);
	r = 0;
      }

      FREE (&seq);
    }
    else
    {
      km_bind (key, menu, OP_MACRO, buf->data, NULL);
      r = 0;
    }
  }
  FREE (&key);
  return (r);
}

/* exec command-name */
int mutt_parse_exec (BUFFER *buf, BUFFER *s, unsigned long data, BUFFER *err)
{
  int ops[128]; 
  int nops = 0;
  struct binding_t *bindings = NULL;
  char *command;
  
  if (!MoreArgs (s))
  {
    strfcpy (err->data, _("exec: too few arguments"), err->dsize);
    return (-1);
  }

  do
  {
    mutt_extract_token (buf, s, 0);
    command = buf->data;

    if ((bindings = km_get_table (CurrentMenu)) == NULL 
	&& CurrentMenu != MENU_PAGER)
      bindings = OpGeneric;
    
    ops[nops] = get_op (bindings, command, mutt_strlen(command));
    if (ops[nops] == OP_NULL && CurrentMenu != MENU_PAGER)
      ops[nops] = get_op (OpGeneric, command, mutt_strlen(command));
    
    if (ops[nops] == OP_NULL)
    {
      mutt_flushinp ();
      mutt_error (_("%s: no such command"), command);
      return (-1);
    }
    nops++;
  }
  while(MoreArgs(s) && nops < sizeof(ops)/sizeof(ops[0]));
  
  while(nops)
    mutt_ungetch(0, ops[--nops]);
  
  return 0;
}
