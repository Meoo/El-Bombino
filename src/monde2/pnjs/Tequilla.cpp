/*
 * Tequilla.cpp
 *
 *  Created on: 15 mai 2013
 *      Author: Sanpas
 */



/**
 * @file   Idiot.cpp
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


void Tequilla::attaquer_joueur()
{
    //
    //Attaque
    //
    //#TODO
    Case * gauche = get_case()->get_case_gauche();
    Joueur *joueur_gauche;
    bool gauche_att = false;
    for(unsigned i = 0; i < _visibilite; ++i)
    {
        joueur_gauche = dynamic_cast<Joueur *> (gauche->get_objet());
        if(gauche->est_praticable())
        {
            gauche_att = gauche_att || joueur_gauche;
            gauche = gauche->get_case_gauche();
        }
    }
    if(gauche_att)
    {
        _coldown_att = IDIOT_COLDOWN_ATT;
        get_case()->enflammer_direction(nsUtil::GAUCHE, _puissance);
    }


    Case * droite = get_case()->get_case_droite();
    Joueur *joueur_droite;
    bool droite_att = false;
    for(unsigned i = 0; i < _visibilite; ++i)
    {
        joueur_droite = dynamic_cast<Joueur *> (droite->get_objet());
        if(droite->est_praticable())
        {
            droite_att = droite_att || joueur_droite;
            droite = droite->get_case_droite();
        }
    }
    if(droite_att)
    {
        get_case()->enflammer_direction(nsUtil::DROITE,_puissance);
        _coldown_att = IDIOT_COLDOWN_ATT;
    }


    Case * bas = get_case()->get_case_bas();
    Joueur *joueur_bas;
    bool bas_att = false;
    for(unsigned i = 0; i < _visibilite; ++i)
    {
        joueur_bas = dynamic_cast<Joueur *> (bas->get_objet());
        if(bas->est_praticable())
        {
            bas_att = bas_att || joueur_bas;
            bas = bas->get_case_bas();
        }
    }
    if(bas_att)
    {
        get_case()->enflammer_direction(nsUtil::BAS, _puissance);
        _coldown_att = IDIOT_COLDOWN_ATT;
    }


    Case * haut = get_case()->get_case_haut();
    Joueur *joueur_haut;
    bool haut_att = false;
    for(unsigned i = 0; i < _visibilite; ++i)
    {
        joueur_haut = dynamic_cast<Joueur *> (haut->get_objet());
        if(haut->est_praticable())
        {
            haut_att = haut_att || (joueur_haut);
            haut = haut->get_case_haut();
        }
    }
    if(haut_att)
    {
        _coldown_att = IDIOT_COLDOWN_ATT;
        get_case()->enflammer_direction(nsUtil::HAUT, _puissance);
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
