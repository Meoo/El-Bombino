/**
 * @file   Niveau.cpp
 * @author Bastien Brunnenstein
 * @author Pascal-Pierre Sanchez-Carrion
 */

#include <moteur/exceptions/ExceptionRessource.hpp>
#include <moteur/Jeu.hpp>
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
    std::fstream fic((RC_FOLDER + _fichier_rc).c_str(), std::ios_base::in);
    if (!fic)
    throw ExceptionRessource(_fichier_rc,
    "Impossible d'ouvrir le fichier de configuration");

    fic.exceptions(std::ios_base::failbit | std::ios_base::badbit);
    fic >> std::skipws;


    fic >> _largeur;
    fic >> _hauteur;

    if (_largeur < 0 || _hauteur < 0)
    throw ExceptionRessource(_fichier_rc, "Largeur ou Longeur non compatible");

    _cases = new Case*[_largeur*_hauteur];
    // Lire jusqu'à EOF
    LOG(std::string("Chargement du fichier de configuration : ") + _fichier_rc);
    for(unsigned i = 0; i < _largeur * _hauteur && !fic.eof(); ++i)
    {
        char texture_case;
        fic >> texture_case;
        LOG(texture_case);
        switch (texture_case)
        {
            case 'M': // Mur
                _cases[i] = new Case (i % _largeur, i / _hauteur, Jeu::instance().get_texture("mur"));

                break;

            case '_': // Sol
                _cases[i] = new Case (i % _largeur, i / _hauteur, Jeu::instance().get_texture("sol"));

                break;

            case 'I': // Player
                _cases[i] = new Case (i % _largeur, i / _hauteur, Jeu::instance().get_texture("sol"));

                break;

            case 'C': // Caisse
                _cases[i] = new Case (i % _largeur, i / _hauteur, Jeu::instance().get_texture("sol"));

                break;

            case '0': // Enemis
                _cases[i] = new Case (i % _largeur, i / _hauteur, Jeu::instance().get_texture("mur"));

                break;

            case '1': // Enemis
                _cases[i] = new Case (i % _largeur, i / _hauteur, Jeu::instance().get_texture("mur"));

                break;

            default: // ERREUR
                throw ExceptionRessource(_fichier_rc,
                        "Le fichier est mal formé (pas de mode)");
        }
        fic >> std::ws;
    }
    fic >> std::ws;
    if (!fic.eof())
        throw ExceptionRessource(_fichier_rc, "Le fichier est mal formé");
    LOG("");
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
        target.draw(*_cases[i], states);
}

void Niveau::mise_a_jour()
{
    assert(_cases != NULL);

    for (unsigned i = 0; i < _largeur * _hauteur; ++i)
        _cases[i]->mise_a_jour();
}
