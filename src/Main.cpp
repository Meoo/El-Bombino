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

    // TODO DEBUG Enlever
    Jeu::instance().set_monde_courant(0);
    Jeu::instance().get_monde_courant().set_niveau_courant(1);

    // Variables pour la Pause
    sf::Text texte_pause("PAUSE", Jeu::instance().get_default_font());
    texte_pause.setCharacterSize(128);
    texte_pause.setColor(sf::Color::White);
    texte_pause.setOrigin(texte_pause.getLocalBounds().width / 2, texte_pause.getLocalBounds().height / 2);
    texte_pause.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);

    sf::Text texte_pause_fond(texte_pause);
    texte_pause_fond.move(4, 4);
    texte_pause_fond.setColor(sf::Color::Black);
    texte_pause_fond.setStyle(sf::Text::Bold);

    sf::RectangleShape fond_pause(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    fond_pause.setFillColor(sf::Color(0, 0, 0, 128));

    bool pause = false;
    int pause_frame = 0;

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
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::LostFocus)
                pause = true;

            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
                window.close();

            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Pause))
                pause = !pause;

            // TODO DEBUG Enlever
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

       // TODO DEBUG Enlever
        if(Jeu::instance().get_monde_courant().get_niveau_courant().get_joueur()==NULL){
            Jeu::instance().liberer();
            Jeu::instance().charger();
            Jeu::instance().set_monde_courant(0);
            Jeu::instance().get_monde_courant().set_niveau_courant(1);
        }
        //test de la liste de pnjs
        /** /
        if(Jeu::instance().get_monde_courant().get_niveau_courant().get_pnjs().empty()){
                    Jeu::instance().liberer();
                    Jeu::instance().charger();
                    Jeu::instance().set_monde_courant(0);
                    Jeu::instance().get_monde_courant().set_niveau_courant(1);
        }
        / **/

        window.clear(sf::Color::Black);

        if (!pause)
        {
            Jeu::instance().mise_a_jour();
        }

        window.draw(Jeu::instance());

        window.setView(sf::View(sf::FloatRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT)));

        if (pause)
        {
            window.draw(fond_pause);

            float a = std::sin(pause_frame++ * 0.015f) * 3.f;
            texte_pause.setRotation(a);
            texte_pause_fond.setRotation(a);

            window.draw(texte_pause_fond);
            window.draw(texte_pause);
        }

        window.display();
    }

    return EXIT_SUCCESS;
}
