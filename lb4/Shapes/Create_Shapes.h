#include "IShape.h"
#include <sstream>
#include "map"
#include <string>
#include "stdexcept"
#include "iostream"
#include "vector"
#include "CLineSegment.h"
#include "CTriangle.h"
#include "CRectangle.h"
#include "CCircle.h"
#include "CPoint.h"
#include <optional>

std::optional<CPoint> ParsePoint(istringstream& iss);

bool ParseColor(std::istringstream& iss, uint32_t& color);

unique_ptr<IShape> CreateRectangle(istringstream& iss);

unique_ptr<IShape> CreateTriangle(istringstream& iss);

unique_ptr<IShape> CreateCircle(istringstream& iss);

unique_ptr<IShape> CreateLineSegment(istringstream& iss);

unique_ptr<IShape> CreateShape(const string& line);

void FindShapes(string& line, vector<unique_ptr<IShape>>& shapes);