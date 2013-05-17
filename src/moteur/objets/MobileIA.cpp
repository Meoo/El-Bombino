/**
 * @file   MobileIA.cpp
 * @author Bastien Brunnenstein
 * @author Pascal-Pierre Sanchez-Carrion
 */

#include <moteur/objets/MobileIA.hpp>
#include <moteur/objets/Soulevable.hpp>
#include <moteur/Jeu.hpp>

MobileIA::MobileIA(Case* cse, float vitesse, unsigned vies, const sf::Texture & texture)
    : Mobile(cse, vitesse), _vies(vies), _texture(texture), _protection(0), _clignote(false), _derniere_direction(nsUtil::ORIGINE)
{
    assert(vies > 0);
    _sprite.setOrigin(_texture.getSize().x / 2, _texture.getSize().y - _texture.getSize().x / 2);
    _sprite.setTexture(_texture);
    Jeu::instance().get_monde_courant().get_niveau_courant().ajouter_pnj(this);
}


MobileIA::~MobileIA()
{
    Jeu::instance().get_monde_courant().get_niveau_courant().delete_pnj(this);
}


void MobileIA::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    // Si l'IA est protégée contre les dégats, elle clignote
    _clignote = !_clignote;
    if (_protection > 0 && _clignote) return;

    if (get_objet_souleve() != NULL)
    {
        target.draw(*get_objet_souleve(), states);
        target.draw(_sprite, states);
    }
    else
        target.draw(_sprite, states);
}// draw()


void MobileIA::mise_a_jour()
{
    Mobile::mise_a_jour();

    if (!est_en_mouvement())
    {
        mise_a_jour_ia();
    }

    if (_protection > 0)
        --_protection;

    // TODO Gérer la direction
    _sprite.setPosition(get_position_ecran());
}// mise_a_jour()


void MobileIA::blesser()
{
    if (_protection == 0 && _vies > 0)
    {
        if (get_objet_souleve() != NULL && get_objet_souleve()->est_valide())
            get_objet_souleve()->blesser();

        --_vies;
        if (_vies == 0)
            detruire();
        else
            _protection = IA_PROTECTION;
    }
}// blesser()


void MobileIA::glacee()
{
    if (_protection == 0)
    {
        if (get_objet_souleve() != NULL && get_objet_souleve()->est_valide())
            get_objet_souleve()->glacee();

        if(get_vitesse() - BOMBE_GLACEE_DELTA > IA_VIT_MIN)
            set_vitesse(get_vitesse() - BOMBE_GLACEE_DELTA);
        else
            set_vitesse(IA_VIT_MIN);
        _protection = IA_PROTECTION;
    }
}


const unsigned MobileIA::get_vies() const
{
    return _vies;
}// get_vies()


unsigned MobileIA::get_vies()
{
    return _vies;
}// get_vies()


void MobileIA::set_vies(unsigned vies)
{
    assert(vies > 0);
    _vies = vies;
}// set_vies()


void MobileIA::appliquer_bonus(Bonus::bonus_t type_bonus)
{
    if(est_valide())
    {
        switch (type_bonus) {
             case Bonus::BONUS_BOMBE:
                 break;
             case Bonus::BONUS_PUISSANCE:
                 break;
             case Bonus::BONUS_VIE:
                 ++_vies;
                 break;
             case Bonus::BONUS_VITESSE:
                 if(get_vitesse()+IA_VIT_DELTA < IA_VIT_MAX)
                     set_vitesse(get_vitesse()+ IA_VIT_DELTA);
                 else
                     set_vitesse(IA_VIT_MAX);
                 break;
             case Bonus::MALUS_BOMBE:
                 break;
             case Bonus::MALUS_PUISSANCE:
                 break;
             case Bonus::MALUS_VITESSE:
                 if(get_vitesse() - IA_VIT_DELTA > IA_VIT_MIN)
                     set_vitesse(get_vitesse() - IA_VIT_DELTA);
                 else
                     set_vitesse(IA_VIT_MIN);
                 break;
             default:
                 break;
         }
    }
}// appliquer_bonus()

void MobileIA::deplacement_aleatoire()
{
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
        case nsUtil::ORIGINE: break;
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
}//deplacement_aleatoire()

sf::Sprite& MobileIA::get_sprite()
{
    return _sprite;
}//get_sprite()

// fin implementation class MobileIA

