#include <ncurses.h>

int main(void)
{
   int mx=0, my=0;

   initscr();
   getmaxyx(stdscr, mx, my);
   endwin();

   printf("%d %d", mx, my);

   return 0;
}
