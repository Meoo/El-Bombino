/**
 * @file   Bonus.cpp
 * @author Bastien Brunnenstein
 * @author Pascal-Pierre Sanchez-Carrion
 */

#include <moteur/objets/Immobile.hpp>
#include <moteur/objets/Bonus.hpp>


Bonus::Bonus(Case* cse, sf::Sprite sprite) : Immobile(cse), _sprite(sprite)
{
}

Bonus::~Bonus()
{
}

void Bonus::mise_a_jour()
{
}
