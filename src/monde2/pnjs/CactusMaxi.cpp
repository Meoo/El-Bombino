/**
 * @file   CactusMaxi.cpp
 * @author Bastien Brunnenstein
 * @author Pascal-Pierre Sanchez-Carrion
 */


#include <monde2/pnjs/CactusMaxi.hpp>
#include <moteur/Jeu.hpp>
#include <moteur/Case.hpp>
#include <moteur/objets/Bonus.hpp>
#include <moteur/objets/Soulevable.hpp>
#include <moteur/objets/Joueur.hpp>
#include <Config.hpp>

#include <vector>

CactusMaxi::CactusMaxi(Case * cse) : MobileIA(cse, IDIOT_PUISSANCE_DEFAULT, IDIOT_VIE_DEFAULT, Jeu::instance().get_texture("cactusmaxi")), _coldown_att(IDIOT_COLDOWN_ATT), _visibilite(IDIOT_VISIBILITE_DEFAULT), _puissance(IDIOT_PUISSANCE_DEFAULT), _acces_joueur(false)
{
    get_sprite().setScale(1.2, 1.2);
}

CactusMaxi::~CactusMaxi()
{
}

void CactusMaxi::appliquer_bonus(Bonus::bonus_t type_bonus)
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
}// appliquer_bonus()


void CactusMaxi::mise_a_jour_ia()
{
    unsigned max = -1;
    if(get_case()->get_case_info()._distance < max)
    {
        if(!_acces_joueur)
        {
            _acces_joueur = true;
            set_vitesse(  get_vitesse() * 3.0);
        }
        bouger(get_case()->get_case_info()._direction);
    }
    else
    {
        if(_acces_joueur)
        {
            _acces_joueur = false;
            set_vitesse( get_vitesse() / 3.0);
        }

        deplacement_aleatoire();
    }
}// mise_a_jour_ia()


void CactusMaxi::mise_a_jour()
{
    MobileIA::mise_a_jour();
}// mise_a_jour()


void CactusMaxi::laisser_tomber_objet(Case* cse)
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


//fin implementation class CactusMaxi
