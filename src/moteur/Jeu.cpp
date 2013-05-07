/**
 * @file   Jeu.cpp
 * @author Bastien Brunnenstein
 * @author Pascal-Pierre Sanchez-Carrion
 */

#include <moteur/Jeu.hpp>
#include <moteur/Monde.hpp>
#include <moteur/exceptions/ExceptionRessource.hpp>
#include <moteur/Menu.hpp>

#include <vector>
#include <fstream>

Jeu Jeu::s_jeu;

Jeu::Jeu() :
        _mondes_count(0), _mondes(NULL), _monde_courant(NULL), _menu(NULL)
#ifndef NDEBUG
        , _pret(false)
#endif
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
    assert(!_pret);

    _default_font.loadFromFile("C:/Windows/Fonts/arial.ttf");

    _menu = new Menu();

    std::fstream fic((RC_FOLDER + RC_JEU).c_str(), std::ios_base::in);
    if (!fic)
        throw ExceptionRessource(RC_JEU,
                "Impossible d'ouvrir le fichier de configuration");

    fic.exceptions(std::ios_base::failbit | std::ios_base::badbit);
    fic >> std::skipws;

    std::string clef, valeur;
    std::vector<std::string> mondes;
    unsigned mode = 0;
    sf::Texture text;

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
                fic >> std::ws;
                if (fic.eof())
                    throw ExceptionRessource(RC_JEU,
                            std::string("Pas de valeur pour la texture : ")
                                    + clef);
                fic >> valeur;
                LOG(std::string("Texture : ") + clef + " -> " + valeur);

                // Charger la texture
                text.loadFromFile(RC_FOLDER + valeur);
                _textures[clef].push_back(text);
                break;

            default: // ERREUR
                throw ExceptionRessource(RC_JEU,
                        "Le fichier est mal formé (pas de mode)");
            }
        }
        fic >> std::ws;
    }
    while (!fic.eof());
    LOG("");

    fic.close();

    // Créer et initialiser les mondes
    _mondes_count = mondes.size();
    _mondes = new Monde*[_mondes_count];
    for (unsigned i = 0; i < _mondes_count; ++i)
        _mondes[i] = new Monde(mondes[i]);

    // TODO : Charger la sauvegarde

#ifndef NDEBUG
    _pret = true;
#endif
}

void Jeu::liberer()
{
    delete _menu;
    for (unsigned i = 0; i < _mondes_count; ++i)
        delete _mondes[i];
    delete _mondes;
    _menu = NULL;
    _mondes = NULL;
    _mondes_count = 0;
    _monde_courant = NULL;

    _textures.clear();

#ifndef NDEBUG
    _pret = false;
#endif
}

const sf::Texture & Jeu::get_texture(const std::string & res) const
{
    assert(_pret);

    if (_monde_courant != NULL && _monde_courant->has_texture(res))
        return _monde_courant->get_texture(res);

    if (_textures.count(res) > 0)
    {
        const std::vector<sf::Texture> & vec = _textures.at(res);
        return vec.at(rand() % vec.size());
    }

    throw ExceptionRessource(res, "La ressource demandée n'existe pas");
}

Monde & Jeu::get_monde_courant()
{
    assert(_pret && _monde_courant != NULL);

    return *_monde_courant;
}

const Monde & Jeu::get_monde_courant() const
{
    assert(_pret && _monde_courant != NULL);

    return *_monde_courant;
}

void Jeu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    assert(_pret && (_monde_courant != NULL || _menu != NULL));
    if(_menu)
        target.draw(*_menu,states);
    else
        target.draw(*_monde_courant, states);

}

void Jeu::mise_a_jour()
{
    assert(_pret && (_monde_courant != NULL || _menu != NULL));
    if(!_menu)
    {
        _monde_courant->mise_a_jour();
    }
}

const sf::Font& Jeu::get_default_font() const
{
    assert(_pret);

    return _default_font;
}

void Jeu::clic(int x, int y)
{
    assert(_pret && _menu);

    if(_menu)
        _menu->clic(x,y);
}

void Jeu::set_menu(Menu * value)
{
    assert(_pret);

    _menu = value;
}

void Jeu::set_monde_courant(unsigned num)
{
    assert(_pret && num < _mondes_count);

    if (_monde_courant != NULL)
        _monde_courant->liberer();

    _monde_courant = _mondes[num];
    _monde_courant->charger();
}
