/**
 * @file   Main.cpp
 * @author Bastien Brunnenstein
 * @author Pascal-Pierre Sanchez-Carrion
 */

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <ctime>
#include <cstdlib>

#include <Config.hpp>

#include <moteur/Jeu.hpp>

#ifndef NDEBUG
bool DEBUG_ALGO;
#endif

int main(int argc, char ** argv)
{
    srand(time(NULL));

    Jeu::instance().charger();

    sf::Music mus;
    mus.openFromFile(RC_FOLDER + "musique.ogg");
    mus.setVolume(50.f);
    mus.setLoop(true);
    mus.play();

    unsigned timer_close = 200;

    // Fenêtre
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32), WINDOW_NAME, sf::Style::Default, sf::ContextSettings(32));
    window.setFramerateLimit(WINDOW_FRAMERATE);
    window.setVerticalSyncEnabled(true);

    // Icône de la fenêtre
    {
        sf::Image icon;
        icon.loadFromFile(RC_FOLDER + RC_ICON);
        window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    }

#ifndef NDEBUG
    DEBUG_ALGO = false;
    sf::Clock clock;
    int count = 0;
#endif
    while (window.isOpen())
    {

        //gestion des different evenement
        sf::Event event;
        while (window.pollEvent(event))
        {
            if((event.type == sf::Event::KeyPressed) )
                Jeu::instance().press_touch(event.key);

            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::LostFocus)
                Jeu::instance().lost_focus();

            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
                Jeu::instance().press_pause();

#ifndef NDEBUG
            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::F8))
                DEBUG_ALGO = !DEBUG_ALGO;
#endif

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {
                    Jeu::instance().clic(event.mouseButton.x,event.mouseButton.y);
                }
            }
#ifndef NDBEUG
            if((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::F1))
            {
                int count_monde = Jeu::instance().get_count_mondes();
                int count_niveau = Jeu::instance().get_monde_courant().get_count_niveaux();
                int num_monde = Jeu::instance().get_num_monde_courant();
                int num_niv   = Jeu::instance().get_monde_courant().get_num_niveau_courant();
                if(num_niv + 1 >= count_niveau)
                {
                    if(num_monde + 1 < count_monde)
                    {
                        Jeu::instance().get_monde_courant().get_niveau_courant().liberer();
                        Jeu::instance().get_monde_courant().liberer();
                        Jeu::instance().set_monde_courant(num_monde + 1);
                        Jeu::instance().get_monde_courant().set_niveau_courant(0);
                    }
                }
                else
                {
                    Jeu::instance().get_monde_courant().get_niveau_courant().liberer();
                    Jeu::instance().get_monde_courant().set_niveau_courant(num_niv + 1);
                }
            }
#endif
        }

        //option quitter du menu principal
        if (Jeu::instance().get_menu()->get_menu_type() == Menu::QUITTER)
        {
            if (timer_close == 0)
            {
                //Jeu::instance().liberer();
                window.close();
            }
            else
                --timer_close;
        }


        //affichage du jeu
        window.clear(sf::Color::Black);

        Jeu::instance().mise_a_jour();

        window.draw(Jeu::instance());

        window.display();

#ifndef NDEBUG
        ++count;
        if (clock.getElapsedTime().asMilliseconds() >= 1000)
        {
            window.setTitle(std::string("FPS : ") + nsUtil::convertInt(count));
            clock.restart();
            count = 0;
        }
#endif
    }

    return EXIT_SUCCESS;
}
