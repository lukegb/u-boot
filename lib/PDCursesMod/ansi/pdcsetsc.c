#include <stdio.h>
#include "../curspriv.h"
#include "pdcansi.h"

/*man-start**************************************************************

pdcsetsc
--------

### Synopsis

    int PDC_set_blink(bool blinkon);
    int PDC_set_bold(bool boldon);
    void PDC_set_title(const char *title);

### Description

   PDC_set_blink() toggles whether the A_BLINK attribute sets an actual
   blink mode (TRUE), or sets the background color to high intensity
   (FALSE). The default is platform-dependent (FALSE in most cases). It
   returns OK if it could set the state to match the given parameter,
   ERR otherwise.

   PDC_set_bold() toggles whether the A_BOLD attribute selects an actual
   bold font (TRUE), or sets the foreground color to high intensity
   (FALSE). It returns OK if it could set the state to match the given
   parameter, ERR otherwise.

   PDC_set_title() sets the title of the window in which the curses
   program is running. This function may not do anything on some
   platforms.

### Portability
                             X/Open  ncurses  NetBSD
    PDC_set_blink               -       -       -
    PDC_set_title               -       -       -

**man-end****************************************************************/

    /* #define BLINKING_CURSOR   "\033[?12h"    */
#define BLINKING_BLOCK      "\033[1 q"
#define STEADY_BLOCK        "\033[2 q"
#define BLINKING_UNDERLINE  "\033[3 q"
#define STEADY_UNDERLINE    "\033[4 q"
      /* "bar" = "vertical line".  xterm only. */
#define BLINKING_BAR        "\033[5 q"
#define STEADY_BAR          "\033[6 q"
#define CURSOR_ON           "\033[?25h"
#define CURSOR_OFF          "\033[?25l"

void PDC_puts_to_stdout( const char *buff);

int PDC_curs_set( int visibility)
{
    int ret_vis;

    PDC_LOG("PDC_curs_set() - called: visibility=%d\n", visibility);

    ret_vis = SP->visibility;

    if( !SP->visibility && visibility)    /* turn cursor back on */
        PDC_puts_to_stdout( CURSOR_ON);
    else if( SP->visibility && !visibility)
        PDC_puts_to_stdout( CURSOR_OFF);
    SP->visibility = visibility;
    return ret_vis;
}

static int reset_attr( const attr_t attr, const bool attron)
{
    attr_t prev_termattrs;

    if (!SP)
        return ERR;
    prev_termattrs = SP->termattrs;
    if( attron)
        SP->termattrs |= attr;
    else
        SP->termattrs &= ~attr;
    if( prev_termattrs != SP->termattrs)
       curscr->_clear = TRUE;
    return OK;
}

int PDC_set_blink(bool blinkon)
{
   return( reset_attr( A_BLINK, blinkon));
}

int PDC_set_bold(bool boldon)
{
   return( reset_attr( A_BOLD, boldon));
}

void PDC_set_title( const char *title)
{
    (void)title;
    PDC_LOG("PDC_set_title() - called:<%s>\n", title);
}