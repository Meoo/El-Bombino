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
private:
    bool    _menu_principal;
    bool    _menu_config;


    sf::Text _menu_principal_play;
    sf::Text _menu_principal_charger;
    sf::Text _menu_principal_config;
    sf::Text _menu_principal_quitter;

    sf::Text _menu_config_retour;

    sf::RectangleShape _fond_mp_play;
    sf::RectangleShape _fond_mp_charger;
    sf::RectangleShape _fond_mp_config;
    sf::RectangleShape _fond_mp_quitter;

    sf::RectangleShape _fond_mc_retour;

    sf::Texture fond_menu_picture;
public:
                    Menu();
    virtual         ~Menu();

    virtual void    draw(sf::RenderTarget& target, sf::RenderStates states) const;

    virtual void    mise_a_jour();

    void            clic(int x, int y);

    bool                est_actif();
};


#endif /* MENU_HPP_ */
