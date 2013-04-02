#include "build_panel.h"

BuildPanel::BuildPanel(std::vector<UnitType *> &unit_types, Player *play, int scr_x, int scr_y, int panel_size) :
    types(unit_types),
    win(NULL),
    pl(play),
    size(panel_size),
    opt(0)
{
    resize(scr_x,scr_y)
}

BuildPanel::~BuildPanel()
{
    delwin(win);
}

void BuildPanel::resize(int scr_x, int scr_y)
{
    win = newwin(scr_y,scr_x-size,0,scr_x-size+1);
    wattron(win,COLOR_PAIR(15));
    for(int i=0;i<types.size();i++)
    {
        if(opt==i)
        {
            wattroff(win,COLOR_PAIR(15));
            wattron(win,COLOR_PAIR(16));
        }
        mvwprintw(win,4+2*i,0,types[i]->get_unit_name.c_str());
        waddch(win,' ');
        waddstr(win,atoi(type[i]->get_unit_cost()));
        if(opt==i)
        {
            wattroff(win,COLOR_PAIR(15));
            wattron(win,COLOR_PAIR(16));
        }
    }
    if(opt == types.size())
    {
        wattroff(win,COLOR_PAIR(15));
        wattron(win,COLOR_PAIR(16));
        mvwprintw(win,scr_y-2,0,"EXIT");
        wattroff(win,COLOR_PAIR(16));
        wattron(win,COLOR_PAIR(15));
    }else{
        mvwprintw(win,scr_y-2,0,"EXIT");
    }
}

Unit *BuildPanel::use_panel()
{
    int temp1, temp2;
    wnoutrefresh(win);
    doupdate();
    while(true)
    {
        int ch = getch();
        switch(ch)
        {
            case KEY_UP:
                if(opt == types.size())
                {
                    mvwprintw(win,scr_y-2,0,"EXIT");
                    for(;temp2<size;temp2++)
                        waddch(win,' ');
                    opt = 0;
                }else{
                    mvwprintw(win,4+2*opt,0,types[opt]->get_unit_name.c_str());
                    waddch(win,' ');
                    waddstr(win,atoi(type[opt]->get_unit_cost()));
                    getyx(win,temp1,temp2);
                    for(;temp2<size;temp2++)
                        waddch(win,' ');
                    opt++;
                }
                wattroff(win,COLOR_PAIR(15));
                wattron(win,COLOR_PAIR(16));
                if(opt == types.size())
                {
                    mvwprintw(win,scr_y-2,0,"EXIT");
                    for(;temp2<size;temp2++)
                        waddch(win,' ');
                }else{
                    mvwprintw(win,4+2*opt,0,types[opt]->get_unit_name.c_str());
                    waddch(win,' ');
                    waddstr(win,atoi(type[opt]->get_unit_cost()));
                    getyx(win,temp1,temp2);
                    for(;temp2<size;temp2++)
                        waddch(win,' ');
                }
                wattroff(win,COLOR_PAIR(16));
                wattron(win,COLOR_PAIR(15));
                break;
            case KEY_DOWN:
                if(opt == types.size())
                {
                    mvwprintw(win,scr_y-2,0,"EXIT");
                    for(;temp2<size;temp2++)
                        waddch(win,' ');
                    opt--;
                }else{
                    mvwprintw(win,4+2*opt,0,types[opt]->get_unit_name.c_str());
                    waddch(win,' ');
                    waddstr(win,atoi(type[opt]->get_unit_cost()));
                    getyx(win,temp1,temp2);
                    for(;temp2<size;temp2++)
                        waddch(win,' ');
                    if(opt==0)
                    {
                        opt = types.size();
                    }else{
                        opt--;
                    }
                }
                wattroff(win,COLOR_PAIR(15));
                wattron(win,COLOR_PAIR(16));
                if(opt == types.size())
                {
                    mvwprintw(win,scr_y-2,0,"EXIT");
                    for(;temp2<size;temp2++)
                        waddch(win,' ');
                }else{
                    mvwprintw(win,4+2*opt,0,types[opt]->get_unit_name.c_str());
                    waddch(win,' ');
                    waddstr(win,atoi(type[opt]->get_unit_cost()));
                    getyx(win,temp1,temp2);
                    for(;temp2<size;temp2++)
                        waddch(win,' ');
                }
                wattroff(win,COLOR_PAIR(16));
                wattron(win,COLOR_PAIR(15));
                break;
            case 'z':
                if(opt==types.size())
                    return NULL;
                Unit *temp_ptr = Unit(types.opt,pl);
                return temp_ptr;
                break;
            default:
                break;
        }
    }
    return NULL;
}
