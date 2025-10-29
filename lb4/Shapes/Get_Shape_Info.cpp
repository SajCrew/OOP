#include "Get_Shape_Info.h"

//������� ����� ��� �������
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
        cout << "������ � ������������ ��������:\n";
        cout << maxAreaShape->ToString() << endl;
        cout << "�������: " << maxAreaShape->GetArea() << endl;
        cout << "��������: " << maxAreaShape->GetPerimeter() << endl;
        cout << "���� �������: #" << hex << setw(6) << setfill('0')
            << maxAreaShape->GetOutlineColor() << dec << endl;

        if (auto solidShape = dynamic_cast<const ISolidShape*>(maxAreaShape))
        {
            cout << "���� �������: #" << hex << setw(6) << setfill('0')
                << solidShape->GetFillColor() << dec << endl;
        }
    }

    if (minPerimeterShape)
    {
        cout << "\n������ � ����������� ����������:\n";
        cout << minPerimeterShape->ToString() << endl;
        cout << "�������: " << minPerimeterShape->GetArea() << endl;
        cout << "��������: " << minPerimeterShape->GetPerimeter() << endl;
        cout << "���� �������: #" << hex << setw(6) << setfill('0')
            << minPerimeterShape->GetOutlineColor() << dec << endl;

        if (auto solidShape = dynamic_cast<const ISolidShape*>(minPerimeterShape))
        {
            cout << "���� �������: #" << hex << setw(6) << setfill('0')
                << solidShape->GetFillColor() << dec << endl;
        }
    }
}