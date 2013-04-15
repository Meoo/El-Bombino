/**
 * @file   Monde.cpp
 * @author Bastien Brunnenstein
 * @author Pascal-Pierre Sanchez-Carrion
 */

#include <moteur/Monde.hpp>
#include <moteur/Niveau.hpp>
#include <moteur/exceptions/ExceptionRessource.hpp>

#include <vector>
#include <fstream>
#include <cstdlib>

Monde::Monde(const std::string & fic) :
        _fichier_rc(fic), _niveaux_count(0), _niveaux(NULL), _niveau_courant(NULL)
#ifndef NDEBUG
        , _pret(false)
#endif
{
}

Monde::~Monde()
{
    liberer();
}

Niveau & Monde::get_niveau_courant()
{
    assert(_niveau_courant != NULL);
    return *_niveau_courant;
}

const Niveau & Monde::get_niveau_courant() const
{
    assert(_niveau_courant != NULL);
    return *_niveau_courant;
}

void Monde::charger()
{
    assert(!_pret);

    std::fstream fic((RC_FOLDER + _fichier_rc).c_str(), std::ios_base::in);
    if (!fic)
        throw ExceptionRessource(_fichier_rc,
                "Impossible d'ouvrir le fichier de configuration");

    fic.exceptions(std::ios_base::failbit | std::ios_base::badbit);
    fic >> std::skipws;

    std::string clef, valeur;
    std::vector<std::string> niveaux;
    sf::Texture text;

    unsigned mode = 0;

    // Lire jusqu'à EOF
    LOG(std::string("Chargement du fichier de configuration : ") + _fichier_rc);
    do
    {
        fic >> clef;
        if (clef == "NIVEAUX")
            mode = 1;
        else if (clef == "TEXTURES")
            mode = 2;
        else
        {
            switch (mode)
            {
            case 1: // NIVEAUX
                LOG(std::string("Niveau : ") + clef);
                niveaux.push_back(clef);
                break;

            case 2: // TEXTURES
                fic >> std::ws;
                if (fic.eof())
                    throw ExceptionRessource(RC_JEU,
                            std::string("Pas de valeur pour la texture : ")
                                    + clef);
                fic >> valeur;

                // Charger la texture
                text.loadFromFile(RC_FOLDER + valeur);
                _textures[clef].push_back(text);
                break;

            default: // ERREUR
                throw ExceptionRessource(_fichier_rc, "Le fichier est mal formé (pas de mode)");
            }
        }
        fic >> std::ws;
    }
    while (!fic.eof());
    LOG("");

    // Créer et initialiser les niveaux
    _niveaux_count = niveaux.size();
    _niveaux = new Niveau *[_niveaux_count];
    for (unsigned i = 0; i < _niveaux_count; ++i)
        _niveaux[i] = new Niveau(niveaux[i]);

#ifndef NDEBUG
    _pret = true;
#endif
}

void Monde::liberer()
{
    for (unsigned i = 0; i < _niveaux_count; ++i)
        delete _niveaux[i];
    delete _niveaux;
    _niveaux = NULL;
    _niveaux_count = 0;
    _niveau_courant = NULL;

    _textures.clear();

#ifndef NDEBUG
    _pret = false;
#endif
}

bool Monde::has_texture(const std::string & res) const
{
    assert(_pret);

    return _textures.count(res) > 0;
}

const sf::Texture & Monde::get_texture(const std::string & res) const
{
    assert(_pret);

    if (_textures.count(res) > 0)
    {
        const std::vector<sf::Texture> & vec = _textures.at(res);
        return vec.at(rand() % vec.size());
    }

    throw ExceptionRessource(res, "La ressource demandée n'existe pas");
}

void Monde::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    assert(_pret && _niveau_courant != NULL);

    target.draw(*_niveau_courant, states);
}

void Monde::mise_a_jour()
{
    assert(_pret && _niveau_courant != NULL);

    _niveau_courant->mise_a_jour();
}

void Monde::set_niveau_courant(unsigned num)
{
    assert(_pret && num < _niveaux_count);

    if (_niveau_courant != NULL)
        _niveau_courant->liberer();

    _niveau_courant = _niveaux[num];
    _niveau_courant->charger();
}
