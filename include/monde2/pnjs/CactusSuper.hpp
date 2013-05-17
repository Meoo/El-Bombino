/*
 * CactusSuper.hpp
 *
 *  Created on: 17 mai 2013
 *      Author: Sanpas
 */

#ifndef CACTUSSUPER_HPP_
#define CACTUSSUPER_HPP_


#include "../../moteur/objets/MobileIA.hpp"

/**
 * @brief
 */
class CactusSuper : public MobileIA
{
private:
    unsigned    _coldown_att;
    unsigned    _visibilite;
    unsigned    _puissance;
    bool        _acces_joueur;
    bool        _objet;

public:
    CactusSuper(Case * cse);
    virtual ~CactusSuper();

    virtual void mise_a_jour_ia();

    virtual void mise_a_jour();

    virtual void    laisser_tomber_objet(Case * cse);

    virtual void    appliquer_bonus(Bonus::bonus_t type_bonus);

private:

};
// class CactusSuper


#endif /* CACTUSSUPER_HPP_ */
