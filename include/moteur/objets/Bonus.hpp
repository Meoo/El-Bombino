/**
 * @file   Bonus.hpp
 * @author Bastien Brunnenstein
 * @author Pascal-Pierre Sanchez-Carrion
 */

#ifndef BONUS_HPP_
#define BONUS_HPP_

#include <moteur/objets/Immobile.hpp>

class Mobile;


/**
 * @brief
 */
class Bonus : public Immobile
{
public:
    enum bonus_t{
        BONUS_BOMBE,
        BONUS_PUISSANCE,
        BONUS_VITESSE,
        BONUS_VIE,
        MALUS_BOMBE,
        MALUS_PUISSANCE,
        MALUS_VITESSE,
        SPECIAL_GANT,
        SPECIAL_BOMBE_GLACEE,
    };

private:
    sf::Sprite          _sprite;
    bonus_t             _type_bonus;

    unsigned            _timer;
    mutable bool        _clignote;
    unsigned            _invesible;



public:
                Bonus(Case * cse, bonus_t type_bonus);
    virtual     ~Bonus();

    virtual void    draw(sf::RenderTarget & target, sf::RenderStates states) const;

    virtual void mise_a_jour();

    virtual void blesser();

    void        utiliser(Mobile * mobile);
};
// Class Bonus


#endif /* BONUS_HPP_ */
