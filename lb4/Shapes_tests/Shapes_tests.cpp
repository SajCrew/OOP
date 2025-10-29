#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <stdexcept>
#include "../Shapes/Get_Shape_Info.h"

TEST_CASE("Create Rectangle and get max area and min perimeter") 
{
    
    vector<unique_ptr<IShape>> shapes;
    CPoint leftTop (10.3, 20.15);
    CRectangle rectangle(leftTop, 30.7, 40.4, 0Xff0000, 0x00ff00);
    SECTION("Check properties") 
    {
        REQUIRE(rectangle.GetLeftTop().GetX() == Approx(10.3));
        REQUIRE(rectangle.GetLeftTop().GetY() == Approx(20.15));
        REQUIRE(rectangle.GetWidth() == Approx(30.7));
        REQUIRE(rectangle.GetHeight() == Approx(40.4));
        REQUIRE(rectangle.GetOutlineColor() == 0xFF0000);
        REQUIRE(rectangle.GetFillColor() == 0x00FF00);
    }

    SECTION("Check calculations") 
    {
        REQUIRE(rectangle.GetArea() == Approx(30.7 * 40.4));
        REQUIRE(rectangle.GetPerimeter() == Approx(2 * (30.7 + 40.4)));
    }
}

TEST_CASE("Create triangle and get max area and min perimeter") 
{

    vector<unique_ptr<IShape>> shapes;
    CPoint point1(10.3, 20.15);
    CPoint point2(14.3, 30.15);
    CPoint point3(40.3, 20.15);
    CTriangle triangle(point1, point2, point3, 0Xff0000, 0x00ff00);

    SECTION("Check properties") 
    {
        REQUIRE(triangle.GetVertex1().GetX() == 10.3);
        REQUIRE(triangle.GetVertex1().GetY() == 20.15);
        REQUIRE(triangle.GetVertex2().GetX() == 14.3);
        REQUIRE(triangle.GetVertex2().GetY() == 30.15);
        REQUIRE(triangle.GetVertex3().GetX() == 40.3);
        REQUIRE(triangle.GetVertex3().GetY() == 20.15);

        REQUIRE(triangle.GetOutlineColor() == 0xFF0000);
        REQUIRE(triangle.GetFillColor() == 0x00FF00);
    }

    SECTION("Check calculations") 
    {
        double x1 = 10.3, y1 = 20.15;
        double x2 = 14.3, y2 = 30.15;
        double x3 = 40.3, y3 = 20.15;

        double expectedArea = 0.5 * std::abs(
            x1 * (y2 - y3) +
            x2 * (y3 - y1) +
            x3 * (y1 - y2)
        );

        REQUIRE(triangle.GetArea() == Approx(expectedArea));

        // Проверка периметра
        double side1 = std::hypot(14.3 - 10.3, 30.15 - 20.15);
        double side2 = std::hypot(40.3 - 14.3, 20.15 - 30.15);
        double side3 = std::hypot(10.3 - 40.3, 20.15 - 20.15);
        REQUIRE(triangle.GetPerimeter() == Approx(side1 + side2 + side3));
    }
}

TEST_CASE("Create circle and check properties")
{
    vector<unique_ptr<IShape>> shapes;
    CPoint center(10.0, 20.0);
    CCircle circle(center, 5.0, 0xFF0000, 0x00FF00);

    SECTION("Check properties")
    {
        REQUIRE(circle.GetCenter().GetX() == Approx(10.0));
        REQUIRE(circle.GetCenter().GetY() == Approx(20.0));
        REQUIRE(circle.GetRadius() == Approx(5.0));
        REQUIRE(circle.GetOutlineColor() == 0xFF0000);
        REQUIRE(circle.GetFillColor() == 0x00FF00);
    }

    SECTION("Check calculations")
    {
        double expectedArea = 3.14 * 5.0 * 5.0;
        REQUIRE(circle.GetArea() == Approx(expectedArea));

        double expectedPerimeter = 2 * 3.14 * 5.0;
        REQUIRE(circle.GetPerimeter() == Approx(expectedPerimeter));
    }
}

TEST_CASE("Create line segment and check properties")
{
    vector<unique_ptr<IShape>> shapes;
    CPoint start(10.0, 20.0);
    CPoint end(40.0, 50.0);
    CLineSegment line(start, end, 0xFF0000);

    SECTION("Check properties")
    {
        REQUIRE(line.GetStartPoint().GetX() == Approx(10.0));
        REQUIRE(line.GetStartPoint().GetY() == Approx(20.0));
        REQUIRE(line.GetEndPoint().GetX() == Approx(40.0));
        REQUIRE(line.GetEndPoint().GetY() == Approx(50.0));
        REQUIRE(line.GetOutlineColor() == 0xFF0000);
    }

    SECTION("Check calculations")
    {
        REQUIRE(line.GetArea() == Approx(0.0));

        double expectedLength = std::hypot(40.0 - 10.0, 50.0 - 20.0);
        REQUIRE(line.GetPerimeter() == Approx(expectedLength));
    }
}

TEST_CASE("Create shapes and find max area and min perimeter")
{
    vector<unique_ptr<IShape>> shapes;
    CPoint point1(10.3, 20.15);
    CPoint point2(14.3, 30.15);
    CPoint point3(40.3, 20.15);
    
    CPoint leftTop(10.3, 20.15);
    unique_ptr<IShape> rectangle = make_unique<CRectangle>(leftTop, 30.7, 40.4, 0Xff0000, 0x00ff00);
    shapes.push_back(std::move(rectangle));
    
    CPoint center(10.0, 20.0);
    unique_ptr<IShape> circle = make_unique<CCircle>(center, 5.0, 0xFF0000, 0x00FF00);
    shapes.push_back(std::move(circle));

    CPoint start(10.0, 20.0);
    CPoint end(40.0, 50.0);
    unique_ptr<IShape> line = make_unique<CLineSegment>(start, end, 0xFF0000);
    shapes.push_back(std::move(line));

    auto* maxAreaShape = FindMaxArea(shapes);
    REQUIRE(maxAreaShape->GetArea() == Approx(30.7 * 40.4));   
}

TEST_CASE("CreateShape with invalid input")
{
    SECTION("Unknown shape type") {
        std::string input = "hexagon 1 2 3 4 5 6";
        REQUIRE_THROWS_AS(
            CreateShape(input),
            std::runtime_error, "Неизвестная фигура"
        );
    }

    SECTION("Empty input") {
        REQUIRE_THROWS_AS(
            CreateShape(""),
            std::runtime_error, "Empty input"
        );
    }

    SECTION("Uncorrect object's data (uncorrect point)") 
    {
        std::string input = "rectangle a b";
        REQUIRE(CreateShape(input) == nullptr);
    }

}