/**
 * @file   Vide.cpp
 * @author Bastien Brunnenstein
 * @author Pascal-Pierre Sanchez-Carrion
 */

#include <moteur/Case.hpp>
#include <moteur/case/Vide.hpp>


Vide::Vide(unsigned x, unsigned y, const sf::Texture& texture): Case(x,y,texture)
{
}

Vide::~Vide()
{
}

bool Vide::est_praticable()
{
    return false;
}// est_praticable()


// fin implementation class Vide
