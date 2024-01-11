//Programteil für graphische Darstellung des Spiels
#include <vector>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <time.h>
using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::string;

void fillGameboard(vector<vector<char> > &v)
    {
        srand(time(NULL));
        vector<char> colors {'r', 'g', 'y', 'b', 'm'};
        for (int i = 0; i < v.size(); i++)
        {
            for (int j = 0; j < v[i].size(); j++)
            {
                
                int randomColor = rand() % colors.size();
                v[i][j] = colors[randomColor];
                
            }
        }
    }




void printGameboardColored(const vector<vector<char>> &v, int score = 0)
{
    const string red = "\033[0;31m";
    const string green = "\033[0;32m";
    const string yellow = "\033[0;33m";
    const string blue = "\033[0;34m";
    const string magenta = "\033[0;35m";
    const string space = "\033[0;30m";
   
    const string reset = "\033[0m";

    for (int i = 0; i < v.size(); i++)
    {
        cout << i << " ";
        for (int j = 0; j < v[i].size(); j++)
        {
            char square = 254;
            char emptySquare = 255;
            
            if (v[i][j] == 'r')
                cout << red << square << " " << reset;
            if (v[i][j] == 'g')
                cout << green << square << " " << reset;
            if (v[i][j] == 'y')
                cout << yellow << square << " " << reset;
            if (v[i][j] == 'b')
                cout << blue << square << " " << reset;
            if (v[i][j] == 's')
                cout << space << emptySquare << " " << reset;
            if (v[i][j] == 'm')
                cout << magenta << square << " " << reset;
        }
        cout << endl;
    }
    cout << "  0 1 2 3 4 5 6 7 8" << endl;
    cout << "Score: " << score << endl;
}

