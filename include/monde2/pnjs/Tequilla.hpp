/*
 * Tequilla.hpp
 *
 *  Created on: 15 mai 2013
 *      Author: Sanpas
 */

#ifndef TEQUILLA_HPP_
#define TEQUILLA_HPP_

#include "../../moteur/objets/MobileIA.hpp"

/**
 * @brief
 */
class Tequilla : public MobileIA
{
private:
    unsigned    _coldown_att;
    unsigned    _visibilite;
    unsigned    _puissance;

public:
    Tequilla(Case * cse);
    virtual ~Tequilla();

    virtual void mise_a_jour_ia();

    virtual void mise_a_jour();

    virtual void    laisser_tomber_objet(Case * cse);

    virtual void    appliquer_bonus(Bonus::bonus_t type_bonus);

    void attaquer_joueur();
private:

};
// class Tequilla


#endif /* TEQUILLA_HPP_ */
