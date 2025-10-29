#include <stdexcept>
#include <iostream>
#include <vector>
#include "Get_Shape_Info.h"

int main()
{
    setlocale(LC_ALL, "ru");
	vector<unique_ptr<IShape>> shapes;
	string line;

    while (getline(cin, line))
    {
        FindShapes(line, shapes);
        PrintInfo(shapes);
    }
    return 0;
}

