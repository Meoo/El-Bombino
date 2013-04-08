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
    std::fstream fic((RC_FOLDER + _fichier_rc).c_str(), std::ios_base::in);
    if (!fic)
    {
        // Exception : Impossible d'ouvrir le fichier
        assert(false && new std::string("Impossible d'ouvrir le fichier monde " + _fichier_rc));
    }
    fic.exceptions(std::ios_base::failbit | std::ios_base::badbit);
    fic >> std::skipws;

    std::string clef, valeur;
    std::vector<std::string> niveaux;

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

    // Créer et initialiser les niveaux
    _niveaux_count = niveaux.size();
    _niveaux = new Niveau *[_niveaux_count];
    for (unsigned i = 0; i < _niveaux_count; ++i)
        _niveaux[i] = new Niveau(niveaux[i]);
    fic.close();
}

void Monde::liberer()
{
    for (unsigned i = 0; i < _niveaux_count; ++i)
       delete _niveaux[i];
   delete _niveaux;
   _niveaux_count = 0;
   _niveau_courant = NULL;
}

const sf::Texture & Monde::get_texture(const std::string & res) const
{
    if (_textures.count(res) > 0)
        return _textures.at(res);

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
