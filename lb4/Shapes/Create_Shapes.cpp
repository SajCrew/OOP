#include "Create_Shapes.h"

std::optional<CPoint> ParsePoint(istringstream& iss)
{
    double x, y;
    if (iss >> x >> y)
    {
        return CPoint(x, y);
    }
    return std::nullopt;
}

std::optional<double> ParseSegment(istringstream& iss)
{
    double seg;
    if ((iss >> seg) && (seg > 0))
    {
        return seg;
    }
    return std::nullopt;
}

bool ParseColor(std::istringstream& iss, uint32_t& color) 
{
    std::string hexStr;
    if (iss >> hexStr && hexStr.length() == 6) 
    {
        try 
        {
            // Конвертируем RRGGBB в AABBGGRR
            uint32_t rr = std::stoul(hexStr.substr(0, 2), nullptr, 16);
            uint32_t gg = std::stoul(hexStr.substr(2, 2), nullptr, 16);
            uint32_t bb = std::stoul(hexStr.substr(4, 2), nullptr, 16);

            color = 0xFF000000 | // Альфа-канал (непрозрачность)
                (bb << 16) |  // Синий
                (gg << 8) |   // Зелёный
                 rr;           // Красный
            return true;
        }
        catch (...) { return false;}
    }
    return false;
}

//iss: x y width height outline fillcolor
unique_ptr<IShape> CreateRectangle(istringstream& iss)
{
    uint32_t outlineColor, fillColor;

    auto leftTop = ParsePoint(iss); 

    auto width = ParseSegment(iss);
    auto height = ParseSegment(iss);

    if (leftTop == nullopt && leftTop != nullopt && width != nullopt &&
        height != nullopt &&
        ParseColor(iss, outlineColor) &&
        ParseColor(iss, fillColor))
    {
        return make_unique<CRectangle>(*leftTop, *width, *height, outlineColor, fillColor);
    }
    return nullptr;
}

unique_ptr<IShape> CreateTriangle(istringstream& iss)
{
    auto v1 = ParsePoint(iss);
    auto v2 = ParsePoint(iss);
    auto v3 = ParsePoint(iss);

    uint32_t outlineColor, fillColor;

    if ((v1 != nullopt) && 
        (v2 != nullopt) && 
        (v3 != nullopt) && 
        ParseColor(iss, outlineColor) && 
        ParseColor(iss, fillColor))
    {
        return make_unique<CTriangle>(*v1, *v2, *v3, outlineColor, fillColor);
    }
    return nullptr;
}

unique_ptr<IShape> CreateCircle(istringstream& iss)
{
    uint32_t outlineColor, fillColor;
    auto center = ParsePoint(iss);
    auto radius = ParseSegment(iss);

    if (center != nullopt && ParseColor(iss, outlineColor) && ParseColor(iss, fillColor)) 
    {
        return make_unique<CCircle>(*center, *radius, outlineColor, fillColor);     
    }
    return nullptr;
}

unique_ptr<IShape> CreateLineSegment(istringstream& iss)
{
    uint32_t outlineColor;
 
    auto start = ParsePoint(iss);
    auto end = ParsePoint(iss);

    if (start != nullopt &&
        end != nullopt &&
        ParseColor(iss, outlineColor))
    {
        return make_unique<CLineSegment>(*start, *end, outlineColor);
    }
    return nullptr;
}

unique_ptr<IShape> CreateShape(const string& line)
{
    istringstream iss(line);
    string type;
    iss >> type;

    if (type == "") throw::runtime_error("Empty input");

    enum ShapeType { RECTANGLE, TRIANGLE, CIRCLE, LINE, UNKNOWN };

    static const map<string, ShapeType> typeMap =
    {
        {"rectangle", RECTANGLE},
        {"triangle", TRIANGLE},
        {"circle", CIRCLE},
        {"line", LINE}
    };

    auto it = typeMap.find(type);

    ShapeType shapeType = (it != typeMap.end()) ? it->second : UNKNOWN;
    unique_ptr<IShape> result;

    switch (shapeType)
    {
    case RECTANGLE:
        result = CreateRectangle(iss);
        break;
    case TRIANGLE:
        result = CreateTriangle(iss);
        break;
    case CIRCLE:
        result = CreateCircle(iss);
        break;
    case LINE:
        result = CreateLineSegment(iss);
        break;
    default:
        throw std::runtime_error("Неизвестная фигура");
        return nullptr;
    }
    return result;
}

void FindShapes(string& line, vector<unique_ptr<IShape>>& shapes)
{
    try
    {
        auto shape = CreateShape(line);
        if (shape)
        {
            shapes.push_back(move(shape));
        }
    }
    catch (const std::runtime_error& e)
    {
        cout << e.what() << endl;
    }
}