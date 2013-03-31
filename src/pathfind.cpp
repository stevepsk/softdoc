#include "pathfind.h"

Pathfind::Pathfind(int start_x, int start_y, Unit *unit_ptr, Map *map_ptr) :
    path_map(NULL),
    x_offset(start_x-MAX_PATH),
    y_offset(start_y-MAX_PATH),
    unit(unit_ptr),
    map(map_ptr)
{
    path_map = new int * [2*MAX_PATH + 1];
    for(int i = 0;i<2*MAX_PATH+1;i++)
    {
        path_map[i] = new int [2*MAX_PATH+1];
    }
}

Pathfind::~Pathfind()
{
    for(int i = 0;i<2*MAX_PATH+1;i++)
        delete [] path_map[i];
    delete[] path_map;
}

int Pathfind::dist_est(int x0, int y0, int x, int y)
{
    int temp = x0 - x_offset - x + y0 - y_offset - y;
    if(temp < 0)
        temp = -temp;
    return temp;
}

int Pathfind::find_dist(int x, int y)
{
    std::list<position> stack; //should be priority queue
    tile_pair *ptr;
    position temp;

    if(x<x_offset-1 || y<y_offset-1 || x>x_offset+2*MAX_PATH || y>y_offset+2*MAX_PATH)
        return -1;
    for(int i=0;i<2*MAX_PATH+1;i++)
    {
        for(int j=0;j<2*MAX_PATH+1;j++)
            path_map[i][j] = -1;
    }
    path_map[MAX_PATH][MAX_PATH] = 0;
    temp.x = MAX_PATH;
    temp.y = MAX_PATH;
    stack.push_back(temp);
    while(!stack.empty())
    {
        std::list<position>::iterator itr,min_itr;
        itr = min_itr = stack.begin();
        itr++;
        for(;itr!=stack.end();itr++)
        {
            if(path_map[itr->x][itr->y]+dist_est(x,y,itr->x,itr->y) < path_map[min_itr->x][min_itr->y] + dist_est(x,y,min_itr->x,min_itr->y))
                min_itr = itr;
        }
        ptr = map->get_tile(min_itr->x+x_offset+1,min_itr->y+y_offset);
        if(min_itr->x+1 < 2*MAX_PATH+1 && ptr) 
        {
            if(path_map[min_itr->x+1][min_itr->y]==-1 || path_map[min_itr->x+1][min_itr->y] > path_map[min_itr->x][min_itr->y] + unit->terrain(ptr->terrain)) 
            {
                path_map[min_itr->x+1][min_itr->y] = path_map[min_itr->x][min_itr->y] + unit->terrain(ptr->terrain);
                temp = *min_itr;
                temp.x++;
                stack.push_back(temp);
            }
        }
        ptr = map->get_tile(min_itr->x+x_offset-1,min_itr->y+y_offset);
        if(min_itr->x-1 > -1 && ptr)
        {
            if(path_map[min_itr->x-1][min_itr->y]==-1 || path_map[min_itr->x-1][min_itr->y] > path_map[min_itr->x][min_itr->y] + unit->terrain(ptr->terrain)) 
            {
                path_map[min_itr->x-1][min_itr->y] = path_map[min_itr->x][min_itr->y] + unit->terrain(ptr->terrain);
                temp = *min_itr;
                temp.x--;
                stack.push_back(temp);
            }
        }
        ptr = map->get_tile(min_itr->x+x_offset,min_itr->y+y_offset-1);
        if(min_itr->y-1 > -1 && ptr)
        {
            if(path_map[min_itr->x][min_itr->y-1]==-1 || path_map[min_itr->x][min_itr->y-1] > path_map[min_itr->x][min_itr->y] + unit->terrain(ptr->terrain)) 
            {
                path_map[min_itr->x][min_itr->y-1] = path_map[min_itr->x][min_itr->y] + unit->terrain(ptr->terrain);
                temp = *min_itr;
                temp.y--;
                stack.push_back(temp);
            }
        }
        ptr = map->get_tile(min_itr->x+x_offset,min_itr->y+y_offset+1);
        if(min_itr->y+1 < 2*MAX_PATH+1 && ptr)
        {
            if(path_map[min_itr->x][min_itr->y+1]==-1 || path_map[min_itr->x][min_itr->y+1] > path_map[min_itr->x][min_itr->y] + unit->terrain(ptr->terrain)) 
            {
                path_map[min_itr->x][min_itr->y+1] = path_map[min_itr->x][min_itr->y] + unit->terrain(ptr->terrain);
                temp = *min_itr;
                temp.y++;
                stack.push_back(temp);
            }
        }
        stack.remove(min_itr);
        if(path_map[x-x_offset][y-y_offset] != -1)
            return path_map[x-x_offset][y-y_offset];
    }
    return -1; //should never get here
}