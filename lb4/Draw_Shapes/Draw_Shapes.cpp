#include <SFML\Graphics.hpp>
#include <fstream>
#include "CCanvas.h"
#include "../Shapes/IShape.h"
#include <iostream>
#include <memory>
#include <vector>
#include "../Shapes/Create_Shapes.h"

std::vector<std::unique_ptr<IShape>> LoadShapesFromFile(const std::string& filename) 
{
    std::vector<std::unique_ptr<IShape>> shapes;
    std::ifstream inputFile(filename);

    if (!inputFile.is_open()) 
    {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return shapes;
    }

    std::string line;
    while (std::getline(inputFile, line)) 
    {
        try 
        {
            auto shape = CreateShape(line);
            if (shape) 
            {
                shapes.push_back(std::move(shape));
            }
        }
        catch (const std::exception& e) 
        {
            std::cerr << "Error parsing shape: " << e.what() << std::endl;
        }
    }
    return shapes;
}

int main()
{
    // Проверяем аргументы командной строки
    std::cout << "Enter filename with shapes: ";
    std::string fileName;
    std::cin >> fileName;

    auto shapes = LoadShapesFromFile(fileName);
    for (size_t i = 0; i < shapes.size(); ++i) 
    {
        std::cout << i + 1 << ". " << shapes[i]->ToString()
            << ", Area: " << shapes[i]->GetArea()
            << ", Perimeter: " << shapes[i]->GetPerimeter() << ", Color: ";
    }

    if (shapes.empty())
    {
        std::cerr << "No shapes loaded or file is empty." << std::endl;
        return 1;
    }

    sf::RenderWindow window(sf::VideoMode(800, 600), "Shapes Drawing");
    CCanvas canvas(window);

    while (window.isOpen()) 
    {
        sf::Event event;
        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color(255, 255, 255));

        for (auto it = shapes.rbegin(); it != shapes.rend(); ++it) 
        {
            (*it)->Draw(canvas);
        }
        window.display();
    }
    return 0;
}