/**
 * @file   Mobile.cpp
 * @author Bastien Brunnenstein
 * @author Pascal-Pierre Sanchez-Carrion
 */

#include <moteur/objets/Mobile.hpp>
#include <moteur/objets/Soulevable.hpp>

Mobile::Mobile(Case * cse) :
        Objet(cse), _objet_souleve(NULL)
{
}

Mobile::~Mobile()
{
    if (_objet_souleve != NULL)
        delete _objet_souleve;
}

Soulevable* Mobile::get_objet_souleve()
{
    return _objet_souleve;
}

void Mobile::mise_a_jour()
{
    if (_objet_souleve != NULL)
        _objet_souleve->mise_a_jour();
}
