#include <ncurses.h>

/*TO COMPILE USE -lncurses FLAG*/

/*Useful ncurses stuff:
curs_set(int) -> 0=invisable,1=visable,2=very visable
attron(A_DIM) -> half bright(doesn't work)
attron(A_BOLD) -> bolds char (works)*/
int main(int argc, char **argv)
{
	int x,y,maxx,maxy;

	initscr(); //start ncurses
	start_color();
	noecho();
	raw();
	getmaxyx(stdscr,maxy,maxx);//gets the size of the screen
	if(!can_change_color())
		printw("cant change color ");
	init_pair(1, COLOR_BLACK, COLOR_CYAN);
	init_pair(2, COLOR_WHITE, COLOR_BLUE);
	init_pair(3, COLOR_BLACK, COLOR_CYAN);
	init_pair(4, COLOR_WHITE, COLOR_BLUE);
	keypad(stdscr,TRUE);
	attron(A_BOLD);//add a attribute (bold)
	printw("bold test");//print
	attroff(A_BOLD);//remove a attribute
	printw(" less bold");
	mvprintw(1,0,"cursor test, press q to quit");//move then print
	getyx(stdscr,y,x);//get position of cursor
	int ch = getch();
	while(ch!= 'q')
	{
		switch(ch)
		{
			case KEY_UP:
			case 'w':
				if(y)
				{
					y--;
					move(y,x);
				}
				break;
			case KEY_DOWN:
			case 's':
				if(y<maxy-1)
				{
					y++;
					move(y,x);
				}
				break;
			case KEY_RIGHT:
			case 'd':
				if(x<maxx-1)
				{
					x++;
					move(y,x);
				}
				break;
			case KEY_LEFT:
			case 'a':
				if(x)
				{
					x--;
					move(y,x);
				}
				break;
		}
		refresh();//refesh screen
		ch = getch();
	}
	endwin(); //end ncurses

	return 0;
}