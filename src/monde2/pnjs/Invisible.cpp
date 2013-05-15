/*
 * Invisible.cpp
 *
 *  Created on: 16 mai 2013
 *      Author: Sanpas
 */




/**
 * @file   Tequilla.cpp
 * @author Bastien Brunnenstein
 * @author Pascal-Pierre Sanchez-Carrion
 */

#include <monde2/pnjs/Invisible.hpp>
#include <moteur/Jeu.hpp>
#include <moteur/Case.hpp>
#include <moteur/objets/Bonus.hpp>
#include <moteur/objets/Joueur.hpp>


#include <vector>

Invisible::Invisible(Case * cse) : MobileIA(cse, 1.f, IDIOT_VIE_DEFAULT, Jeu::instance().get_texture("invisible")),
                            _coldown_att(IDIOT_COLDOWN_ATT), _visibilite(IDIOT_VISIBILITE_DEFAULT), _puissance(IDIOT_PUISSANCE_DEFAULT), _invisible(true)
{
}

Invisible::~Invisible()
{
}

void Invisible::appliquer_bonus(Bonus::bonus_t type_bonus)
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


void Invisible::attaquer_joueur()
{

}// attaquer_joueur()


void Invisible::mise_a_jour_ia()
{
    unsigned max = -1;
    if(get_case()->get_case_info()._distance > 5){
        get_sprite().setTexture(Jeu::instance().get_texture("invisible"));
        if(!_invisible){
            _invisible = !_invisible;
            set_vitesse(get_vitesse() / 4);
        }
    }
    if(get_case()->get_case_info()._distance <= 5 ){
        get_sprite().setTexture(Jeu::instance().get_texture("mouche"));
        if(_invisible){
            _invisible = !_invisible;
            set_vitesse(get_vitesse() * 4);
        }
    }

    deplacement_aleatoire();
}// mise_a_jour_ia()


void Invisible::mise_a_jour()
{
    MobileIA::mise_a_jour();
    //
    //
    if(_coldown_att > 0)
        --_coldown_att;
    else
        attaquer_joueur();
}// mise_a_jour()


void Invisible::laisser_tomber_objet(Case* cse)
{
    int bonnus_ok = rand() % 4;
    if (bonnus_ok == 0)
    {
        int type_bonus = rand() % 2;
        if(type_bonus == 0)
            new Bonus(get_case(),Bonus::BONUS_VIE);
        else
            new Bonus(get_case(), Bonus::BONUS_VITESSE);
    }
    else
    {
        int type_bonus = rand() % 4;
        if(type_bonus == 0)
            new Bonus(get_case(),Bonus::SPECIAL_BOMBE_GLACEE);
        else
            new Bonus(get_case(), Bonus::SPECIAL_GANT);
    }
}// laisser_tomber_objet()


//fin implementation class Tequilla
