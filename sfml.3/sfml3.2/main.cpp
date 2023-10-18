#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

struct Eye
{
    sf::ConvexShape eyeBall1;
    sf::ConvexShape eyeBall2;
    sf::ConvexShape pupil1;
    sf::ConvexShape pupil2;
    sf::Vector2f pupil1Pos;
    sf::Vector2f pupil2Pos;
    float pupil1Rotation = 0;
    float pupil2Rotation = 0;
    float rotation = 0;
};

float toDegrees(float radians)
{
    return float(double(radians) * 180.0 / M_PI);
}

sf::Vector2f toEuclidean(float radius, float angle)
{
    return {
        radius * cos(angle),
        radius * sin(angle)};
}

void updateEye(Eye &eye)
{
    const sf::Vector2f pupil1Offset = toEuclidean(30, eye.pupil1Rotation);
    eye.pupil1.setPosition(eye.pupil1Pos + pupil1Offset);
    // eye.pupil1.setRotation(toDegrees(eye.pupil1Rotation));

    const sf::Vector2f pupil2Offset = toEuclidean(30, eye.pupil2Rotation);
    eye.pupil2.setPosition(eye.pupil2Pos + pupil2Offset);
    // eye.pupil2.setRotation(toDegrees(eye.pupil2Rotation));
}

void initEyeElement(sf::ConvexShape &eyeElement, sf::Vector2f &ellipsRadius, sf::Vector2f &position, sf::Color &color)
{
    constexpr int pointCount = 200;
    eyeElement.setPosition(position);
    eyeElement.setFillColor(color);

    eyeElement.setPointCount(pointCount);
    for (int pointNo = 0; pointNo < pointCount; ++pointNo)
    {
        float angle = float(2 * M_PI * pointNo) / float(pointCount);
        sf::Vector2f point = {
            ellipsRadius.x * std::sin(angle),
            ellipsRadius.y * std::cos(angle)};
        eyeElement.setPoint(pointNo, point);
    }
}

void initEye(Eye &eye)
{
    sf::Vector2f eyeBallRadius = {60.f, 120.f};
    sf::Vector2f pupilRadius = {15.f, 30.f};
    sf::Color eyeBallColor = {0xFF, 0xFF, 0xFF};
    sf::Color pupilColor = {0x00, 0x00, 0x00};

    sf::Vector2f eyeBall1Position = {330.f, 300.f};
    initEyeElement(eye.eyeBall1, eyeBallRadius, eyeBall1Position, eyeBallColor);

    sf::Vector2f eyeBall2Position = {480.f, 300.f};
    initEyeElement(eye.eyeBall2, eyeBallRadius, eyeBall2Position, eyeBallColor);

    eye.pupil1Pos = {330.f, 300.f};
    initEyeElement(eye.pupil1, pupilRadius, eye.pupil1Pos, pupilColor);
    eye.pupil1.setOrigin({0, 0});

    eye.pupil2Pos = {480.f, 300.f};
    initEyeElement(eye.pupil2, pupilRadius, eye.pupil2Pos, pupilColor);
    eye.pupil2.setOrigin({0, 0});

    updateEye(eye);
}

void onMouseMove(const sf::Event::MouseMoveEvent &event, sf::Vector2f &mousePosition)
{
    mousePosition = {float(event.x), float(event.y)};
}

void pollEvent(sf::RenderWindow &window, sf::Vector2f &mousePosition)
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

void update(const sf::Vector2f &mousePosition, Eye &eye)
{
    const sf::Vector2f delta1 = mousePosition - eye.pupil1Pos;
    eye.pupil1Rotation = atan2(delta1.y, delta1.x);
    const sf::Vector2f delta2 = mousePosition - eye.pupil2Pos;
    eye.pupil2Rotation = atan2(delta2.y, delta2.x);

    updateEye(eye);
}

void redrawFrame(sf::RenderWindow &window, Eye &eye)
{
    window.clear();
    window.draw(eye.eyeBall1);
    window.draw(eye.eyeBall2);
    window.draw(eye.pupil1);
    window.draw(eye.pupil2);
    window.display();
}

int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
        "Tracking eyes", sf::Style::Default, settings);

    Eye eye;
    sf::Vector2f mousePosition;

    initEye(eye);
    while (window.isOpen())
    {
        pollEvent(window, mousePosition);
        update(mousePosition, eye);
        redrawFrame(window, eye);
    }
}