/**
 * @file   Tequilla.cpp
 * @author Bastien Brunnenstein
 * @author Pascal-Pierre Sanchez-Carrion
 */

#include <monde2/pnjs/Tequilla.hpp>
#include <moteur/Jeu.hpp>
#include <moteur/Case.hpp>
#include <moteur/objets/Bonus.hpp>
#include <moteur/objets/Joueur.hpp>


#include <vector>

Tequilla::Tequilla(Case * cse) : MobileIA(cse, 1.f, IDIOT_VIE_DEFAULT, Jeu::instance().get_texture("tequilla")),
                            _coldown_att(IDIOT_COLDOWN_ATT), _visibilite(IDIOT_VISIBILITE_DEFAULT), _puissance(IDIOT_PUISSANCE_DEFAULT)
{
}

Tequilla::~Tequilla()
{
}

void Tequilla::appliquer_bonus(Bonus::bonus_t type_bonus)
{
    switch (type_bonus) {

        case (Bonus::BONUS_PUISSANCE):
            if(_puissance + IDIOT_PUISSANCE_DELTA < IDIOT_PUISSANCE_MAX)
            {
                _puissance += IDIOT_PUISSANCE_DELTA;
                if(_visibilite < 6)++_visibilite;
            }
            else
            {
                _puissance = IDIOT_PUISSANCE_MAX;
                if(_visibilite < 6)++_visibilite;
            }
            break;
        case(Bonus::MALUS_PUISSANCE):
            if(_puissance - IDIOT_PUISSANCE_DELTA > IDIOT_PUISSANCE_MIN)
            {
                _puissance -= IDIOT_PUISSANCE_DELTA;
                if(_visibilite > 2)--_visibilite;
            }
            else
            {
                _puissance = IDIOT_PUISSANCE_MIN;
                if(_visibilite > 2)--_visibilite;
            }
            break;
        case Bonus::BONUS_BOMBE:
           break;
       case Bonus::BONUS_VIE:
           if(get_vies()+IDIOT_VIE_DELTA < IDIOT_VIE_MAX)
               set_vitesse(get_vies()+ IDIOT_VIE_DELTA);
           else
               set_vitesse(IDIOT_VIE_MAX);
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


void Tequilla::attaquer_joueur()
{
    if(get_case()->get_case_info()._distance <= _visibilite)
    {
        get_case()->enflammer_direction(get_case()->get_case_info()._direction,_puissance + (rand()%3));
        _coldown_att = IDIOT_COLDOWN_ATT;
    }
}// attaquer_joueur()


void Tequilla::mise_a_jour_ia()
{

    deplacement_aleatoire();
}// mise_a_jour_ia()


void Tequilla::mise_a_jour()
{
    MobileIA::mise_a_jour();
    //
    //
    if(_coldown_att > 0)
        --_coldown_att;
    else
        attaquer_joueur();
}// mise_a_jour()


void Tequilla::laisser_tomber_objet(Case* cse)
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


//fin implementation class Tequilla
