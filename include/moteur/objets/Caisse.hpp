/**
 * @file   Caisse.hpp
 * @author Bastien Brunnenstein
 * @author Pascal-Pierre Sanchez-Carrion
 */

#ifndef _CAISSE_HPP_
#define _CAISSE_HPP_

#include "Soulevable.hpp"

class Caisse : public Soulevable
{
private:
    sf::Sprite      _sprite;

public:
    explicit        Caisse(Case * cse);
    virtual         ~Caisse();

    // Fonction d'affichage de Drawable
    virtual void    draw(sf::RenderTarget & target, sf::RenderStates states) const;

    virtual void    mise_a_jour();

    virtual void    laisser_tomber_objet(Case * cse);
};
// class Caisse

#endif /* _CAISSE_HPP_ */
