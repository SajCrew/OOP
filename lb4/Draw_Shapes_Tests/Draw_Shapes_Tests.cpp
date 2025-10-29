#define CATCH_CONFIG_MAIN
#include "../Shapes/CRectangle.h"
#include "../Shapes/CCircle.h"
#include "catch.hpp"
#include "../Draw_Shapes/MockCanvas.h"

TEST_CASE("Rectangle drawing") {
    CRectangle rect(CPoint(10, 10), 20, 30, 0xFF0000, 0x00FF00);
    MockCanvas canvas;

    rect.Draw(canvas);
    auto commands = canvas.GetCommands();

    REQUIRE(commands.size() == 5);
    REQUIRE(commands[0].type == "fill_poly");
    REQUIRE(commands[0].points.size() == 4);
    REQUIRE(commands[1].type == "line");
}

TEST_CASE("Circle drawing") {
    CCircle circle(CPoint(50, 50), 10, 0x0000FF, 0xFF00FF);
    MockCanvas canvas;

    circle.Draw(canvas);
    auto commands = canvas.GetCommands();

    REQUIRE(commands.size() == 2);
    REQUIRE(commands[0].type == "fill_circle");
    REQUIRE(commands[1].type == "draw_circle");
}