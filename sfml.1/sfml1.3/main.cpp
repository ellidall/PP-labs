#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode({800, 700}), "House");

    window.clear();

    sf::RectangleShape carcass;
    carcass.setSize({500, 250});
    carcass.setPosition({50, 400});
    carcass.setFillColor(sf::Color{0x50, 0x3f, 0x0});
    window.draw(carcass);

    sf::RectangleShape door;
    door.setSize({80, 160});
    door.setPosition({100, 490});
    door.setFillColor(sf::Color{0x20, 0x20, 0x20});
    window.draw(door);

    sf::ConvexShape roof;
    roof.setPosition({300, 250});
    roof.setPointCount(4);
    roof.setPoint(0, {-150, 30});
    roof.setPoint(1, {+150, 30});
    roof.setPoint(2, {+300, 150});
    roof.setPoint(3, {-300, 150});
    roof.setFillColor(sf::Color{0x6b, 0x0, 0x0});
    window.draw(roof);

    sf::CircleShape smoke1(25);
    smoke1.setPosition({350, 170});
    smoke1.setFillColor(sf::Color{0x80, 0x80, 0x80});
    window.draw(smoke1);

    sf::CircleShape smoke2(30);
    smoke2.setPosition({365, 130});
    smoke2.setFillColor(sf::Color{0x80, 0x80, 0x80});
    window.draw(smoke2);

    sf::CircleShape smoke3(35);
    smoke3.setPosition({380, 90});
    smoke3.setFillColor(sf::Color{0x80, 0x80, 0x80});
    window.draw(smoke3);

    sf::CircleShape smoke4(40);
    smoke4.setPosition({395, 50});
    smoke4.setFillColor(sf::Color{0x80, 0x80, 0x80});
    window.draw(smoke4);

    sf::RectangleShape flue1;
    flue1.setSize({90, 50});
    flue1.setPosition({330, 210});
    flue1.setFillColor(sf::Color{0x40, 0x40, 0x3b});
    window.draw(flue1);

    sf::RectangleShape flue2;
    flue2.setSize({50, 75});
    flue2.setPosition({350, 250});
    flue2.setFillColor(sf::Color{0x40, 0x40, 0x3b});
    window.draw(flue2);

    window.display();

    sf::sleep(sf::seconds(3));
}