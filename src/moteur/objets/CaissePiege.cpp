/**
 * @file   CaissePiege.cpp
 * @author Bastien Brunnenstein
 * @author Pascal-Pierre Sanchez-Carrion
 */

#include <moteur/objets/CaissePiege.hpp>
#include <moteur/objets/Mobile.hpp>
#include <moteur/objets/Bombe.hpp>
#include <moteur/Jeu.hpp>
#include <moteur/Case.hpp>

CaissePiege::CaissePiege(Case * cse) :
        Caisse(cse), _explosive(true)
{
    get_sprite().setColor(sf::Color(254, 75, 0));
}


CaissePiege::~CaissePiege()
{
}


void CaissePiege::blesser()
{
    Soulevable::blesser();
    if(_explosive)
    {
        get_case()->enflammer_direction(nsUtil::BAS, 1);
        get_case()->enflammer_direction(nsUtil::DROITE, 1);
        get_case()->enflammer_direction(nsUtil::GAUCHE, 1);
        get_case()->enflammer_direction(nsUtil::HAUT, 1);
    }
}// blesser()


void CaissePiege::glacee()
{
    _explosive = false;
    get_sprite().setColor(sf::Color::Blue);
}// glacee()

void CaissePiege::laisser_tomber_objet(Case* cse)
{
    if(!_explosive)
    {
        Caisse::laisser_tomber_objet(cse);
    }
}// laisser_tomber_objet()



// fin implementation class CaissePiege


