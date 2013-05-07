/*
 * Menu.cpp
 *
 *  Created on: 7 mai 2013
 *      Author: Sanpas
 */


#include <moteur/Menu.hpp>
#include <moteur/Jeu.hpp>

#include <Config.hpp>

#include <SFML/Graphics.hpp>

Menu::Menu(): _menu_principal(true), _menu_config(false)
{
    //
    // MENU PRINCIPAL
    //
    _menu_principal_play = sf::Text("NOUVELLE PARTIE",Jeu::instance().get_default_font());
    _menu_principal_play.setCharacterSize(32);
    _menu_principal_play.setColor(sf::Color::Black);
    _menu_principal_play.setOrigin(_menu_principal_play.getLocalBounds().width / 2, _menu_principal_play.getLocalBounds().height / 2);
    _menu_principal_play.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT * 2/ 8);

    _menu_principal_charger = sf::Text("CHARGER PARTIE", Jeu::instance().get_default_font());
    _menu_principal_charger.setCharacterSize(32);
    _menu_principal_charger.setColor(sf::Color::Black);
    _menu_principal_charger.setOrigin(_menu_principal_charger.getLocalBounds().width / 2, _menu_principal_charger.getLocalBounds().height / 2);
    _menu_principal_charger.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT * 3/ 8);

    _menu_principal_config = sf::Text("CONFIGURATION",Jeu::instance().get_default_font());
    _menu_principal_config.setCharacterSize(32);
    _menu_principal_config.setColor(sf::Color::Black);
    _menu_principal_config.setOrigin(_menu_principal_config.getLocalBounds().width / 2, _menu_principal_config.getLocalBounds().height / 2);
    _menu_principal_config.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT * 4/ 8);


    _menu_principal_quitter = sf::Text("QUITTER", Jeu::instance().get_default_font());
    _menu_principal_quitter.setCharacterSize(32);
    _menu_principal_quitter.setColor(sf::Color::Black);
    _menu_principal_quitter.setOrigin(_menu_principal_quitter.getLocalBounds().width / 2, _menu_principal_quitter.getLocalBounds().height / 2);
    _menu_principal_quitter.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT * 5/ 8);

    _fond_mp_play = sf::RectangleShape(sf::Vector2f(_menu_principal_play.getLocalBounds().width, _menu_principal_play.getGlobalBounds().height * 2));
    _fond_mp_play.setOrigin(_menu_principal_play.getOrigin());
    _fond_mp_play.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT * 2/ 8);
    _fond_mp_play.setFillColor(sf::Color::White);

    _fond_mp_charger = sf::RectangleShape(sf::Vector2f(_menu_principal_charger.getLocalBounds().width, _menu_principal_charger.getLocalBounds().height * 2));
    _fond_mp_charger.setOrigin(_menu_principal_charger.getLocalBounds().width / 2, _menu_principal_charger.getLocalBounds().height / 2);
    _fond_mp_charger.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT * 3/ 8);
    _fond_mp_charger.setFillColor(sf::Color::White);

    _fond_mp_config = sf::RectangleShape(sf::Vector2f(_menu_principal_config.getLocalBounds().width, _menu_principal_config.getLocalBounds().height * 2));
    _fond_mp_config.setOrigin(_menu_principal_config.getLocalBounds().width / 2, _menu_principal_config.getLocalBounds().height / 2);
    _fond_mp_config.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT * 4/ 8);
    _fond_mp_config.setFillColor(sf::Color::White);

    _fond_mp_quitter = sf::RectangleShape(sf::Vector2f(_menu_principal_quitter.getLocalBounds().width, _menu_principal_quitter.getLocalBounds().height * 2));
    _fond_mp_quitter.setOrigin(_menu_principal_quitter.getLocalBounds().width / 2, _menu_principal_quitter.getLocalBounds().height / 2);
    _fond_mp_quitter.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT * 5/ 8);
    _fond_mp_quitter.setFillColor(sf::Color::White);

    //
    // MENU CONFIGURATION
    //
    _menu_config_retour = sf::Text("RETOUR", Jeu::instance().get_default_font());
    _menu_config_retour.setCharacterSize(32);
    _menu_config_retour.setColor(sf::Color::Black);
    _menu_config_retour.setOrigin(_menu_config_retour.getLocalBounds().width / 2, _menu_config_retour.getLocalBounds().height / 2);
    _menu_config_retour.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT * 5/ 8);

    _fond_mc_retour = sf::RectangleShape(sf::Vector2f(_menu_config_retour.getLocalBounds().width, _menu_config_retour.getGlobalBounds().height * 2));
    _fond_mc_retour.setOrigin(_menu_config_retour.getOrigin());
    _fond_mc_retour.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT * 5/ 8);
    _fond_mc_retour.setFillColor(sf::Color::White);


    fond_menu_picture.loadFromFile(RC_FOLDER + RC_FONDMENU);
}

Menu::~Menu()
{
}

void Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

    sf::Sprite sp_fond(fond_menu_picture);
    target.draw(sp_fond);

    if(_menu_principal)
    {
        target.draw(_fond_mp_play);
        target.draw(_menu_principal_play);
        target.draw(_fond_mp_charger);
        target.draw(_menu_principal_charger);
        target.draw(_fond_mp_config);
        target.draw(_menu_principal_config);
        target.draw(_fond_mp_quitter);
        target.draw(_menu_principal_quitter);
    }
    else if (_menu_config)
    {
        target.draw(_fond_mc_retour);
        target.draw(_menu_config_retour);
    }
}

void Menu::mise_a_jour()
{

}

void Menu::clic(int x, int y)
{
    if(_menu_principal)
    {
        if(_fond_mp_charger.getGlobalBounds().contains(x,y))
        {
            //new Sauvegarde();
            Jeu::instance().set_monde_courant(0);
            Jeu::instance().get_monde_courant().set_niveau_courant(1);
            _menu_config = false;
            _menu_principal = false;
            Jeu::instance().set_menu(NULL);
        }
        else if (_fond_mp_config.getGlobalBounds().contains(x,y))
        {
            _menu_principal = false;
            _menu_config = true;
        }
        else if (_fond_mp_play.getGlobalBounds().contains(x,y))
        {
            Jeu::instance().set_monde_courant(0);
            Jeu::instance().get_monde_courant().set_niveau_courant(0);
            _menu_config = false;
            _menu_principal = false;
            Jeu::instance().set_menu(NULL);
        }
        else if (_fond_mp_quitter.getGlobalBounds().contains(x,y))
        {

        }
    }
    else if (_menu_config)
    {
        if(_fond_mc_retour.getGlobalBounds().contains(x,y))
        {
            _menu_config = false;
            _menu_principal = true;
        }
    }
}

bool Menu::est_actif()
{
    return _menu_config || _menu_principal;
}
