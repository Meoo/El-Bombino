/**
 * @file   Bombe.hpp
 * @author Bastien Brunnenstein
 * @author Pascal-Pierre Sanchez-Carrion
 */

#ifndef BOMBE_HPP_
#define BOMBE_HPP_

#include "Soulevable.hpp"

class Bombe : public Soulevable
{
private:
    sf::Sprite      _sprite;

    //_timer en nombres d'affichages
    unsigned        _timer;

public:
                    Bombe(Mobile * porteur);
    virtual         ~Bombe();

    void            explose();

    // Fonction d'affichage de Drawable
    virtual void    draw(sf::RenderTarget & target, sf::RenderStates states) const;

    // redefinition de deposer (initialisation du timer)
    virtual void    deposer(Case *cse);

    // redefinition de mise_a_jour (timer - 1) timer compte le nombres de frame (50 frame par seconde)
    virtual void    mise_a_jour();
};
// class Bombe


#endif /* BOMBE_HPP_ */
