/**
 * @file   MobileIA.hpp
 * @author Bastien Brunnenstein
 * @author Pascal-Pierre Sanchez-Carrion
 */

#ifndef _MOBILEIA_HPP_
#define _MOBILEIA_HPP_

#include "Mobile.hpp"

#include <SFML/Graphics.hpp>

/**
 * @brief
 */
class MobileIA : public Mobile
{
    unsigned            _vies;
    const sf::Texture & _texture;
    sf::Sprite          _sprite;

    unsigned            _protection;
    mutable bool        _clignote;

public:
                        MobileIA(Case * cse, float vitesse, unsigned vies, const sf::Texture & texture);
    virtual             ~MobileIA();

    // Fonction d'affichage de Drawable
    virtual void        draw(sf::RenderTarget & target, sf::RenderStates states) const;

    virtual void        mise_a_jour();
    virtual void        mise_a_jour_ia() = 0;

    virtual void        blesser();

};
// class Mobile

#endif // _MOBILEIA_HPP_
