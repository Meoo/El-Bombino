/**
 * @file   Case.cpp
 * @author Bastien Brunnenstein
 * @author Pascal-Pierre Sanchez-Carrion
 */

#include <moteur/Case.hpp>

Case::Case(unsigned x, unsigned y) :
        _x(x), _y(y), _objet(NULL), _feu_duree(0), _texture(0)
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
    if (_objet != NULL)
        _objet->draw(target, states);
}

void Case::mise_a_jour()
{
    if (_objet != NULL)
        _objet->mise_a_jour();
}
