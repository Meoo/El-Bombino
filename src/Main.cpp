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

    /*
    // TODO DEBUG Enlever
    Jeu::instance().set_monde_courant(0);
    Jeu::instance().get_monde_courant().set_niveau_courant(1);
    */


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
            // TODO DEBUG Enlever
#ifndef NDEBUG
            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::F1))
            {
                Jeu::instance().liberer();
                Jeu::instance().charger();
                Jeu::instance().set_monde_courant(0);
                Jeu::instance().get_monde_courant().set_niveau_courant(0);
                Jeu::instance().get_menu()->active_menu(Menu::AUCUN_MENU);
            }
#endif
        }

       // TODO DEBUG Enlever
       /* if(Jeu::instance().get_monde_courant().get_niveau_courant().get_joueur()==NULL){
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
        /**/

        window.clear(sf::Color::Black);

        //
        Jeu::instance().mise_a_jour();
        window.draw(Jeu::instance());

        //areter les mise_a_jour du jeu si la pause est active
        /*if(!Jeu::instance().get_pause()->est_active())
        {
            Jeu::instance().mise_a_jour();
        }
        window.draw(Jeu::instance());*/

        window.setView(sf::View(sf::FloatRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT)));

        //affichage de la pause dessus le jeu si elle est active
        /*if (Jeu::instance().get_pause()->est_active())
        {
            Jeu::instance().get_pause()->mise_a_jour();
            window.draw(*Jeu::instance().get_pause());
        }*/

        window.display();
    }

    return EXIT_SUCCESS;
}
