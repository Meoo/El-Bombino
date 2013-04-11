/**
 * @file   Objet.hpp
 * @author Bastien Brunnenstein
 */

#ifndef _OBJET_HPP_
#define _OBJET_HPP_

#include "../Config.hpp"

#include <SFML/Graphics.hpp>

class Case;
class Soulevable;

/**
 * @brief
 */
class Objet : public sf::Drawable
{
    friend class Soulevable;

private:
    Case *          _case;

                    Objet();
public:
                    Objet(Case * cse);
    virtual         ~Objet();

    virtual Case *  get_case();
    virtual const Case * get_case() const;
    void            set_case(Case * cse);

    // Fonction d'affichage de Drawable
    virtual void    draw(sf::RenderTarget & target, sf::RenderStates states) const = 0;

    virtual void    mise_a_jour();

};
// class Objet

#endif // _OBJET_HPP_
