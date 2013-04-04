/*
 * Niveau.cpp
 *
 *  Created on: 4 avr. 2013
 *      Author: Sanpas
 */


#include <moteur/Niveau.hpp>

Niveau::Niveau(const std::string & fic): _largeur(0), _hauteur(0), _cases(NULL), _fichier_rc(fic)
{
}

Niveau::~Niveau()
{
}

void Niveau::charger()
{
    std::ifstream fic;

    fic.open((RC_FOLDER + _fichier_rc).c_str());

    // TODO Lire le fichier

    fic.close();
}

void Niveau::liberer()
{
}

void Niveau::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    assert(_cases != NULL);

    for(unsigned i = 0; i < _largeur*_hauteur; ++i)
        _cases[i]->draw(target, states);
}

void Niveau::mise_a_jour()
{
    assert(_cases != NULL);

    for(unsigned i = 0; i < _largeur*_hauteur; ++i)
         _cases[i]->mise_a_jour();
}
