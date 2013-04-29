/**
 * @file   Bonus.hpp
 * @author Bastien Brunnenstein
 * @author Pascal-Pierre Sanchez-Carrion
 */

#ifndef BONUS_HPP_
#define BONUS_HPP_

#include <moteur/objets/Immobile.hpp>

class Bonus : public Immobile
{
private:
    sf::Sprite      _sprite;


public:
                Bonus(Case * cse);
    virtual     ~Bonus();

    virtual void    draw(sf::RenderTarget & target, sf::RenderStates states) const;

    virtual void mise_a_jour();

    virtual void blesser();

    void        utiliser(Objet *);
};
// Class Bonus


#endif /* BONUS_HPP_ */
