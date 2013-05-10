/**
 * @file   Objet.cpp
 * @author Bastien Brunnenstein
 * @author Pascal-Pierre Sanchez-Carrion
 */

#include <moteur/Objet.hpp>
#include <moteur/Case.hpp>

// Réservé pour Soulevable
Objet::Objet() :
        _case(NULL), _valide(true)
{
}


Objet::Objet(Case * cse) :
        _case(NULL), _valide(true)
{
    set_case(cse);
}


Objet::~Objet()
{
    if (_case != NULL && _case->get_objet() == this)
        _case->set_objet(NULL);
}


Case * Objet::get_case()
{
    return _case;
}// get_case()


const Case * Objet::get_case() const
{
    return _case;
}// get_case()


void Objet::set_case(Case * cse)
{
    assert(cse != NULL);

    if (_case == cse) return;

    if (_case != NULL)
        _case->set_objet(NULL);

    _case = cse;
    cse->set_objet(this);
}// set_case()


bool Objet::est_valide() const
{
    return _valide;
}// est_valide()


void Objet::mise_a_jour()
{
}// mise_a_jour()


void Objet::blesser()
{
    detruire();
}// blesser()


void Objet::laisser_tomber_objet(Case* cse)
{
}// laisser_tomber_objet()

void Objet::glacee()
{
}// glacee()

void Objet::detruire()
{
    _valide = false;
}// detruire()


// fin implementation class Objet
