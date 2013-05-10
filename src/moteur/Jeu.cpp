/**
 * @file   Jeu.cpp
 * @author Bastien Brunnenstein
 * @author Pascal-Pierre Sanchez-Carrion
 */

#include <moteur/Jeu.hpp>
#include <moteur/Monde.hpp>
#include <moteur/exceptions/ExceptionRessource.hpp>
#include <moteur/Menu.hpp>
#include <moteur/objets/Joueur.hpp>

#include <vector>
#include <fstream>

Jeu Jeu::s_jeu;

Jeu::Jeu() :
        _mondes_count(0), _mondes(NULL), _monde_courant(NULL), _menu(NULL), _num_monde_courant(0),
        _vitesse_joueur(JOUEUR_VIT_DEFAULT),  _nb_bombe_joueur(JOUEUR_NB_BOMBES_DEFAULT), _puissance_joueur(BOMBE_POWER_DEFAULT),
        _vie_joueur(JOUEUR_VIE_DEFAULT),  _bonus_soulevable_joueur(false),  _bonus_bombe_special_joueur(false)
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
}// instance()


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
}// charger()


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
}// liberer()


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
}// get_texture()


Monde & Jeu::get_monde_courant()
{
    assert(_pret && _monde_courant != NULL);

    return *_monde_courant;
}// get_monde_courant()


const Monde & Jeu::get_monde_courant() const
{
    assert(_pret && _monde_courant != NULL);

    return *_monde_courant;
}// get_monde_courant()


void Jeu::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    assert(_pret && (_monde_courant != NULL || _menu != NULL));

    switch (_menu->get_menu_type()) {
        case Menu::MENU_PAUSE:
            target.draw(*_monde_courant, states);
            target.draw(*_menu, states);
            break;
        case Menu::NIVEAU_SUIVANT:
            target.draw(*_monde_courant, states);
            target.draw(*_menu, states);
            break;
        case Menu::MONDE_SUIVANT:
            target.draw(*_monde_courant, states);
            target.draw(*_menu, states);
            break;
        case Menu::AUCUN_MENU:
            target.draw(*_monde_courant);
            break;
        case Menu::GAME_OVER:
            target.draw(*_monde_courant);
            target.draw(*_menu, states);
            break;
        default:
            target.draw(*_menu, states);
            break;
    }

}// draw()


void Jeu::mise_a_jour()
{
    assert(_pret && (_monde_courant != NULL || _menu != NULL));
    if(_menu->get_menu_type() == Menu::AUCUN_MENU)
    {
        _monde_courant->mise_a_jour();
        if(_monde_courant->est_fini())
        {
            if(_num_monde_courant + 1 == _mondes_count)
            {
                //Jeu Fini #TODO
                _menu->active_menu(Menu::JEU_FINI);
            }
            else
            {
                //Monde suivant #TODO
                _menu->active_menu(Menu::MONDE_SUIVANT);
            }

        }
    }
    else
        _menu->mise_a_jour();
}// mise_a_jour()


const sf::Font& Jeu::get_default_font() const
{
    //assert (_pret);

    return _default_font;
}// get_default_font()


void Jeu::clic(int x, int y)
{
    assert(_pret && (_menu));

    if(_menu)
        _menu->clic(x,y);
}// clic()


void Jeu::lost_focus()
{
    assert(_pret && _menu);

    _menu->lost_focus();
}// lost_focus()


void Jeu::press_pause()
{
    assert(_pret && _menu);

    _menu->press_pause();
}// press_pause()


const float Jeu::get_vitesse_joueur() const
{
    return _vitesse_joueur;
}// get_vitesse_joueur()


float Jeu::get_vitesse_joueur()
{
    return _vitesse_joueur;
}// get_vitesse_joueur()


const unsigned Jeu::get_nb_bombe_joueur() const
{
    return _nb_bombe_joueur;
}// get_nb_bombe_joueur()


unsigned Jeu::get_nb_bombe_joueur()
{
    return _nb_bombe_joueur;
}// get_nb_bombe_joueur()


const unsigned Jeu::get_puissance_joueur() const
{
    return _puissance_joueur;
}// get_puissance_joueur()


unsigned Jeu::get_puissance_joueur()
{
    return _puissance_joueur;
}// get_puissance_joueur()


const unsigned Jeu::get_vie_joueur() const
{
    return _vie_joueur;
}// get_vie_joueur()


unsigned Jeu::get_vie_joueur()
{
    return _vie_joueur;
}// get_vie_joueur()


const bool Jeu::get_bonus_soulevable_joueur() const
{
    return _bonus_soulevable_joueur;
}// get_bonus_soulevable_joueur()


bool Jeu::get_bonus_soulevable_joueur()
{
    return _bonus_soulevable_joueur;
}// get_bonus_soulevable_joueur()


const bool Jeu::get_bonus_bombe_special_joueur() const
{
    return _bonus_bombe_special_joueur;
}// get_bonus_bombe_special_joueur()


bool Jeu::get_bonus_bombe_special_joueur()
{
    return _bonus_bombe_special_joueur;
}// get_bonus_bombe_special_joueur()

void Jeu::press_touch(sf::Event::KeyEvent key)
{
    assert(_pret && _menu);

    _menu->press_touch(key);
}// press_touch()

void Jeu::set_monde_courant(unsigned num)
{
    assert(_pret && num < _mondes_count);

    if (_monde_courant != NULL)
        _monde_courant->liberer();

    _num_monde_courant = num;
    _monde_courant = _mondes[num];
    _monde_courant->charger();
}// set_monde_courant()


const unsigned Jeu::get_num_monde_courant() const
{
    return _num_monde_courant;
}// get_num_monde_courant()


unsigned Jeu::get_num_monde_courant()
{
    return _num_monde_courant;
}// get_num_monde_courant()


const Menu * Jeu::get_menu() const
{
    return _menu;
}// get_menu()


Menu * Jeu::get_menu()
{
    return _menu;
}// get_menu()


void    Jeu::sauve_donnees_joueur()
{
    _vitesse_joueur     =   _monde_courant->get_niveau_courant().get_joueur()->get_vitesse();
    _vie_joueur         =   _monde_courant->get_niveau_courant().get_joueur()->get_vie();
    _nb_bombe_joueur    =   _monde_courant->get_niveau_courant().get_joueur()->get_nb_bombe_simultanee();
    _puissance_joueur   =   _monde_courant->get_niveau_courant().get_joueur()->get_puissance_bombe();
    _bonus_bombe_special_joueur =    _monde_courant->get_niveau_courant().get_joueur()->get_bonus_bombe_spe();
    _bonus_soulevable_joueur    =    _monde_courant->get_niveau_courant().get_joueur()->get_bonus_soulevable();
}// sauve_donnees_joueur()


void   Jeu::charger_donnees_joueur(float vitesse_joueur, unsigned nb_bombe_joueur,
                                   unsigned puissance_joueur, unsigned vie_joueur,
                                   bool bonus_soulevable_joueur, bool  bonus_bombe_special_joueur)
{
    _vie_joueur         = vitesse_joueur;
    _nb_bombe_joueur    = nb_bombe_joueur;
    _puissance_joueur   = puissance_joueur;
    _vie_joueur         = vie_joueur;
    _bonus_bombe_special_joueur     = bonus_bombe_special_joueur;
    _bonus_soulevable_joueur        = bonus_soulevable_joueur;
}// charger_donnees_joueur()


void        Jeu::set_num_monde_courant(unsigned num)
{
    _num_monde_courant = num;
}// set_num_monde_courant()


// fin implementation class Jeu
