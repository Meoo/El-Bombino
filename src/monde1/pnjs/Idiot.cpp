/**
 * @file   Idiot.cpp
 * @author Bastien Brunnenstein
 */

#include <monde1/pnjs/Idiot.hpp>
#include <moteur/Jeu.hpp>
#include <moteur/Case.hpp>
#include <moteur/objets/Bonus.hpp>
#include <moteur/objets/Joueur.hpp>
#include <Config.hpp>

#include <vector>

Idiot::Idiot(Case * cse) : MobileIA(cse, 1.f, 2, Jeu::instance().get_texture("idiot")), _derniere_direction((Direction) -1), _coldown_att(IDIOT_COLDOWN_ATT), _visibilite(IDIOT_VISIBILITE_DEFAULT), _puissance(IDIOT_PUISSANCE_DEFAULT)
{
}

Idiot::~Idiot()
{
}

void Idiot::appliquer_bonus(Bonus::bonus_t type_bonus)
{
    MobileIA::appliquer_bonus(type_bonus);
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
        default:
            break;
    }
}

void Idiot::attaquer_joueur()
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
    gauche = get_case()->get_case_gauche();
    bool r_gauche = true;
    if(gauche_att)
    {
        _coldown_att = IDIOT_COLDOWN_ATT;
        for(unsigned i = 0; i < _puissance; ++i)
        {
            if(gauche->est_praticable() && r_gauche)
            {
                r_gauche = gauche->enflammer();
                gauche = gauche->get_case_gauche();
            }
        }
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
    droite = get_case()->get_case_droite();
    bool r_droite = true;
    if(droite_att)
    {
        _coldown_att = IDIOT_COLDOWN_ATT;
        for(unsigned i = 0; i < _puissance; ++i)
        {
            if(droite->est_praticable() && r_droite)
            {
                r_droite = droite->enflammer();
                droite = droite->get_case_droite();
            }
        }
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
    bas = get_case()->get_case_bas();
    bool r_bas = true;
    if(bas_att)
    {
        _coldown_att = IDIOT_COLDOWN_ATT;
        for(unsigned i = 0; i < _puissance; ++i)
        {
            if(bas->est_praticable() && r_bas)
            {
                r_bas = bas->enflammer();
                bas = bas->get_case_bas();
            }
        }
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
    haut = get_case()->get_case_haut();
    bool r_haut = true;
    if(haut_att)
    {
        _coldown_att = IDIOT_COLDOWN_ATT;
        for(unsigned i = 0; i < _puissance; ++i)
        {
            if(haut->est_praticable() && r_haut)
            {
                r_haut = haut->enflammer();
                haut = haut->get_case_haut();
            }
        }
    }
}

void Idiot::mise_a_jour_ia()
{

    //
    //Deplacement
    //
    Case * gauche = get_case()->get_case_gauche();
    Bonus * bonus_gauche = dynamic_cast<Bonus *> (gauche->get_objet());
    bool gauche_ok = gauche->est_praticable() && !gauche->est_en_feu() && (gauche->get_objet() == NULL || bonus_gauche);

    Case * droite = get_case()->get_case_droite();
    Bonus * bonus_droite = dynamic_cast<Bonus *> (droite->get_objet());
    bool droite_ok = droite->est_praticable() && !droite->est_en_feu() && (droite->get_objet() == NULL || bonus_droite);

    Case * haut = get_case()->get_case_haut();
    Bonus * bonus_haut = dynamic_cast<Bonus *> (haut->get_objet());
    bool haut_ok = haut->est_praticable() && !haut->est_en_feu() && (haut->get_objet() == NULL || bonus_haut);

    Case * bas = get_case()->get_case_bas();
    Bonus * bonus_bas = dynamic_cast<Bonus *> (bas->get_objet());
    bool bas_ok = bas->est_praticable() && !bas->est_en_feu() && (bas->get_objet() == NULL || bonus_bas);

    int num_choix = gauche_ok + droite_ok + haut_ok + bas_ok;

    if (num_choix == 0) return;

    // Si on as plusieurs choix on bloque la direction d'ou l'on vient
    if (num_choix > 1)
    {
        switch(_derniere_direction)
        {
        case HAUT:
            bas_ok = false; --num_choix;
            break;
        case BAS:
            haut_ok = false; --num_choix;
            break;
        case GAUCHE:
            droite_ok = false; --num_choix;
            break;
        case DROITE:
            gauche_ok = false; --num_choix;
            break;
        }
    }

    int choix = rand() % num_choix;

    if (gauche_ok)
    {
        if (choix == 0)
        {
            _derniere_direction = GAUCHE;
            bouger(GAUCHE);
            return;
        }
        --choix;
    }

    if (droite_ok)
    {
        if (choix == 0)
        {
            _derniere_direction = DROITE;
            bouger(DROITE);
            return;
        }
        --choix;
    }

    if (haut_ok)
    {
        if (choix == 0)
        {
            _derniere_direction = HAUT;
            bouger(HAUT);
            return;
        }
        --choix;
    }

    if (bas_ok)
    {
        if (choix == 0)
        {
            _derniere_direction = BAS;
            bouger(BAS);
            return;
        }
    }

    if(num_choix == 0)
    {
        return;
    }
    assert(false);
}

void Idiot::mise_a_jour()
{
    MobileIA::mise_a_jour();
    //
    //
    if(_coldown_att > 0)
        --_coldown_att;
    else
        attaquer_joueur();
}

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
}
