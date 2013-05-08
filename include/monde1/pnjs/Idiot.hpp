/**
 * @file   Idiot.hpp
 * @author Bastien Brunnenstein
 */

#ifndef _IDIOT_HPP_
#define _IDIOT_HPP_

#include "../../moteur/objets/MobileIA.hpp"

/**
 * @brief
 */
class Idiot : public MobileIA
{
private:
    Direction   _derniere_direction;
    unsigned    _coldown_att;
    unsigned    _visibilite;
    unsigned    _puissance;

public:
    Idiot(Case * cse);
    virtual ~Idiot();

    virtual void mise_a_jour_ia();

    virtual void mise_a_jour();

    virtual void    laisser_tomber_objet(Case * cse);

    virtual void    appliquer_bonus(Bonus::bonus_t type_bonus);

    void attaquer_joueur();
private:

};
// class Idiot

#endif // _IDIOT_HPP_
