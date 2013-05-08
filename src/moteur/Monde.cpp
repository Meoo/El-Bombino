/**
 * @file   Monde.cpp
 * @author Bastien Brunnenstein
 * @author Pascal-Pierre Sanchez-Carrion
 */

#include <moteur/Monde.hpp>
#include <moteur/Niveau.hpp>
#include <moteur/Usine.hpp>
#include <moteur/exceptions/ExceptionRessource.hpp>

#include <vector>
#include <fstream>
#include <cstdlib>

Monde::Monde(const std::string & fic) :
        _fichier_rc(fic), _niveaux_count(0), _niveaux(NULL), _niveau_courant(NULL), _num_niveau_courant(0)
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
    Tuile tuile;

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
        else if (clef == "CASES")
            mode = 3;
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

            case 3: // CASES
                if (clef.length() != 1)
                    throw ExceptionRessource(RC_JEU,
                            std::string("Identifiant de case invalide : ") + clef);
                fic >> std::ws;

                if (fic.eof())
                    throw ExceptionRessource(RC_JEU,
                            std::string("Pas assez d'arguments : ") + clef);
                fic >> tuile.classe_case >> std::ws;

                if (fic.eof())
                    throw ExceptionRessource(RC_JEU,
                            std::string("Pas assez d'arguments : ") + clef);
                fic >> tuile.texture_case >> std::ws;

                if (fic.eof())
                    throw ExceptionRessource(RC_JEU,
                            std::string("Pas assez d'arguments : ") + clef);
                fic >> tuile.classe_objet;

                _usine_cases[clef[0]] = tuile;
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
    /*
    if(_niveau_courant->est_fini() && _num_niveau_courant == _niveaux_count)
    {
        if(_num_niveau_courant + 1 == _niveaux_count)
        {
            // Monde fini
            _fini = true;
        }
        else
        {
            //Niveau fini
            //Jeu::instance().get_menu()->active_menu(Menu::NIVEAU_SUIVANT);
        }

    }
    */
}

Case * Monde::creer_case(unsigned x, unsigned y, char tuile) const
{
    const char err[] = {tuile, 0};
    if (_usine_cases.count(tuile) == 0)
        throw ExceptionRessource(err, "La tuile n'est pas enregistrée");

    const Tuile & tuile_dat = _usine_cases.at(tuile);

    Case * cse = Usine::creer_case(tuile_dat.classe_case, x, y, tuile_dat.texture_case);
    if (tuile_dat.classe_objet.compare("Vide") != 0)
        Usine::creer_objet(tuile_dat.classe_objet, cse);

    return cse;
}

const unsigned Monde::get_num_niveau_courant() const
{
    return _num_niveau_courant;
}

unsigned Monde::get_num_niveau_courant()
{
    return _num_niveau_courant;
}

bool Monde::est_fini()
{
    return _fini;
}

void Monde::set_niveau_courant(unsigned num)
{
    assert(_pret && num < _niveaux_count);

    if (_niveau_courant != NULL)
        _niveau_courant->liberer();

    _num_niveau_courant = num;
    _niveau_courant     = _niveaux[num];

    _niveau_courant->charger(this);
}
