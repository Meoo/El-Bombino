/**
 * @file   Objet.cpp
 * @author Bastien Brunnenstein
 * @author Pascal-Pierre Sanchez-Carrion
 */

#include <moteur/Objet.hpp>
#include <moteur/Case.hpp>

Objet::Objet(Case * cse) :
        _case(NULL)
{
    set_case(cse);
}

Objet::~Objet()
{
    _case->set_objet(NULL);
}

Case * Objet::get_case()
{
    return _case;
}

const Case * Objet::get_case() const
{
    return _case;
}

void Objet::set_case(Case * cse)
{
    assert(cse != NULL);

    if (_case == cse) return;

    if (_case != NULL)
        _case->set_objet(NULL);

    _case = cse;
    cse->set_objet(this);
}

void Objet::mise_a_jour()
{
}
