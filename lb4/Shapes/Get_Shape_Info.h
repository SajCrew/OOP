#include "Create_Shapes.h"
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <memory>

//� �����
const IShape* FindMaxArea(const vector<unique_ptr<IShape>>& shapes);

const IShape* FindMinPerimeter(const vector<unique_ptr<IShape>>& shapes);

void PrintInfo(vector<unique_ptr<IShape>>& shapes);