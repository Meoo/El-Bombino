/**
 * @file   Soulevable.cpp
 * @author Bastien Brunnenstein
 * @author Pascal-Pierre Sanchez-Carrion
 */

#include <moteur/objets/Soulevable.hpp>

Soulevable::Soulevable(Case * cse) :
        Objet(cse), _porteur(NULL)
{
}

Soulevable::~Soulevable()
{
}

Mobile* Soulevable::get_poteur()
{
    return _porteur;
}
