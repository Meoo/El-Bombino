/**
 * @file   Jeu.cpp
 * @author Bastien Brunnenstein
 */

#include <moteur/Jeu.hpp>
#include <moteur/Monde.hpp>

Jeu::Jeu() : _monde_courant(NULL)
{
    _mondes = new Monde* [MONDES_COUNT];

    // Créer les mondes
    _mondes[0] = new Monde("monde1.txt");
    _mondes[1] = new Monde("monde2.txt");
    _mondes[2] = new Monde("monde3.txt");

    set_monde_courant(0);
}

Jeu::~Jeu()
{
    delete[] _mondes;
}

Jeu& Jeu::instance()
{
    return s_jeu;
}

const sf::Texture * Jeu::get_texture(const std::string & res) const
{
    return NULL;
}

void Jeu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    assert(_monde_courant != NULL);

    _monde_courant->draw(target, states);
}

void Jeu::mise_a_jour()
{
    assert(_monde_courant != NULL);

    _monde_courant->mise_a_jour();
}

Monde* Jeu::get_monde_courant()
{
    assert(_monde_courant != NULL);

    return _monde_courant;
}

const Monde* Jeu::get_monde_courant() const
{
    assert(_monde_courant != NULL);

    return _monde_courant;
}

void Jeu::set_monde_courant(unsigned num)
{
    assert(num < MONDES_COUNT);

    if (_monde_courant != NULL)
        _monde_courant->liberer();

    _monde_courant = _mondes[num];
    _monde_courant->charger();
}
