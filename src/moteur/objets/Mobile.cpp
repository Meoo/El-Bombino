/**
 * @file   Mobile.cpp
 * @author Bastien Brunnenstein
 * @author Pascal-Pierre Sanchez-Carrion
 */

#include <moteur/objets/Mobile.hpp>

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
