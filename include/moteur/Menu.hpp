/*
 * Menu.hpp
 *
 *  Created on: 7 mai 2013
 *      Author: Sanpas
 */

#ifndef MENU_HPP_
#define MENU_HPP_

#include <SFML/Graphics.hpp>

class Menu : public sf::Drawable
{
public:
    enum menu_type {
        MENU_PRINCIPAL,
        MENU_CONFIGURATION,
        MENU_PAUSE,
        NIVEAU_SUIVANT,
        MONDE_SUIVANT,
        GAME_OVER,
        JEU_FINI,
        AUCUN_MENU,
    };
private:

    menu_type   _menu_type;

    sf::Text _menu_principal_play;
    sf::Text _menu_principal_charger;
    sf::Text _menu_principal_config;
    sf::Text _menu_principal_quitter;

    sf::Text _menu_config_retour;

    sf::RectangleShape  _fond_mp_play;
    sf::RectangleShape  _fond_mp_charger;
    sf::RectangleShape  _fond_mp_config;
    sf::RectangleShape  _fond_mp_quitter;

    sf::RectangleShape  _fond_mc_retour;

    sf::Texture         fond_menu_picture;


    //MENU PAUSE
    sf::Text            _texte_pause;
    sf::Text            _texte_pause_fond;
    sf::RectangleShape  _fond_pause;
    int                 _pause_frame;

    sf::Text _niveau_suivant;
    sf::RectangleShape  _niveau_suivant_fond;

    sf::Text _monde_suivant;
    sf::RectangleShape  _monde_suivant_fond;

    sf::Text _game_over;
    sf::RectangleShape  _game_over_fond;

    sf::Text _fin_jeu;
    sf::RectangleShape  _fin_jeu_fond;
public:
                    Menu();
    virtual         ~Menu();

    virtual void    draw(sf::RenderTarget& target, sf::RenderStates states) const;

    virtual void    mise_a_jour();

    void            clic(int x, int y);

    void            lost_focus();

    void            press_pause();

    menu_type       get_menu_type();

    void            active_menu(menu_type type);
};


#endif /* MENU_HPP_ */
