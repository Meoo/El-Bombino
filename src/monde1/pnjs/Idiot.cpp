/**
 * @file   Idiot.cpp
 * @author Bastien Brunnenstein
 */

#include <monde1/pnjs/Idiot.hpp>
#include <moteur/Jeu.hpp>
#include <moteur/Case.hpp>
#include <moteur/objets/Bonus.hpp>


#include <vector>

Idiot::Idiot(Case * cse) : MobileIA(cse, 1.f, 2, Jeu::instance().get_texture("idiot")), _derniere_direction((Direction) -1)
{
}

Idiot::~Idiot()
{
}

void Idiot::mise_a_jour_ia()
{
    Case * gauche = get_case()->get_case_gauche();
    Bonus *bonus_gauche = dynamic_cast<Bonus *> (gauche->get_objet());
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

