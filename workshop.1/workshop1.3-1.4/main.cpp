#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

void onMousePress(const sf::Event::MouseButtonEvent &event, sf::Vector2f &mousePosition, sf::Sprite &pointer)
{
    mousePosition = {float(event.x),
                     float(event.y)};
    pointer.setPosition(mousePosition);
}

void pollEvents(sf::RenderWindow &window, sf::Vector2f &mousePosition, sf::Sprite &pointer)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::MouseButtonPressed:
            onMousePress(event.mouseButton, mousePosition, pointer);
            break;
        defaut:
            break;
        }
    }
}

void update(const sf::Vector2f &mousePosition, sf::Clock &clock, sf::Sprite &cat, sf::Sprite &pointer)
{
    const float dt = clock.restart().asSeconds();
    const float speed = 100;
    const float oneFrameWay = speed * dt;

    sf::Vector2f catPosition = cat.getPosition();
    const sf::Vector2f pointerPosition = pointer.getPosition();

    const sf::Vector2f motion = pointerPosition - catPosition;
    sf::Vector2f direction;

    if (((motion.x <= 0.5) && (motion.x >= -0.5)) || ((motion.y <= 0.5) && (motion.y >= -0.5)))
    {
        direction = {0, 0};
    }
    else
    {
        direction = {motion.x / sqrt(pow(motion.x, 2) + pow(motion.y, 2)),
                     motion.y / sqrt(pow(motion.x, 2) + pow(motion.y, 2))};
    }

    if (motion.x < 0)
    {
        cat.setScale(-1, 1);
    }
    else
    {
        cat.setScale(1, 1);
    }

    catPosition = catPosition + direction * oneFrameWay;
    cat.setPosition(catPosition);
}

void redrawFrame(sf::RenderWindow &window, sf::Sprite &cat, sf::Sprite &pointer)
{
    window.clear(sf::Color(0xFF, 0xFF, 0xFF));
    window.draw(pointer);
    window.draw(cat);
    window.display();
}

int main()
{
    constexpr unsigned WINDOW_WIDTH = 1000;
    constexpr unsigned WINDOW_HEIGHT = 700;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
        "Drawing cat", sf::Style::Default, settings);

    sf::Vector2f mousePosition;

    sf::Texture pointerTexture;
    pointerTexture.loadFromFile("red_pointer.png");
    sf::Sprite pointer;
    pointer.setTexture(pointerTexture);
    pointer.setPosition(480, 330);
    pointer.setOrigin(16, 16);

    sf::Texture catTexture;
    catTexture.loadFromFile("cat.png");
    sf::Sprite cat;
    cat.setTexture(catTexture);
    cat.setPosition(480, 330);
    cat.setOrigin(19, 18);

    sf::Clock clock;

    while (window.isOpen())
    {
        pollEvents(window, mousePosition, pointer);
        update(mousePosition, clock, cat, pointer);
        redrawFrame(window, cat, pointer);
    }
}