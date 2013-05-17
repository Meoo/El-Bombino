/**
 * @file   Mobile.cpp
 * @author Bastien Brunnenstein
 * @author Pascal-Pierre Sanchez-Carrion
 */

#include <moteur/objets/Mobile.hpp>
#include <moteur/objets/Soulevable.hpp>
#include <moteur/Case.hpp>
#include <moteur/objets/Bonus.hpp>

Mobile::Mobile(Case * cse, float vitesse) :
        Objet(cse), _objet_souleve(NULL), _vitesse(vitesse), _direction(nsUtil::BAS), _bouge(
                false), _deplacement(0), _position_ecran(
                cse->get_x() * TILE_SIZE + TILE_SIZE / 2,
                cse->get_y() * TILE_SIZE + TILE_SIZE / 2), _change_case(false)
{
    assert(vitesse > 0);
}


Mobile::~Mobile()
{
    if (_objet_souleve != NULL)
        delete _objet_souleve;
}


Soulevable * Mobile::get_objet_souleve()
{
    return _objet_souleve;
}// get_objet_souleve()


const Soulevable * Mobile::get_objet_souleve() const
{
    return _objet_souleve;
}// get_objet_souleve()


void Mobile::bouger(nsUtil::direction_t dir, bool forcer)
{
    if (_bouge)
        return; // TODO assert?

    _direction = dir;

    Case * cse = NULL;
    switch (_direction)
    {
    case nsUtil::HAUT: cse = get_case()->get_case_haut(); break;
    case nsUtil::BAS: cse = get_case()->get_case_bas(); break;
    case nsUtil::GAUCHE: cse = get_case()->get_case_gauche(); break;
    case nsUtil::DROITE: cse = get_case()->get_case_droite(); break;
    case nsUtil::ORIGINE: return;
    }

    Soulevable * soul = dynamic_cast<Soulevable *> (cse->get_objet());
    if (forcer) _bouge = true;
    else if (cse->est_praticable() && soul == NULL)
    {
        _bouge = true;
    }
}// bouger()


bool Mobile::est_en_mouvement() const
{
    return _bouge;
}// est_en_mouvement()


float Mobile::get_vitesse() const
{
    return _vitesse;
}// get_vitesse()


void Mobile::set_vitesse(float vitesse)
{
    assert(vitesse > 0);
    _vitesse = vitesse;
}// set_vitesse()


nsUtil::direction_t Mobile::get_direction() const
{
    return _direction;
}// get_direction()


const sf::Vector2f & Mobile::get_position_ecran() const
{
    return _position_ecran;
}// get_position_ecran()


const sf::Vector2f Mobile::get_position_objet_souleve() const
{
    return get_position_ecran() + sf::Vector2f(0, -32);
}// get_position_objet_souleve()


void Mobile::mise_a_jour()
{
    if (_bouge)
    {
        if (_deplacement + _vitesse < TILE_SIZE)
        {
            _deplacement += _vitesse;

            // Bouger la position écran
            switch (_direction)
            {
            case nsUtil::HAUT: _position_ecran.y -= _vitesse; break;
            case nsUtil::BAS: _position_ecran.y += _vitesse; break;
            case nsUtil::GAUCHE: _position_ecran.x -= _vitesse; break;
            case nsUtil::DROITE: _position_ecran.x += _vitesse; break;
            case nsUtil::ORIGINE: break;
            }

            // Changer de case à la moitié du déplacement
            if (_deplacement >= TILE_SIZE / 2 && !_change_case)
            {
                _change_case = true;

                Case * cse = NULL;
                switch (_direction)
                {
                case nsUtil::HAUT: cse = get_case()->get_case_haut(); break;
                case nsUtil::BAS: cse = get_case()->get_case_bas(); break;
                case nsUtil::GAUCHE: cse = get_case()->get_case_gauche(); break;
                case nsUtil::DROITE: cse = get_case()->get_case_droite(); break;
                case nsUtil::ORIGINE: break;
                }

                Bonus * bonus = dynamic_cast<Bonus *> (cse->get_objet());
                Mobile * mobile = dynamic_cast<Mobile *> (cse->get_objet());

                if (cse->est_praticable() && cse->get_objet() == NULL)
                {
                    // C'est ok, on change de case
                    set_case(cse);
                }
                else if (cse->est_praticable() && bonus)
                {
                    bonus->utiliser(this);
                    _change_case = false;
                }
                else
                {
                    // Un objet est apparu entre temps, demi-tour!
                    switch (_direction)
                    {
                    case nsUtil::HAUT: _direction = nsUtil::BAS; break;
                    case nsUtil::BAS: _direction = nsUtil::HAUT; break;
                    case nsUtil::GAUCHE: _direction = nsUtil::DROITE; break;
                    case nsUtil::DROITE: _direction = nsUtil::GAUCHE; break;
                    case nsUtil::ORIGINE: break;
                    }

                    if (mobile)
                    {
                        // C'est un autre mobile! Ils se sont touchés!
                        toucher(mobile);
                        mobile->toucher(this);
                    }
                }
            }
        }
        else
        {
            // Fin du déplacement
            _position_ecran.x = get_case()->get_x() * TILE_SIZE + TILE_SIZE / 2;
            _position_ecran.y = get_case()->get_y() * TILE_SIZE + TILE_SIZE / 2;
            _bouge = false;
            _deplacement = 0;
            _change_case = false;
        }
    }

    if (_objet_souleve != NULL)
    {
        if (_objet_souleve->est_valide())
            _objet_souleve->mise_a_jour();

        // mise_a_jour peut enlever _objet_souleve
        if (_objet_souleve != NULL && !_objet_souleve->est_valide())
        {
            delete _objet_souleve;
            _objet_souleve = NULL;
        }
    }
}// mise_a_jour()


void Mobile::blesser()
{
    if (_objet_souleve != NULL && _objet_souleve->est_valide())
        _objet_souleve->blesser();

    detruire();
}// blesser()


void Mobile::glacee()
{

}// glacee()


void Mobile::appliquer_bonus(Bonus::bonus_t type_bonus)
{

}// appliquer_bonus()


bool Mobile::est_joueur()
{
    return false;
}// est_joueur()


void Mobile::toucher(Mobile* autre)
{
}// toucher()


// fin implementation class Mobile
