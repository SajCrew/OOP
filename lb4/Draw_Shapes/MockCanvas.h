#pragma once
#include "ICanvas.h"
#include <vector>
#include <string>

struct DrawingCommand 
{
    std::string type;
    std::vector<CPoint> points;
    double radius;
    uint32_t color;
};

class MockCanvas : public ICanvas 
{
public:
    void DrawLine(CPoint from, CPoint to, uint32_t color) override 
    {
        commands.push_back({ "line", {from, to}, 0, color });
    }

    void FillPolygon(const std::vector<CPoint>& points, uint32_t fillColor) override 
    {
        commands.push_back({ "fill_poly", points, 0, fillColor });
    }

    void DrawCircle(CPoint center, double radius, uint32_t color) override 
    {
        commands.push_back({ "draw_circle", {center}, radius, color });
    }

    void FillCircle(CPoint center, double radius, uint32_t fillColor) override 
    {
        commands.push_back({ "fill_circle", {center}, radius, fillColor });
    }

    const std::vector<DrawingCommand>& GetCommands() const { return commands; }

private:
    std::vector<DrawingCommand> commands;
};