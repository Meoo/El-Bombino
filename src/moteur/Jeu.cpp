/**
 * @file   Jeu.cpp
 * @author Bastien Brunnenstein
 * @author Pascal-Pierre Sanchez-Carrion
 */

#include <moteur/Jeu.hpp>
#include <moteur/Monde.hpp>

#include <vector>
#include <fstream>

Jeu Jeu::s_jeu;

Jeu::Jeu() :
        _mondes_count(0), _mondes(NULL), _monde_courant(NULL)
{
}

Jeu::~Jeu()
{
    liberer();
}

Jeu& Jeu::instance()
{
    return s_jeu;
}

void Jeu::charger()
{
    std::fstream fic((RC_FOLDER + RC_JEU).c_str(), std::ios_base::in);
    if (!fic)
    {
        // Exception : Impossible d'ouvrir le fichier
        assert(false && "Impossible d'ouvrir le fichier jeu");
    }
    fic.exceptions(std::ios_base::failbit | std::ios_base::badbit);
    fic >> std::skipws;

    std::string clef, valeur;
    std::vector<std::string> mondes;

    unsigned mode = 0;

    // Lire jusqu'à EOF
    LOG(std::string("Chargement du fichier de configuration : ") + RC_JEU);
    do
    {
        fic >> clef;
        if (clef == "MONDES")
            mode = 1;
        else if (clef == "TEXTURES")
            mode = 2;
        else
        {
            switch (mode)
            {
            case 1: // MONDES
                LOG(std::string("Monde : ") + clef);
                mondes.push_back(clef);
                break;

            case 2: // TEXTURES
                fic >> valeur;
                LOG(std::string("Texture : ") + clef + " -> " + valeur);
                _textures[clef].loadFromFile(RC_FOLDER + valeur);
                break;

            default: // ERREUR
                // Exception : Pas de mode
                assert(false);
                break;
            }
        }
    }
    while (!fic.eof());
    LOG("");

    fic.close();

    // Créer et initialiser les mondes
    _mondes_count = mondes.size();
    _mondes = new Monde*[_mondes_count];
    for (unsigned i = 0; i < _mondes_count; ++i)
        _mondes[i] = new Monde(mondes[i]);
}

void Jeu::liberer()
{
    for (unsigned i = 0; i < _mondes_count; ++i)
        delete _mondes[i];
    delete _mondes;
    _mondes_count = 0;
    _monde_courant = NULL;
}

const sf::Texture & Jeu::get_texture(const std::string & res) const
{
    if (_textures.count(res) > 0)
        return _textures.at(res);

    if (_monde_courant != NULL)
        return _monde_courant->get_texture(res);

    assert(false);
    return sf::Texture();
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

void Jeu::set_monde_courant(unsigned num)
{
    assert(num < _mondes_count);

    if (_monde_courant == _mondes[num])
        return;

    if (_monde_courant != NULL)
        _monde_courant->liberer();

    _monde_courant = _mondes[num];
    _monde_courant->charger();
}
