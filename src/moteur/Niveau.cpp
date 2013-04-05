/**
 * @file   Niveau.cpp
 * @author Bastien Brunnenstein
 * @author Pascal-Pierre Sanchez-Carrion
 */

#include <moteur/Niveau.hpp>
#include <moteur/Case.hpp>

#include <fstream>

Niveau::Niveau(const std::string & fic) :
        _fichier_rc(fic), _largeur(0), _hauteur(0), _cases(NULL)
{
}

Niveau::~Niveau()
{
    liberer();
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

    for (unsigned i = 0; i < _largeur * _hauteur; ++i)
        _cases[i]->draw(target, states);
}

void Niveau::mise_a_jour()
{
    assert(_cases != NULL);

    for (unsigned i = 0; i < _largeur * _hauteur; ++i)
        _cases[i]->mise_a_jour();
}
