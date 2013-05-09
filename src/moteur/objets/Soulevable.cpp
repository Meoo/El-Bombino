/**
 * @file   Soulevable.cpp
 * @author Bastien Brunnenstein
 * @author Pascal-Pierre Sanchez-Carrion
 */

#include <moteur/objets/Soulevable.hpp>
#include <moteur/objets/Mobile.hpp>
#include <moteur/Case.hpp>

Soulevable::Soulevable(Case * cse) :
        Objet(cse), _porteur(NULL)
{
}


Soulevable::Soulevable(Mobile * porteur) :
        Objet(), _porteur(porteur)
{
    assert(porteur != NULL && porteur->_objet_souleve == NULL);
    porteur->_objet_souleve = this;
}


Soulevable::~Soulevable()
{
}


Mobile* Soulevable::get_porteur()
{
    return _porteur;
}// get_porteur()


const Mobile* Soulevable::get_porteur() const
{
    return _porteur;
}// get_porteur()


void Soulevable::set_porteur(Mobile * porteur)
{
    assert(porteur != NULL && porteur->_objet_souleve == NULL);

    if (_porteur == NULL)
    {
        assert(_case != NULL);

        // Détacher l'objet de la case
        _case->set_objet(NULL);
        _case = NULL;
    }
    else
        // Détacher l'objet du précédent porteur
        _porteur->_objet_souleve = NULL;

    // Attacher l'objet au porteur
    _porteur = porteur;
    porteur->_objet_souleve = this;
}// set_porteur()


void Soulevable::deposer(Case * cse)
{
    assert(_porteur != NULL && _case == NULL);

    // Rattacher l'objet à une case
    if(cse->est_praticable() && cse->get_objet() == NULL)
    {
        set_case(cse);
        _porteur->_objet_souleve = NULL;
        _porteur = NULL;
    }
}// deposer()


Case * Soulevable::get_case()
{
    if (_porteur != NULL)
        return _porteur->get_case();
    return _case;
}// get_case()


const Case * Soulevable::get_case() const
{
    if (_porteur != NULL)
        return _porteur->get_case();
    return _case;
}// get_case()


// fin implementation class Soulevable
