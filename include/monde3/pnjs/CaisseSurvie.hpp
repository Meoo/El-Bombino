/**
 * @file   CaisseSurvie.hpp
 * @author Bibi
 */

#ifndef CAISSE_SURVIE_HPP_
#define CAISSE_SURVIE_HPP_

#include "../../moteur/objets/MobileIA.hpp"

/**
 * @brief
 */
class CaisseSurvie : public MobileIA
{
private:
    unsigned    _coldown_att;
    unsigned    _visibilite;
    unsigned    _puissance;
    bool        _acces_joueur;

public:
    CaisseSurvie(Case * cse);
    virtual ~CaisseSurvie();

    virtual void mise_a_jour_ia();

    virtual void mise_a_jour();

    virtual void    laisser_tomber_objet(Case * cse);

    virtual void    appliquer_bonus(Bonus::bonus_t type_bonus);
private:

};
// class CaisseSurvie


#endif /* CAISSE_SURVIE_HPP_ */
