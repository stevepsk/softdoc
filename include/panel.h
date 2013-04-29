#ifndef PANEL_H
#define PANEL_H

#include <curses.h>
#include "unit.h"

//Class that creates an information panel on the screen
class Panel
{
    int scr_x, scr_y;//total size of screen
    int size;//panel width
    int pos_x;//panel starting x position
    int terrain_pos;//line with terrain info
    int unit_name_pos;//line with unit name
    int move_pos;//line with unit move info
    int selected_unit_pos;
    WINDOW *panel_window;

    //unsued constructors to stop warnings
    void operator=(const Panel &p);

    public:
    Panel(int screen_x, int screen_y, int panel_size);
    ~Panel();
    void update(int terrain, Unit *unit, Unit *selected, int path_length);
    void resize(int screen_x, int screen_y, int terrain, Unit *unit, Unit *selected, int path);
    int get_size();
};

#endif
