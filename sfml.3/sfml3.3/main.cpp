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

const sf::Vector2f eyeBallRadius = {60.f, 120.f};
const sf::Vector2f pupilRadius = {15.f, 30.f};
const sf::Vector2f eyeBall1Position = {330.f, 300.f};
const sf::Vector2f eyeBall2Position = {480.f, 300.f};

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

float getDistanseToBorder(float rotation, const float &roadRadius)
{
    const sf::Vector2f vector = {
        roadRadius * std::cos(rotation),
        roadRadius * std::sin(rotation)};
    return sqrt(vector.x * vector.x + vector.y * vector.y);
}

float getDictanseToMouse(sf::Vector2f position, const sf::Vector2f &mousePosition)
{
    const sf::Vector2f vectorToMouse = {
        mousePosition.x - position.x,
        mousePosition.y - position.y};
    return sqrt(vectorToMouse.x * vectorToMouse.x + vectorToMouse.y * vectorToMouse.y);
}

void updateEye(Eye &eye, const sf::Vector2f &mousePosition, const float &roadRadius)
{
    if (getDictanseToMouse(eyeBall1Position, mousePosition) < getDistanseToBorder(eye.pupil1Rotation, roadRadius))
    {
        eye.pupil1.setPosition(mousePosition);
    }
    else
    {
        const sf::Vector2f pupil1Offset = toEuclidean(roadRadius, eye.pupil1Rotation);
        eye.pupil1.setPosition(eye.pupil1Pos + pupil1Offset);
    }
    if (getDictanseToMouse(eyeBall2Position, mousePosition) < getDistanseToBorder(eye.pupil2Rotation, roadRadius))
    {
        eye.pupil2.setPosition(mousePosition);
    }
    else
    {
        const sf::Vector2f pupil2Offset = toEuclidean(roadRadius, eye.pupil2Rotation);
        eye.pupil2.setPosition(eye.pupil2Pos + pupil2Offset);
    }
}

void update(const sf::Vector2f &mousePosition, Eye &eye, const float &roadRadius)
{
    const sf::Vector2f delta1 = mousePosition - eye.pupil1Pos;
    eye.pupil1Rotation = atan2(delta1.y, delta1.x);
    const sf::Vector2f delta2 = mousePosition - eye.pupil2Pos;
    eye.pupil2Rotation = atan2(delta2.y, delta2.x);

    updateEye(eye, mousePosition, roadRadius);
}

void initEyeElement(
    sf::ConvexShape &eyeElement,
    const sf::Vector2f &ellipsRadius,
    const sf::Vector2f &position,
    const sf::Color &color)
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
    const sf::Color eyeBallColor = {0xFF, 0xFF, 0xFF};
    const sf::Color pupilColor = {0x00, 0x00, 0xFF};

    initEyeElement(eye.eyeBall1, eyeBallRadius, eyeBall1Position, eyeBallColor);
    initEyeElement(eye.eyeBall2, eyeBallRadius, eyeBall2Position, eyeBallColor);
    eye.pupil1Pos = {330.f, 300.f};
    initEyeElement(eye.pupil1, pupilRadius, eye.pupil1Pos, pupilColor);
    eye.pupil2Pos = {480.f, 300.f};
    initEyeElement(eye.pupil2, pupilRadius, eye.pupil2Pos, pupilColor);
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
    const float roadRadius = 30;

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
        update(mousePosition, eye, roadRadius);
        redrawFrame(window, eye);
    }
}