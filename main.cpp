#include <iostream>
#include "GameCommand.h"
#include "Input_Handling.h"
using namespace std;

int main()
{
    cout << "EC327: Introduction to Software Engineering" << endl;
    cout << "Fall 2022 - PA3" << endl;
    cout << "Pokemon"
            << '\n';
    Model* m = new Model();
    View* v  = new View();

    bool run = 1;
    char command = ' ';

    m->ShowStatus();
    m->Display(*v);
    
    while (run)
    {   
        int in_id;
        int obj_id;
        unsigned int amount;
        Point2D move;
        cout << "Enter command: ";
        cin >> command;
        try
        {
        if (command != 'm' && command != 'c' && command != 'g' && command != 's' && command != 'b' && command != 'p' && command != 'a' && command != 'r' && command != 'q')
        {
            throw Invalid_Input("Valid Commands are exclusively m, c, g, s, b, p, a, r, and q");
        }

        switch (command)
        {
        case 'm':
            cin >> in_id >> move.x >> move.y;
            cout << move.x << move.y;
            if (!(cin >> in_id, move.x, move.y))
            {
                throw Invalid_Input("Was expecting three integers");
            }
            DoMoveCommand(*m, in_id, move);
            m->Display(*v);
            break;

        case 'c':
            cin >> in_id >> obj_id;
            if (!(cin >> in_id >> obj_id))
            {
                throw Invalid_Input("Was expecting two integers");
            }
            DoMoveToCenterCommand(*m, in_id, obj_id);
            m->Display(*v);
            break;
        
        case 'g':
            cin >> in_id >> obj_id;
            if (!(cin >> in_id >> obj_id))
            {
                throw Invalid_Input("Was expecting two integers");
            }
            DoMoveToGymCommand(*m, in_id, obj_id);
            m->Display(*v);
            break;

        case 's':
            cin >> in_id >> obj_id;
            if (!(cin >> in_id >> obj_id))
            {
                throw Invalid_Input("Was expecting two integers");
            }
            DoStopCommand(*m, in_id); 
            m->Display(*v);
            break;

        case 'b':
            cin >> in_id >> amount;
            if (!(cin >> in_id >> amount))
            {
                throw Invalid_Input("Was expecting two integers");
            }
            DoBattleCommand(*m, in_id, amount);
            m->Display(*v);
            break;

        case 'p':
            cin >> in_id >> amount;
            if (!(cin >> in_id >> amount))
            {
                throw Invalid_Input("Was expecting two integers");
            }
            DoRecoverInCenterCommand(*m, in_id, amount);
            m->Display(*v);
            break;
        
        case 'a':
            DoAdvanceCommand(*m, *v);
            m->ShowStatus();
            break;

        case 'r':
            DoRunCommand(*m, *v);
            m->ShowStatus();
            break;
            
        case 'q':
            exit(0);
        
        default:
            break;
        }
        }
        catch (Invalid_Input& except)
        {
            cout << "Invalid input - " << except.msg_ptr << endl;
            cin.clear();
            cin.ignore(50, '\n');
        }
    }

    return 0;
}