#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <cmath>

constexpr unsigned WINDOW_WIDTH = 1000;
constexpr unsigned WINDOW_HEIGHT = 1000;

int main()
{
    constexpr int pointCount = 200;
    float deltaRotationAgile = 0.2;
    float rotationAgile = 0.2;
    float roadRadius = 200;
    float roadAgile = 0.5;
    float deltaRoadAgile = 0.5;
    sf::Vector2f position = {450.f, 450.f};

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Rose",
        sf::Style::Default, settings);

    sf::ConvexShape rose;
    rose.setPosition({400, 320});
    rose.setFillColor(sf::Color(0xFF, 0x09, 0x80));

    rose.setPointCount(pointCount);

    for (int pointNo = 0; pointNo < pointCount; ++pointNo)
    {
        float angle = float(2 * M_PI * pointNo) / float(pointCount);
        float roseRadius = float(200) * float(sin(float(6 * angle)));
        sf::Vector2f point = sf::Vector2f{
            roseRadius * std::sin(angle),
            roseRadius * std::cos(angle)};
        rose.setPoint(pointNo, point);
    }

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        float x = position.x + round(roadRadius * cos(roadAgile * M_PI / 180));
        float y = position.y + round(roadRadius * sin(roadAgile * M_PI / 180));
        rose.setPosition({x, y});
        roadAgile += deltaRoadAgile;
        rose.setRotation(rotationAgile);
        rotationAgile += deltaRotationAgile;

        window.clear();
        window.draw(rose);
        window.display();
    }
}