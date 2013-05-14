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

CactusMaxi::CactusMaxi(Case * cse) : MobileIA(cse, IDIOT_PUISSANCE_DEFAULT, IDIOT_VIE_DEFAULT, Jeu::instance().get_texture("cactusmaxi")), _derniere_direction((nsUtil::direction_t) -1), _coldown_att(IDIOT_COLDOWN_ATT), _visibilite(IDIOT_VISIBILITE_DEFAULT), _puissance(IDIOT_PUISSANCE_DEFAULT), _acces_joueur(false)
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


void CactusMaxi::attaquer_joueur()
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
        _derniere_direction = get_case()->get_case_info()._direction;
        bouger(_derniere_direction);
    }
    else
    {
        if(_acces_joueur)
        {
            _acces_joueur = false;
            set_vitesse( get_vitesse() / 3.0);
        }

        //
        //Deplacement
        //
        Case * gauche = get_case()->get_case_gauche();
        Soulevable * bonus_gauche = dynamic_cast<Soulevable *> (gauche->get_objet());
        bool gauche_ok = gauche->est_praticable() && !gauche->est_en_feu() && (gauche->get_objet() == NULL || !bonus_gauche);

        Case * droite = get_case()->get_case_droite();
        Soulevable * bonus_droite = dynamic_cast<Soulevable *> (droite->get_objet());
        bool droite_ok = droite->est_praticable() && !droite->est_en_feu() && (droite->get_objet() == NULL || !bonus_droite);

        Case * haut = get_case()->get_case_haut();
        Soulevable * bonus_haut = dynamic_cast<Soulevable *> (haut->get_objet());
        bool haut_ok = haut->est_praticable() && !haut->est_en_feu() && (haut->get_objet() == NULL || !bonus_haut);

        Case * bas = get_case()->get_case_bas();
        Soulevable * bonus_bas = dynamic_cast<Soulevable *> (bas->get_objet());
        bool bas_ok = bas->est_praticable() && !bas->est_en_feu() && (bas->get_objet() == NULL || !bonus_bas);

        int num_choix = gauche_ok + droite_ok + haut_ok + bas_ok;

        if (num_choix == 0) return;

        // Si on as plusieurs choix on bloque la direction d'ou l'on vient
        if (num_choix > 1)
        {
            switch(_derniere_direction)
            {
            case nsUtil::HAUT:
                bas_ok = false; --num_choix;
                break;
            case nsUtil::BAS:
                haut_ok = false; --num_choix;
                break;
            case nsUtil::GAUCHE:
                droite_ok = false; --num_choix;
                break;
            case nsUtil::DROITE:
                gauche_ok = false; --num_choix;
                break;
            }
        }

        int choix = rand() % num_choix;

        if (gauche_ok)
        {
            if (choix == 0)
            {
                _derniere_direction = nsUtil::GAUCHE;
                bouger(nsUtil::GAUCHE);
                return;
            }
            --choix;
        }

        if (droite_ok)
        {
            if (choix == 0)
            {
                _derniere_direction = nsUtil::DROITE;
                bouger(nsUtil::DROITE);
                return;
            }
            --choix;
        }

        if (haut_ok)
        {
            if (choix == 0)
            {
                _derniere_direction = nsUtil::HAUT;
                bouger(nsUtil::HAUT);
                return;
            }
            --choix;
        }

        if (bas_ok)
        {
            if (choix == 0)
            {
                _derniere_direction = nsUtil::BAS;
                bouger(nsUtil::BAS);
                return;
            }
        }

        if(num_choix == 0)
        {
            return;
        }
        assert(false);
    }
}// mise_a_jour_ia()


void CactusMaxi::mise_a_jour()
{
    MobileIA::mise_a_jour();
    //
    //
    if(_coldown_att > 0)
        --_coldown_att;
    else
        attaquer_joueur();
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
