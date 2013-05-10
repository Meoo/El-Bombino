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
    unsigned        _puissance;



public:
                    Bombe(Mobile * porteur, unsigned timer, unsigned puissance);
    virtual         ~Bombe();

    virtual void            exploser();

    // Fonction d'affichage de Drawable
    virtual void    draw(sf::RenderTarget & target, sf::RenderStates states) const;

    virtual void    mise_a_jour();

    virtual void    blesser();

    unsigned        get_puissance();
};
// class Bombe


#endif /* BOMBE_HPP_ */
