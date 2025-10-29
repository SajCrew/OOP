#include "Get_Shape_Info.h"

//завести класс для методов
const IShape* FindMaxArea(const vector<unique_ptr<IShape>>& shapes)
{
    if (shapes.empty()) return nullptr;

    const IShape* maxShape = shapes[0].get();
    for (const auto& shape : shapes)
    {
        if (shape->GetArea() > maxShape->GetArea())
        {
            maxShape = shape.get();
        }
    }
    return maxShape;
}


const IShape* FindMinPerimeter(const vector<unique_ptr<IShape>>& shapes)
{
    if (shapes.empty()) return nullptr;

    const IShape* minShape = shapes[0].get();
    for (const auto& shape : shapes)
    {
        if (shape->GetPerimeter() < minShape->GetPerimeter())
        {
            minShape = shape.get();
        }
    }
    return minShape;
}

void PrintInfo(vector<unique_ptr<IShape>>& shapes)
{
    const IShape* maxAreaShape = FindMaxArea(shapes);
    const IShape* minPerimeterShape = FindMinPerimeter(shapes);

    if (maxAreaShape)
    {
        cout << "Фигура с максимальной площадью:\n";
        cout << maxAreaShape->ToString() << endl;
        cout << "Площадь: " << maxAreaShape->GetArea() << endl;
        cout << "Периметр: " << maxAreaShape->GetPerimeter() << endl;
        cout << "Цвет обводки: #" << hex << setw(6) << setfill('0')
            << maxAreaShape->GetOutlineColor() << dec << endl;

        if (auto solidShape = dynamic_cast<const ISolidShape*>(maxAreaShape))
        {
            cout << "Цвет заливки: #" << hex << setw(6) << setfill('0')
                << solidShape->GetFillColor() << dec << endl;
        }
    }

    if (minPerimeterShape)
    {
        cout << "\nФигура с минимальным периметром:\n";
        cout << minPerimeterShape->ToString() << endl;
        cout << "Площадь: " << minPerimeterShape->GetArea() << endl;
        cout << "Периметр: " << minPerimeterShape->GetPerimeter() << endl;
        cout << "Цвет обводки: #" << hex << setw(6) << setfill('0')
            << minPerimeterShape->GetOutlineColor() << dec << endl;

        if (auto solidShape = dynamic_cast<const ISolidShape*>(minPerimeterShape))
        {
            cout << "Цвет заливки: #" << hex << setw(6) << setfill('0')
                << solidShape->GetFillColor() << dec << endl;
        }
    }
}