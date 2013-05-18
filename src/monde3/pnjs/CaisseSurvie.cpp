/**
 * @file   CaisseSurvie.cpp
 * @author Bastien Brunnenstein
 * @author Pascal-Pierre Sanchez-Carrion
 */

#include <monde3/pnjs/CaisseSurvie.hpp>
#include <moteur/Jeu.hpp>
#include <moteur/Case.hpp>
#include <moteur/objets/Bonus.hpp>
#include <moteur/objets/Soulevable.hpp>
#include <moteur/objets/Joueur.hpp>
#include <Config.hpp>
#include <iostream>

using namespace std;


#include <vector>

CaisseSurvie::CaisseSurvie(Case * cse) :
        MobileIA(cse, IDIOT_PUISSANCE_DEFAULT, IDIOT_VIE_DEFAULT,
                Jeu::instance().get_texture("caissesurvie1")), _coldown_att(
                IDIOT_COLDOWN_ATT), _visibilite(IDIOT_VISIBILITE_DEFAULT), _puissance(
                IDIOT_PUISSANCE_DEFAULT)
{
    get_sprite().setScale(1, 1);
}

CaisseSurvie::~CaisseSurvie()
{
}

void CaisseSurvie::appliquer_bonus(Bonus::bonus_t type_bonus)
{
    return;
} // appliquer_bonus()


void CaisseSurvie::mise_a_jour_ia()
{
    unsigned max = -1;
    if (get_case()->get_case_info()._danger_explosion < max)
    {
        set_vitesse(3.0);
        get_sprite().setTexture(Jeu::instance().get_texture("caissesurvie2"), true);

        if (get_case()->get_case_gauche()->est_praticable()
            && get_case()->get_case_gauche()->get_objet() == NULL
            && !get_case()->get_case_gauche()->est_en_feu()
            && get_case()->get_case_gauche()->get_case_info()._danger_explosion == max) {
            bouger(nsUtil::GAUCHE);
            return;
        }
        else if (get_case()->get_case_droite()->est_praticable()
            && get_case()->get_case_droite()->get_objet() == NULL
            && !get_case()->get_case_droite()->est_en_feu()
            && get_case()->get_case_droite()->get_case_info()._danger_explosion == max) {
            bouger(nsUtil::DROITE);
            return;
        }
        else if (get_case()->get_case_haut()->est_praticable()
            && get_case()->get_case_haut()->get_objet() == NULL
            && !get_case()->get_case_haut()->est_en_feu()
            && get_case()->get_case_haut()->get_case_info()._danger_explosion == max) {
            bouger(nsUtil::HAUT);
            return;
        }
        else if (get_case()->get_case_bas()->est_praticable()
            && get_case()->get_case_bas()->get_objet() == NULL
            && !get_case()->get_case_bas()->est_en_feu()
            && get_case()->get_case_bas()->get_case_info()._danger_explosion == max) {
            bouger(nsUtil::BAS);
            return;
        }

        if ((get_case()->get_case_gauche()->get_case_info()._distance_cacher
            > get_case()->get_case_info()._distance_cacher)
            && get_case()->get_case_gauche()->est_praticable()
            && get_case()->get_case_gauche()->get_objet() == NULL
            && !get_case()->get_case_gauche()->est_en_feu())
            bouger(nsUtil::GAUCHE);
        else if ((get_case()->get_case_droite()->get_case_info()._distance_cacher
            > get_case()->get_case_info()._distance_cacher)
            && get_case()->get_case_droite()->est_praticable()
            && get_case()->get_case_droite()->get_objet() == NULL
            && !get_case()->get_case_droite()->est_en_feu())
            bouger(nsUtil::DROITE);
        else if ((get_case()->get_case_haut()->get_case_info()._distance_cacher
            > get_case()->get_case_info()._distance_cacher)
            && get_case()->get_case_haut()->est_praticable()
            && get_case()->get_case_haut()->get_objet() == NULL
            && !get_case()->get_case_haut()->est_en_feu())
            bouger(nsUtil::HAUT);
        else if ((get_case()->get_case_bas()->get_case_info()._distance_cacher
            > get_case()->get_case_info()._distance_cacher)
            && get_case()->get_case_bas()->est_praticable()
            && get_case()->get_case_bas()->get_objet() == NULL
            && !get_case()->get_case_bas()->est_en_feu())
            bouger(nsUtil::BAS);
    }
    else
    {
        set_vitesse(1.0);
        get_sprite().setTexture(Jeu::instance().get_texture("caissesurvie1"), true);
    }
} // mise_a_jour_ia()

void CaisseSurvie::mise_a_jour()
{
    MobileIA::mise_a_jour();
}


void CaisseSurvie::laisser_tomber_objet(Case* cse)
{
    int type_bonus = rand() % BONUS_NB_DIFFERENTS_PNJ
            + BONUS_NB_DIFFERENTS_CAISSE;
    switch (type_bonus)
    {
    case Bonus::SPECIAL_GANT:
        new Bonus(get_case(), Bonus::SPECIAL_GANT);
        break;
    case Bonus::SPECIAL_BOMBE_GLACEE:
        new Bonus(get_case(), Bonus::SPECIAL_BOMBE_GLACEE);
        break;
    default:
        break;
    }
}    // laisser_tomber_objet()

//fin implementation class CaisseSurvie
