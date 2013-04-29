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
                Bonus(Case * cse, sf::Sprite sprite);
    virtual     ~Bonus();

    virtual void mise_a_jour();
};
// Class Bonus


#endif /* BONUS_HPP_ */
