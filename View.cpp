#include <iostream>
#include "View.h"
using namespace std;

View::View()
{
    size = 11;
    scale = 2;
    origin = Point2D(0,0);
}

void View::Clear()
{
    for (int i = 0; i < view_maxsize; ++i)
    {
        for (int j = 0; j < view_maxsize; ++j)
        {
            grid[i][j][0] = '.';
            grid[i][j][1] = ' ';
        }
    }
}

void View::Plot(GameObject* ptr)
{
    if (ptr->ShouldBeVisible())
    {
        int x, y;
        if (GetSubscripts(x, y, ptr->GetLocation()) == true)
        {
            if (grid[x][y][0] == '.')
            {
                ptr->DrawSelf(grid[x][y]);
            }
            else
            {
                grid[x][y][0] = '*';
                grid[x][y][1] = ' ';
            }
        }
    }
}

void View::Draw()
{
    for (int j = size-1; j >= -1; j--)
    {
        for (int i = -1; i <= size-1; i++)
        {
            //grid axis
            if (i == -1 && j%2 == 0)
            {
                cout << j*2;
                if (j/5 == 0)
                {
                    cout << " ";
                }
            }
            else if (i == -1 && j%2 != 0)
            {
                cout << "  ";
            }
            else if (j == -1 && i%2 == 0)
            {
                cout << i*2;
                if (i/5 == 0)
                {
                    cout << " ";
                }
                cout << "  ";
            }
            if (i >= 0 && j >=0)
            {
                cout << grid[i][j][0] << grid[i][j][1];
            }
        }
        cout << endl;
    }
}
bool View::GetSubscripts(int &out_x, int &out_y, Point2D location)
{
    int x = (location.x - origin.x) / scale;
    int y = (location.y - origin.y) / scale;

    if ((x <= view_maxsize) && (y <= view_maxsize))
    {
        out_x = x;
        out_y = y;
        return true;
    }
    else
    {
        cout << "An object is outside the display." << endl;
        return false;
    }    
}