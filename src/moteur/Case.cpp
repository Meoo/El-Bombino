/**
 * @file   Case.cpp
 * @author Bastien Brunnenstein
 * @author Pascal-Pierre Sanchez-Carrion
 */

#include <moteur/Case.hpp>
#include <moteur/Objet.hpp>

Case::Case(unsigned x, unsigned y, const sf::Texture & texture) :
        _objet(NULL), _texture(&texture), _feu_duree(0), _x(x), _y(y)
{
}

Case::~Case()
{
}

Objet * Case::get_objet()
{
    return _objet;
}

const Objet * Case::get_objet() const
{
    return _objet;
}


bool Case::enflammer(unsigned duree, const sf::Color& couleur)
{
    if (_feu_duree > duree)
        return true;

    _feu_duree = duree;
    _feu_couleur = couleur;

    // TODO Brûler objet

    return true;
}

bool Case::est_en_feu() const
{
    return _feu_duree > 0;
}

unsigned Case::get_duree_flammes() const
{
    return _feu_duree;
}

bool Case::est_praticable()
{
    return true;
}

void Case::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    sf::Sprite sprite(*_texture);
    sprite.setPosition(_x * TILE_SIZE, _y * TILE_SIZE);
    sprite.setOrigin(0, 0);
    target.draw(sprite, states);

    if (_objet != NULL)
        target.draw(*_objet, states);
}

void Case::set_objet(Objet& objet)
{
    assert(_objet == NULL);

    _objet = &obj;
}

const unsigned Case::get_x() const
{
    return _x;
}

const unsigned Case::get_y() const
{
    return _y;
}

void Case::mise_a_jour()
{
    if (_objet != NULL)
        _objet->mise_a_jour();
}
