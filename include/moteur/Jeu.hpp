/**
 * @file   Jeu.hpp
 * @author Bastien Brunnenstein
 */

#ifndef _JEU_HPP_
#define _JEU_HPP_

#include <SFML/Graphics.hpp>

#include "Monde.hpp"
#include "Sauvegarde.hpp"

/**
 * @brief
 */
class Jeu : public sf::Drawable
{
private:
    Jeu();                                  //!< Constructeur private car c'est un singleton

    sf::RenderWindow    _fenetre;

    Monde **            _mondes;
    Monde *             _monde_courant;

    Sauvegarde          _sauvegarde;

    sf::Texture         _flammes_texture;   //!< Texture des flammes
    sf::Sprite          _flammes_coin;      //!< Sprite de flamme qui fait un coin
    sf::Sprite          _flammes_bord;      //!< Sprite de flamme qui fait un bord
    sf::Sprite          _flammes_jointure;  //!< Sprite de flamme qui fait une jointure
    sf::Sprite          _flammes_plein;     //!< Sprite de flamme qui est plein

    static Jeu          s_jeu;              //!< Singleton

public:
    virtual             ~Jeu();

    static Jeu &        instance();

    const sf::Texture * get_texture(unsigned id) const;

    // Fonction d'affichage de Drawable
    virtual void        draw(sf::RenderTarget & target, sf::RenderStates states) const;

    virtual void        mise_a_jour();

};
// class Jeu

#endif // _JEU_HPP_
