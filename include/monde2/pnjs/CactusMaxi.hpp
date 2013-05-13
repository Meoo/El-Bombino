/**
 * @file   CactusMaxi.hpp
 * @author Bastien Brunnenstein
 * @author Pascal-Pierre Sanchez-Carrion
 */

#ifndef CACTUS_MAXI_HPP_
#define CACTUS_MAXI_HPP_

#include "../../moteur/objets/MobileIA.hpp"

/**
 * @brief
 */
class CactusMaxi : public MobileIA
{
private:
    nsUtil::direction_t   _derniere_direction;
    unsigned    _coldown_att;
    unsigned    _visibilite;
    unsigned    _puissance;

public:
    CactusMaxi(Case * cse);
    virtual ~CactusMaxi();

    virtual void mise_a_jour_ia();

    virtual void mise_a_jour();

    virtual void    laisser_tomber_objet(Case * cse);

    virtual void    appliquer_bonus(Bonus::bonus_t type_bonus);

    void attaquer_joueur();
private:

};
// class CactusMaxi


#endif /* CACTUS_MAXI_HPP_ */
