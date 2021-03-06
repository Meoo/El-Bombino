/*
 * Invisible.hpp
 *
 *  Created on: 16 mai 2013
 *      Author: Sanpas
 */

#ifndef INVISIBLE_HPP_
#define INVISIBLE_HPP_


#include "../../moteur/objets/MobileIA.hpp"

/**
 * @brief
 */
class Invisible : public MobileIA
{
private:
    unsigned    _coldown_att;
    unsigned    _visibilite;
    unsigned    _puissance;
    bool        _invisible;

public:
    Invisible(Case * cse);
    virtual ~Invisible();

    virtual void mise_a_jour_ia();

    virtual void mise_a_jour();

    virtual void    laisser_tomber_objet(Case * cse);

    virtual void    appliquer_bonus(Bonus::bonus_t type_bonus);

    void attaquer_joueur();
private:

};

#endif /* INVISIBLE_HPP_ */
