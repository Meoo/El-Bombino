/*
 * Mobile.cpp
 *
 *  Created on: 4 avr. 2013
 *      Author: Sanpas
 */




#include <objets/Mobile.hpp>


Mobile::Mobile(): _objet_souleve(NULL)
{
}

Mobile::~Mobile()
{
}

Soulevable* Mobile::get_objet_souleve()
{
    return _objet_souleve;
}

void Mobile::mise_a_jour()
{
}
