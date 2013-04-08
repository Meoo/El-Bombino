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
    Case *          _case;

public:
                    Objet(Case * cse);
    virtual         ~Objet();

    Case *          get_case();
    const Case *    get_case() const;
    void            set_case(Case * cse);

    // Fonction d'affichage de Drawable
    virtual void    draw(sf::RenderTarget & target, sf::RenderStates states) const = 0;

    virtual void    mise_a_jour();

};
// class Objet

#endif // _OBJET_HPP_
