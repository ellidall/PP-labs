#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

void init(sf::ConvexShape &arrow)
{
    arrow.setFillColor(sf::Color(0, 0, 0));
    arrow.setPointCount(7);
    arrow.setPoint(0, {40, 0});
    arrow.setPoint(1, {0, -30});
    arrow.setPoint(2, {0, -10});
    arrow.setPoint(3, {-40, -10});
    arrow.setPoint(4, {-40, 10});
    arrow.setPoint(5, {0, 10});
    arrow.setPoint(6, {0, 30});
    arrow.setPosition({400, 300});
    arrow.setOutlineColor(sf::Color(100, 0, 100));
    arrow.setOutlineThickness(5);
}

float toDegrees(float radians)
{
    return float(double(radians) * 180.0 / M_PI);
}

void onMouseMove(const sf::Event::MouseMoveEvent &event, sf::Vector2f &mousePosition)
{
    mousePosition = {float(event.x), float(event.y)};
}

void pollEvents(sf::RenderWindow &window, sf::Vector2f &mousePosition)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::MouseMoved:
            onMouseMove(event.mouseMove, mousePosition);
            break;
        default:
            break;
        }
    }
}

void updateRotation(sf::Vector2f mousePosition, sf::ConvexShape &arrow)
{
    const sf::Vector2f delta = mousePosition - arrow.getPosition();
    const float angle = atan2(delta.y, delta.x);
    arrow.setRotation(toDegrees(angle));
}

bool updatePosition(sf::Vector2f mousePosition, sf::ConvexShape &arrow, float time)
{
    const int speedPerFrame = 20;
    sf::Vector2f motion = mousePosition - arrow.getPosition();
    const int motionAbs = sqrt(motion.x * motion.x + motion.y * motion.y);
    if (motionAbs >= speedPerFrame)
    {
        motion.x /= motionAbs;
        motion.y /= motionAbs;
        const float speed = speedPerFrame * time;
        const sf::Vector2f position = arrow.getPosition() + motion * speed;
        arrow.setPosition(position);
        return true;
    }
    arrow.setPosition(mousePosition);
    return false;
}

void update(sf::Vector2f mousePosition, sf::ConvexShape &arrow, float time)
{
    if (updatePosition(mousePosition, arrow, time))
        updateRotation(mousePosition, arrow);
}

void redrawFrame(sf::RenderWindow &window, sf::ConvexShape &arrow)
{
    window.clear(sf::Color(0xFF, 0xFF, 0xFF));
    window.draw(arrow);
    window.display();
}

int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;

    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
        "Arrow to mouse", sf::Style::Default);

    sf::Clock clock;
    sf::ConvexShape arrow;
    sf::Vector2f mousePosition;

    init(arrow);

    while (window.isOpen())
    {
        const float time = clock.restart().asSeconds();
        pollEvents(window, mousePosition);
        update(mousePosition, arrow, time);
        redrawFrame(window, arrow);
    }
}