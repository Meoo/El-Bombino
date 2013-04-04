/**
 * @file   Objet.hpp
 * @author Bastien Brunnenstein
 */

#ifndef _OBJET_HPP_
#define _OBJET_HPP_

#include "../Config.hpp"

#include <SFML/Graphics.hpp>

class Case;

/**
 * @brief
 */
class Objet : public sf::Drawable
{
private:
    const Case *    _case;

public:
    Objet();
    virtual ~Objet();

    // Fonction d'affichage de Drawable
    virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const = 0;

    virtual void mise_a_jour();

};
// class Objet

#endif // _OBJET_HPP_
