/*
 * Soulevable.cpp
 *
 *  Created on: 4 avr. 2013
 *      Author: Sanpas
 */




#include <objets/Soulevable.hpp>

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
