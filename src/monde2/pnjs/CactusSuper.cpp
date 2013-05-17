/*
 * CactusSuper.cpp
 *
 *  Created on: 17 mai 2013
 *      Author: Sanpas
 */

#include <monde2/pnjs/CactusSuper.hpp>
#include <moteur/Jeu.hpp>
#include <moteur/Case.hpp>
#include <moteur/objets/Bonus.hpp>
#include <moteur/objets/Soulevable.hpp>
#include <moteur/objets/Joueur.hpp>
#include <Config.hpp>

#include <vector>

CactusSuper::CactusSuper(Case * cse) : MobileIA(cse, IDIOT_PUISSANCE_DEFAULT, IDIOT_VIE_DEFAULT, Jeu::instance().get_texture("porteur")), _coldown_att(IDIOT_COLDOWN_ATT), _visibilite(IDIOT_VISIBILITE_DEFAULT), _puissance(IDIOT_PUISSANCE_DEFAULT), _acces_joueur(false), _objet(false)
{
    get_sprite().setScale(1.2, 1.2);
}

CactusSuper::~CactusSuper()
{
}

void CactusSuper::appliquer_bonus(Bonus::bonus_t type_bonus)
{
    if(est_valide())
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
               if(this->_acces_joueur)
               {
                   if(get_vitesse()+JOUEUR_VIT_DELTA < JOUEUR_VIT_MAX)
                       set_vitesse(get_vitesse()+ JOUEUR_VIT_DELTA);
                   else
                       set_vitesse(JOUEUR_VIT_MAX);
               }
               break;
           case Bonus::MALUS_BOMBE:
               break;
           case Bonus::MALUS_VITESSE:
               if(this->_acces_joueur)
               {
                   if(get_vitesse() - JOUEUR_VIT_DELTA > JOUEUR_VIT_MIN)
                      set_vitesse(get_vitesse() - JOUEUR_VIT_DELTA);
                  else
                      set_vitesse(JOUEUR_VIT_MIN);
               }
               break;
            default:
                break;
        }
    }
}// appliquer_bonus()


void CactusSuper::mise_a_jour_ia()
{
    Soulevable * soulevable;
    if(get_objet_souleve() != NULL)
    {
        switch(get_case()->get_case_info()._direction_cacher){
             case(nsUtil::HAUT):
                 if(!get_case()->get_case_bas()->get_objet())
                     get_objet_souleve()->deposer(get_case()->get_case_bas());
                 else if(!get_case()->get_case_gauche()->get_objet())
                     get_objet_souleve()->deposer(get_case()->get_case_gauche());
                 else if(!get_case()->get_case_droite()->get_objet())
                     get_objet_souleve()->deposer(get_case()->get_case_droite());
                 break;
             case(nsUtil::BAS):
                 if(!get_case()->get_case_haut()->get_objet())
                     get_objet_souleve()->deposer(get_case()->get_case_haut());
                 else if(!get_case()->get_case_gauche()->get_objet())
                     get_objet_souleve()->deposer(get_case()->get_case_gauche());
                 else if(!get_case()->get_case_droite()->get_objet())
                     get_objet_souleve()->deposer(get_case()->get_case_droite());
                 break;
             case(nsUtil::DROITE):
                 if(!get_case()->get_case_bas()->get_objet())
                     get_objet_souleve()->deposer(get_case()->get_case_bas());
                 else if(!get_case()->get_case_gauche()->get_objet())
                     get_objet_souleve()->deposer(get_case()->get_case_gauche());
                 else if(!get_case()->get_case_haut()->get_objet())
                     get_objet_souleve()->deposer(get_case()->get_case_haut());
                 break;
             case(nsUtil::GAUCHE):
                 if(!get_case()->get_case_bas()->get_objet())
                     get_objet_souleve()->deposer(get_case()->get_case_bas());
                 else if(!get_case()->get_case_haut()->get_objet())
                     get_objet_souleve()->deposer(get_case()->get_case_haut());
                 else if(!get_case()->get_case_droite()->get_objet())
                     get_objet_souleve()->deposer(get_case()->get_case_droite());
                 break;
             case(nsUtil::ORIGINE):
                 break;
         }
    }
    else
    {
         switch(get_case()->get_case_info()._direction_cacher){
             case(nsUtil::HAUT):
                soulevable = dynamic_cast<Soulevable *> (get_case()->get_case_haut()->get_objet());
                 if(soulevable){
                     soulevable->set_porteur(this);
                     if(!get_case()->get_case_bas()->get_objet())soulevable->deposer(get_case()->get_case_bas());
                 }
                 break;
             case(nsUtil::BAS):
                 soulevable = dynamic_cast<Soulevable *> (get_case()->get_case_bas()->get_objet());
                 if(soulevable){
                     soulevable->set_porteur(this);
                     if(!get_case()->get_case_haut()->get_objet())soulevable->deposer(get_case()->get_case_haut());
                 }
                 break;
             case(nsUtil::DROITE):
                 soulevable = dynamic_cast<Soulevable *> (get_case()->get_case_droite()->get_objet());
                 if(soulevable){
                     soulevable->set_porteur(this);
                     if(!get_case()->get_case_gauche()->get_objet())soulevable->deposer(get_case()->get_case_gauche());
                 }
                 break;
             case(nsUtil::GAUCHE):
                 soulevable = dynamic_cast<Soulevable *> (get_case()->get_case_gauche()->get_objet());
                 if(soulevable){
                     soulevable->set_porteur(this);
                     if(!get_case()->get_case_droite()->get_objet())soulevable->deposer(get_case()->get_case_droite());
                 }
                 break;
             case(nsUtil::ORIGINE):
                 break;
         }
    }
    switch (get_case()->get_case_info()._direction) {
        case nsUtil::HAUT:
            if(get_case()->get_case_haut()->est_en_feu())return;
            break;
        case nsUtil::BAS:
            if(get_case()->get_case_bas()->est_en_feu())return;
            break;
        case nsUtil::GAUCHE:
            if(get_case()->get_case_gauche()->est_en_feu())return;
            break;
        case nsUtil::DROITE:
            if(get_case()->get_case_droite()->est_en_feu())return;
            break;
        default:
            break;
    }
     bouger(get_case()->get_case_info()._direction_cacher);
}// mise_a_jour_ia()


void CactusSuper::mise_a_jour()
{
    MobileIA::mise_a_jour();
}// mise_a_jour()


void CactusSuper::laisser_tomber_objet(Case* cse)
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


//fin implementation class CactusSuper
