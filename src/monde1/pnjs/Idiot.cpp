/**
 * @file   Idiot.cpp
 * @author Bastien Brunnenstein
 * @author Pascal-Pierre Sanchez-Carrion
 */

#include <monde1/pnjs/Idiot.hpp>
#include <moteur/Jeu.hpp>
#include <moteur/Case.hpp>
#include <moteur/objets/Bonus.hpp>
#include <moteur/objets/Soulevable.hpp>
#include <moteur/objets/Joueur.hpp>
#include <Config.hpp>

#include <vector>

Idiot::Idiot(Case * cse) : MobileIA(cse, IDIOT_PUISSANCE_DEFAULT, IDIOT_VIE_DEFAULT, Jeu::instance().get_texture("idiot")), _coldown_att(IDIOT_COLDOWN_ATT), _visibilite(IDIOT_VISIBILITE_DEFAULT), _puissance(IDIOT_PUISSANCE_DEFAULT)
{
}

Idiot::~Idiot()
{
}

void Idiot::appliquer_bonus(Bonus::bonus_t type_bonus)
{
    switch (type_bonus) {

        case (Bonus::BONUS_PUISSANCE):
            if(_puissance + IDIOT_PUISSANCE_DELTA < IDIOT_PUISSANCE_MAX)
                _puissance += IDIOT_PUISSANCE_DELTA;
            else
                _puissance = IDIOT_PUISSANCE_MAX;
            break;
        case(Bonus::MALUS_PUISSANCE):
            if(_puissance - IDIOT_PUISSANCE_DELTA > IDIOT_PUISSANCE_MIN)
                _puissance -= IDIOT_PUISSANCE_DELTA;
            else
                _puissance = IDIOT_PUISSANCE_MIN;
            break;
        case Bonus::BONUS_BOMBE:
           break;
       case Bonus::BONUS_VIE:
           if(get_vies()+IDIOT_VIE_DELTA < IDIOT_VIE_MAX)
               set_vies(get_vies()+ IDIOT_VIE_DELTA);
           else
               set_vies(IDIOT_VIE_MAX);
           break;
       case Bonus::BONUS_VITESSE:
           if(get_vitesse()+JOUEUR_VIT_DELTA < JOUEUR_VIT_MAX)
               set_vitesse(get_vitesse()+ JOUEUR_VIT_DELTA);
           else
               set_vitesse(JOUEUR_VIT_MAX);
           break;
       case Bonus::MALUS_BOMBE:
           break;
       case Bonus::MALUS_VITESSE:
           if(get_vitesse() - JOUEUR_VIT_DELTA > JOUEUR_VIT_MIN)
               set_vitesse(get_vitesse() - JOUEUR_VIT_DELTA);
           else
               set_vitesse(JOUEUR_VIT_MIN);
           break;
        default:
            break;
    }
}// appliquer_bonus()


void Idiot::attaquer_joueur()
{
    if((rand() % 10 == 0) && get_direction() != nsUtil::GAUCHE)
    {
        _coldown_att = IDIOT_COLDOWN_ATT + rand() % IDIOT_COLDOWN_ATT_RAND;
        get_case()->enflammer_direction(nsUtil::GAUCHE, _puissance + (rand() % 10 == 0 ? 1 : 0));
        return;
    }

    if((rand() % 10 == 0) && get_direction() != nsUtil::DROITE)
    {
        get_case()->enflammer_direction(nsUtil::DROITE,_puissance + (rand() % 10 == 0 ? 1 : 0));
        _coldown_att = IDIOT_COLDOWN_ATT + rand() % IDIOT_COLDOWN_ATT_RAND;
        return;
    }

    if((rand() % 10 == 0) && get_direction() != nsUtil::BAS)
    {
        get_case()->enflammer_direction(nsUtil::BAS, _puissance + (rand() % 10 == 0 ? 1 : 0));
        _coldown_att = IDIOT_COLDOWN_ATT + rand() % IDIOT_COLDOWN_ATT_RAND;
        return;
    }

    if((rand() % 10 == 0) && get_direction() != nsUtil::HAUT)
    {
        get_case()->enflammer_direction(nsUtil::HAUT, _puissance + (rand() % 10 == 0 ? 1 : 0));
        _coldown_att = IDIOT_COLDOWN_ATT + rand() % IDIOT_COLDOWN_ATT_RAND;
        return;
    }
}// attaquer_joueur()


void Idiot::mise_a_jour_ia()
{
    deplacement_aleatoire();
}// mise_a_jour_ia()


void Idiot::mise_a_jour()
{
    MobileIA::mise_a_jour();
    //
    //
    if(_coldown_att > 0)
        --_coldown_att;
    else
        attaquer_joueur();
}// mise_a_jour()


void Idiot::laisser_tomber_objet(Case* cse)
{
    int type_bonus = rand() % BONUS_NB_DIFFERENTS_PNJ + BONUS_NB_DIFFERENTS_CAISSE;
    switch (type_bonus) {
        case Bonus::SPECIAL_GANT:
            new Bonus(get_case(),Bonus::SPECIAL_GANT);
            break;
        case Bonus::SPECIAL_BOMBE_GLACEE:
            new Bonus(get_case(), Bonus::SPECIAL_BOMBE_GLACEE);
            break;
        default:
            break;
    }
}// laisser_tomber_objet()


//fin implementation class Idiot
