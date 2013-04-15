/**
 * @file   Mobile.cpp
 * @author Bastien Brunnenstein
 * @author Pascal-Pierre Sanchez-Carrion
 */

#include <moteur/objets/Mobile.hpp>
#include <moteur/objets/Soulevable.hpp>
#include <moteur/Case.hpp>

Mobile::Mobile(Case * cse, float vitesse) :
        Objet(cse), _objet_souleve(NULL), _vitesse(vitesse), _direction(BAS), _bouge(
                false), _deplacement(0), _position_ecran(
                cse->get_x() * TILE_SIZE + TILE_SIZE / 2,
                cse->get_y() * TILE_SIZE + TILE_SIZE / 2)
{
    assert(vitesse > 0);
}

Mobile::~Mobile()
{
    if (_objet_souleve != NULL) delete _objet_souleve;
}

Soulevable * Mobile::get_objet_souleve()
{
    return _objet_souleve;
}

const Soulevable * Mobile::get_objet_souleve() const
{
    return _objet_souleve;
}

void Mobile::bouger(Direction dir)
{
    if (_bouge) return; // TODO assert?

    // TODO Détecter les murs

    _direction = dir;

    Case * cse = NULL;
    switch (_direction)
    {
    case HAUT:
        cse = get_case()->get_case_haut();
        break;

    case BAS:
        cse = get_case()->get_case_bas();
        break;

    case GAUCHE:
        cse = get_case()->get_case_gauche();
        break;

    case DROITE:
        cse = get_case()->get_case_droite();
        break;
    }

    if (cse->est_praticable() && cse->get_objet() == NULL)
    {
        set_case(cse);
        _bouge = true;
    }
}

float Mobile::get_vitesse() const
{
    return _vitesse;
}

void Mobile::set_vitesse(float vitesse)
{
    assert(vitesse > 0);
    _vitesse = vitesse;
}

Mobile::Direction Mobile::get_direction() const
{
    return _direction;
}

const sf::Vector2f & Mobile::get_position_ecran() const
{
    return _position_ecran;
}

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
            case HAUT:
                _position_ecran.y -= _vitesse;
                break;

            case BAS:
                _position_ecran.y += _vitesse;
                break;

            case GAUCHE:
                _position_ecran.x -= _vitesse;
                break;

            case DROITE:
                _position_ecran.x += _vitesse;
                break;
            }
        }
        else
        {
            // Fin du déplacement
            _position_ecran.x = get_case()->get_x() * TILE_SIZE + TILE_SIZE / 2;
            _position_ecran.y = get_case()->get_y() * TILE_SIZE + TILE_SIZE / 2;
            _bouge = false;
            _deplacement = 0;
        }
    }

    if (_objet_souleve != NULL) _objet_souleve->mise_a_jour();
}
