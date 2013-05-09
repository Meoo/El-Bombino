/**
 * @file   Mur.cpp
 * @author Bastien Brunnenstein
 * @author Pascal-Pierre Sanchez-Carrion
 */

#include <moteur/Case.hpp>
#include <moteur/case/Mur.hpp>

Mur::Mur(unsigned x, unsigned y, const sf::Texture& texture): Case(x,y,texture)
{
}

Mur::~Mur()
{
}

bool Mur::est_praticable()
{
    return false;
}// est_praticable()


// fin impementation class Mur
