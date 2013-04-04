/**
 * @file   Monde.cpp
 * @author Bastien Brunnenstein
 */

#include <moteur/Monde.hpp>
#include <moteur/Niveau.hpp>

#include <fstream>

Monde::Monde(const std::string & fic) : _niveau_courant(NULL), _niveaux(NULL), _niveaux_count(0), _fichier_rc(fic)
{
}

Monde::~Monde()
{
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

const sf::Texture* Monde::get_texture(const std::string & res) const
{
    return NULL;
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

    if (_niveau_courant == _niveaux[num]) return;

    if (_niveau_courant != NULL)
        _niveau_courant->liberer();

    _niveau_courant = _niveaux[num];
    _niveau_courant->charger();
}
