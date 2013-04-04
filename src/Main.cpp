/**
 * @file   Main.cpp
 * @author Bastien Brunnenstein
 * @author Pascal-Pierre Sanchez-Carrion
 */

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <ctime>
#include <cstdlib>

#include <Config.hpp>
#include <moteur/Jeu.hpp>

int main(int argc, char ** argv)
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32), WINDOW_NAME, sf::Style::Default, sf::ContextSettings(32));
    window.setFramerateLimit(WINDOW_FRAMERATE);

    sf::Font font;
    font.loadFromFile("C:/Windows/Fonts/arial.ttf");

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

        window.clear(FIRE_DEFAULT_COLOR);

        /*Jeu::instance().mise_a_jour();

        window.draw(Jeu::instance());*/

        sf::Text text(WINDOW_NAME, font);

        text.setPosition(20, 20);
        text.setColor(sf::Color::Blue);

        window.draw(text);

        window.display();
    }

    return EXIT_SUCCESS;
}
