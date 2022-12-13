#ifndef GameObject_H
#define GameObject_H
#include "Point2D.h"
#include "Vector2D.h"
using namespace std;

class GameObject
{
    protected:
    Point2D location;
    int id_num;
    char display_code;
    char state;
    
    public:
    GameObject(char);
    GameObject(Point2D, int, char);
    ~GameObject();
    Point2D GetLocation();
    int GetId();
    char GetState();
    virtual void ShowStatus();
    virtual bool ShouldBeVisible() = 0;
    virtual bool Update() = 0;
    void DrawSelf(char * ptr);
};

#endif