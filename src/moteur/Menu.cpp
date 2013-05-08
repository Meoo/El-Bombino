/*
 * Menu.cpp
 *
 *  Created on: 7 mai 2013
 *      Author: Sanpas
 */


#include <moteur/Menu.hpp>
#include <moteur/Jeu.hpp>

#include <Config.hpp>

#include <cmath>
#include <ctime>
#include <cstdlib>

#include <SFML/Graphics.hpp>

Menu::Menu(): _menu_principal(true), _menu_config(false), _menu_pause(false), _pause_frame(0)
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

    //
    // MENU PAUSE
    //
    texte_pause = sf::Text("PAUSE", Jeu::instance().get_default_font());
    texte_pause.setCharacterSize(128);
    texte_pause.setColor(sf::Color::White);
    texte_pause.setOrigin(texte_pause.getLocalBounds().width / 2, texte_pause.getLocalBounds().height / 2);
    texte_pause.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);

    texte_pause_fond = sf::Text(texte_pause);
    texte_pause_fond.move(4, 4);
    texte_pause_fond.setColor(sf::Color::Black);
    texte_pause_fond.setStyle(sf::Text::Bold);

    fond_pause = sf::RectangleShape(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    fond_pause.setFillColor(sf::Color(0, 0, 0, 128));
}

Menu::~Menu()
{
}

void Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    sf::Sprite sp_fond(fond_menu_picture);

    if(_menu_principal)
    {
        target.draw(sp_fond);
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
        target.draw(sp_fond);
        target.draw(_fond_mc_retour);
        target.draw(_menu_config_retour);
    }
    else if (_menu_pause)
    {
        target.draw(fond_pause);

        target.draw(texte_pause_fond);
        target.draw(texte_pause);
    }
}

void Menu::mise_a_jour()
{
    if(_menu_pause)
    {
        float a = std::sin(_pause_frame++ * 0.015f) * 3.f;
        texte_pause.setRotation(a);
        texte_pause_fond.setRotation(a);
    }
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
            _pause_frame = 0;
            active_menu(Menu::AUCUN_MENU);
        }
        else if (_fond_mp_config.getGlobalBounds().contains(x,y))
        {
            active_menu(Menu::MENU_CONFIGURATION);
        }
        else if (_fond_mp_play.getGlobalBounds().contains(x,y))
        {
            Jeu::instance().set_monde_courant(0);
            Jeu::instance().get_monde_courant().set_niveau_courant(0);
            _pause_frame = 0;
            active_menu(Menu::AUCUN_MENU);
        }
        else if (_fond_mp_quitter.getGlobalBounds().contains(x,y))
        {

        }
    }
    else if (_menu_config)
    {
        if(_fond_mc_retour.getGlobalBounds().contains(x,y))
        {
            active_menu(Menu::MENU_PRINCIPAL);
        }
    }
    else if (_menu_pause)
    {

    }
}


void Menu::lost_focus()
{
    if(!_menu_config && !_menu_principal)
    {
        active_menu(Menu::MENU_PAUSE);
    }
}

void Menu::press_pause()
{
    if(!_menu_config && !_menu_principal && !_menu_pause)
    {
        active_menu(Menu::MENU_PAUSE);
    }
    else if (!_menu_config &&  !_menu_principal && _menu_pause)
    {
        active_menu(Menu::AUCUN_MENU);
    }
}

Menu::menu_type Menu::get_menu_type()
{
    if(_menu_principal)return Menu::MENU_PRINCIPAL;
    else if (_menu_config)return Menu::MENU_CONFIGURATION;
    else if (_menu_pause)return Menu::MENU_PAUSE;
    else return Menu::AUCUN_MENU;
}

void Menu::active_menu(Menu::menu_type type)
{
    switch (type) {
        case MENU_CONFIGURATION:
            _menu_config = true;
            _menu_pause = false;
            _menu_principal = false;
            break;
        case MENU_PRINCIPAL:
            _menu_config = false;
            _menu_pause = false;
            _menu_principal = true;
            break;
        case MENU_PAUSE:
            _menu_config = false;
            _menu_principal = false;
            _menu_pause = true;
            break;
        case AUCUN_MENU:
            _menu_config = false;
            _menu_pause = false;
            _menu_principal = false;
            break;
        default:
            break;
    }
}
