#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode({1000, 450}), "Rectangle and Circle");

    window.clear();

    sf::CircleShape B1(75);
    B1.setPosition({700, 100});
    B1.setFillColor(sf::Color{0x0, 0x80, 0x80});
    window.draw(B1);

    sf::CircleShape B2(75);
    B2.setPosition({700, 250});
    B2.setFillColor(sf::Color{0x0, 0x80, 0x80});
    window.draw(B2);

    sf::CircleShape B3(55);
    B3.setPosition({700, 120});
    B3.setFillColor(sf::Color{0x0, 0x0, 0x0});
    window.draw(B3);

    sf::CircleShape B4(55);
    B4.setPosition({700, 270});
    B4.setFillColor(sf::Color{0x0, 0x0, 0x0});
    window.draw(B4);

    sf::RectangleShape B5;
    B5.setSize({40, 300});
    B5.setPosition({700, 100});
    B5.setFillColor(sf::Color{0x0, 0x80, 0x80});
    window.draw(B5);

    sf::RectangleShape A11;
    A11.setSize({40, 300});
    A11.setRotation(20);
    A11.setPosition({200, 100});
    A11.setFillColor(sf::Color{0x0, 0x80, 0x80});
    window.draw(A11);

    sf::RectangleShape A12;
    A12.setSize({40, 300});
    A12.setRotation(-20);
    A12.setPosition({235, 113});
    A12.setFillColor(sf::Color{0x0, 0x80, 0x80});
    window.draw(A12);

    sf::RectangleShape A13;
    A13.setSize({40, 150});
    A13.setRotation(90);
    A13.setPosition({300, 250});
    A13.setFillColor(sf::Color{0x0, 0x80, 0x80});
    window.draw(A13);

    sf::RectangleShape A14;
    A14.setSize({40, 70});
    A14.setRotation(90);
    A14.setPosition({270, 100});
    A14.setFillColor(sf::Color{0x0, 0x80, 0x80});
    window.draw(A14);

    sf::RectangleShape A21;
    A21.setSize({40, 300});
    A21.setRotation(20);
    A21.setPosition({500, 100});
    A21.setFillColor(sf::Color{0x0, 0x80, 0x80});
    window.draw(A21);

    sf::RectangleShape A22;
    A22.setSize({40, 300});
    A22.setRotation(-20);
    A22.setPosition({535, 113});
    A22.setFillColor(sf::Color{0x0, 0x80, 0x80});
    window.draw(A22);

    sf::RectangleShape A23;
    A23.setSize({40, 150});
    A23.setRotation(90);
    A23.setPosition({600, 250});
    A23.setFillColor(sf::Color{0x0, 0x80, 0x80});
    window.draw(A23);

    sf::RectangleShape A24;
    A24.setSize({40, 70});
    A24.setRotation(90);
    A24.setPosition({570, 100});
    A24.setFillColor(sf::Color{0x0, 0x80, 0x80});
    window.draw(A24);

    window.display();

    sf::sleep(sf::seconds(3));
}