/**
 * @file   Monde.cpp
 * @author Bastien Brunnenstein
 * @author Pascal-Pierre Sanchez-Carrion
 */

#include <moteur/Monde.hpp>
#include <moteur/Niveau.hpp>

#include <fstream>

Monde::Monde(const std::string & fic) :
        _fichier_rc(fic), _niveaux_count(0), _niveaux(NULL), _niveau_courant(NULL)
{
}

Monde::~Monde()
{
    liberer();
}

Niveau* Monde::get_niveau_courant()
{
    assert(_niveau_courant != NULL);
    return _niveau_courant;
}

const Niveau* Monde::get_niveau_courant() const
{
    assert(_niveau_courant != NULL);
    return _niveau_courant;
}

void Monde::charger()
{
    std::ifstream fic;

    fic.open((RC_FOLDER + _fichier_rc).c_str());

    // TODO Lire le fichier

    fic.close();
}

void Monde::liberer()
{
}

const sf::Texture & Monde::get_texture(const std::string & res) const
{
    assert(false);
    return sf::Texture();
}

void Monde::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    assert(_niveau_courant != NULL);
    _niveau_courant->draw(target, states);
}

void Monde::mise_a_jour()
{
    assert(_niveau_courant != NULL);
    _niveau_courant->mise_a_jour();
}

void Monde::set_niveau_courant(unsigned num)
{
    assert(num < _niveaux_count);

    if (_niveau_courant == _niveaux[num])
        return;

    if (_niveau_courant != NULL)
        _niveau_courant->liberer();

    _niveau_courant = _niveaux[num];
    _niveau_courant->charger();
}
