/**
 * @file   Monde.hpp
 * @author Bastien Brunnenstein
 */

#ifndef _MONDE_HPP_
#define _MONDE_HPP_

#include <SFML/Graphics.hpp>

#include "Niveau.hpp"

/**
 * @brief
 */
class Monde : public sf::Drawable
{
private:
    Niveau **           _niveaux;
    Niveau *            _niveau_courant;

public:
                        Monde();
    virtual             ~Monde();

    Niveau *            get_niveau_courant();
    const Niveau *      get_niveau_courant() const;

    void                charger();
    void                liberer();

    const sf::Texture * get_texture(unsigned id) const;

    // Fonction d'affichage de Drawable
    virtual void    draw(sf::RenderTarget & target, sf::RenderStates states) const;

    virtual void    mise_a_jour();

};
// class Monde

#endif // _MONDE_HPP_
