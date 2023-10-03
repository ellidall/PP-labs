#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <cmath>

constexpr unsigned WINDOW_WIDTH = 800;
constexpr unsigned WINDOW_HEIGHT = 600;

int main()
{
    constexpr float BALL_SIZE = 40;

    sf::RenderWindow window(sf ::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Simple Event Loop");
    sf::Clock clock;
    sf::Clock clockForSin;

    const sf::Vector2f startPosition = {10, 350};
    sf::Vector2f position = startPosition;
    float speedX = 100.f;
    constexpr float amplitudeY = 80.f;
    constexpr float periodY = 2;

    sf::CircleShape ball(BALL_SIZE);
    ball.setFillColor(sf::Color(0xFF, 0xFF, 0xFF));

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

        const float deltaTime = clock.restart().asSeconds();
        position.x += speedX * deltaTime;

        const float time = clockForSin.getElapsedTime().asSeconds();
        const float wavePhase = time * float(2 * M_PI);
        const float y = startPosition.y + amplitudeY * std::sin(wavePhase / periodY);
        position.y = y;

        ball.setPosition(position);

        if (((position.x + 2 * BALL_SIZE >= WINDOW_WIDTH) && (speedX > 0)) || ((position.x < 0) && (speedX < 0)))
        {
            speedX = -speedX;
        }

        window.clear();
        window.draw(ball);
        window.display();
    }
}