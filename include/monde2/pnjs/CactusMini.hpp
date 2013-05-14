/**
 * @file   CactusMini.hpp
 * @author Bastien Brunnenstein
 * @author Pascal-Pierre Sanchez-Carrion
 */

#ifndef CACTUSMINI_HPP_
#define CACTUSMINI_HPP_

#include "../../moteur/objets/MobileIA.hpp"

/**
 * @brief
 */
class CactusMini : public MobileIA
{
private:
    unsigned    _coldown_att;
    unsigned    _visibilite;
    unsigned    _puissance;
    bool        _acces_joueur;

public:
    CactusMini(Case * cse);
    virtual ~CactusMini();

    virtual void mise_a_jour_ia();

    virtual void mise_a_jour();

    virtual void    laisser_tomber_objet(Case * cse);

    virtual void    appliquer_bonus(Bonus::bonus_t type_bonus);
private:

};
// class CactusMini


#endif /* CACTUSMINI_HPP_ */
