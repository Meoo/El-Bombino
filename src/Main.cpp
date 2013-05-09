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

    Jeu::instance().charger();


    unsigned timer_close = 500;

    // Fenêtre
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32), WINDOW_NAME, sf::Style::Default, sf::ContextSettings(32));
    window.setFramerateLimit(WINDOW_FRAMERATE);

    // Icône de la fenêtre
    {
        sf::Image icon;
        icon.loadFromFile(RC_FOLDER + RC_ICON);
        window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    }

    while (window.isOpen())
    {
        //gestion des different evenement
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::LostFocus)
                Jeu::instance().lost_focus();

            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
                window.close();

            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Pause))
                Jeu::instance().press_pause();

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    Jeu::instance().clic(event.mouseButton.x,event.mouseButton.y);
                }
            }

        }

        //option quitter du menu principal
        if (Jeu::instance().get_menu()->get_menu_type() == Menu::QUITTER)
        {
            if (timer_close == 0)
            {
                Jeu::instance().liberer();
                window.close();
            }
            else
                --timer_close;
        }


        //affichage du jeu
        window.clear(sf::Color::Black);

        Jeu::instance().mise_a_jour();
        window.draw(Jeu::instance());

        window.setView(sf::View(sf::FloatRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT)));

        window.display();
    }

    return EXIT_SUCCESS;
}
