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
    srand(time(NULL));

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32), WINDOW_NAME, sf::Style::Default, sf::ContextSettings(32));
    window.setFramerateLimit(WINDOW_FRAMERATE);

    Jeu::instance().charger();

    Jeu::instance().set_monde_courant(0);
    Jeu::instance().get_monde_courant().set_niveau_courant(1);

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

#ifndef NDEBUG
            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::F1))
            {
                Jeu::instance().liberer();
                Jeu::instance().charger();
                Jeu::instance().set_monde_courant(0);
                Jeu::instance().get_monde_courant().set_niveau_courant(0);
            }
#endif
        }

        window.clear(sf::Color::Black);

        Jeu::instance().mise_a_jour();

        window.draw(Jeu::instance());

        window.setView(sf::View(sf::FloatRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT)));

        sf::Text text(WINDOW_NAME, font);

        text.setPosition(20, 20);
        text.setColor(sf::Color::Blue);
        window.draw(text);

        window.display();
    }

    return EXIT_SUCCESS;
}
