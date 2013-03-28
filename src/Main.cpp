
#include <SFML/Window.hpp>

/**
 * @brief Point d'entrée du programme
 */
int main(int argc, char ** argv)
{
    sf::Window window(sf::VideoMode(640, 480, 32), "El-Bombino", sf::Style::Default, sf::ContextSettings(32));

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
                window.close();
        }



        window.display();
    }

    return EXIT_SUCCESS;
}
