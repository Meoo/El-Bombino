/**
 * @file   Soulevable.cpp
 * @author Bastien Brunnenstein
 * @author Pascal-Pierre Sanchez-Carrion
 */

#include <moteur/objets/Soulevable.hpp>

Soulevable::Soulevable(): _porteur(NULL)
{
}

Soulevable::~Soulevable()
{
}

Mobile* Soulevable::get_poteur()
{
    return _porteur;
}

void Soulevable::souleve()
{
}

void Soulevable::mise_a_jour()
{
}
