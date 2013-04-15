/**
 * @file   Joueur.hpp
 * @author Bastien Brunnenstein
 * @author Pascal-Pierre Sanchez-Carrion
 */

#ifndef _JOUEUR_HPP_
#define _JOUEUR_HPP_

#include "Mobile.hpp"

/**
 * @brief
 */
class Joueur : public Mobile
{
private:
    sf::Sprite          _sprite;

public:
                        Joueur(Case * cse);
    virtual             ~Joueur();

    // Fonction d'affichage de Drawable
    virtual void        draw(sf::RenderTarget & target, sf::RenderStates states) const;

    virtual void        mise_a_jour();

};
// class Joueur

#endif // _JOUEUR_HPP_
