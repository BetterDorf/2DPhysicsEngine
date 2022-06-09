#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>


int main()
{
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "window");

    while (window.isOpen())
    {
        window.clear();

        //Draw stuff

        window.display();
    }

    return EXIT_SUCCESS;
}