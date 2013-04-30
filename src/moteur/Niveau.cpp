/**
 * @file   Niveau.cpp
 * @author Bastien Brunnenstein
 * @author Pascal-Pierre Sanchez-Carrion
 */

#include <moteur/Niveau.hpp>
#include <moteur/exceptions/ExceptionRessource.hpp>
#include <moteur/Jeu.hpp>
#include <moteur/Monde.hpp>
#include <moteur/Case.hpp>
#include <moteur/objets/Joueur.hpp>
#include <moteur/objets/MobileIA.hpp>
#include <moteur/objets/Bombe.hpp>

#include <fstream>

Niveau::Niveau(const std::string & fic) :
        _fichier_rc(fic), _largeur(0), _hauteur(0), _cases(NULL), _joueur(NULL)
#ifndef NDEBUG
        , _pret(false)
#endif
{
}

Niveau::~Niveau()
{
    liberer();
}

void Niveau::charger(const Monde * parent)
{
    assert(!_pret);

    std::fstream fic((RC_FOLDER + _fichier_rc).c_str(), std::ios_base::in);
    if (!fic)
        throw ExceptionRessource(_fichier_rc,
                "Impossible d'ouvrir le fichier de configuration");

    fic.exceptions(std::ios_base::failbit | std::ios_base::badbit);
    fic >> std::skipws;

    fic >> _largeur;
    fic >> _hauteur;

    if (_largeur <= 0 || _hauteur <= 0)
        throw ExceptionRessource(_fichier_rc, "Largeur ou heuteur incorrecte");

    _cases = new Case* [_largeur * _hauteur];

    // Lire toutes les cases
    LOG(std::string("Chargement du fichier de configuration : ") + _fichier_rc);
    for (unsigned i = 0; i < _largeur * _hauteur && !fic.eof(); ++i)
    {
        char texture_case;
        fic >> texture_case;
        _cases[i] = parent->creer_case(i % _largeur, i / _largeur, texture_case);
    }

    // Vérifier que le fichier soit vide
    fic >> std::ws;
    if (!fic.eof())
        throw ExceptionRessource(_fichier_rc, "Le fichier est mal formé");
    LOG("");

    fic.close();

#ifndef NDEBUG
    _pret = true;
#endif
}

void Niveau::liberer()
{
    for (unsigned i = 0; i < _largeur * _hauteur; ++i)
        delete _cases[i];
    delete _cases;
    _cases = NULL;
    _largeur = 0;
    _hauteur = 0;
    _pnjs.clear();

#ifndef NDEBUG
    _pret = false;
#endif
}

void Niveau::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    assert(_pret);

    target.setView(sf::View(
                    sf::Vector2f(_largeur * TILE_SIZE / 2, _hauteur * TILE_SIZE / 2),
                    sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT)));

    // Dessiner toutes les cases de type sol
    for (unsigned i = 0; i < _hauteur * _largeur; ++i)
    {
        if (_cases[i]->est_praticable())
            target.draw(*_cases[i], states);
    }

    // Dessiner les murs et les objets
    for (unsigned i = 0; i < _hauteur * _largeur; ++i)
    {
        if (!_cases[i]->est_praticable())
            target.draw(*_cases[i], states);

        const Objet * obj = _cases[i]->get_objet();
        if (obj != NULL)
            target.draw(*obj, states);
    }
}

Case * Niveau::get_case(unsigned x, unsigned y)
{
    assert(_pret);
    assert(x >= 0 && x < _largeur);
    assert(y >= 0 && y < _hauteur);

    return _cases[y*_largeur + x];
}

const Case * Niveau::get_case(unsigned x, unsigned y) const
{
    assert(_pret);
    assert(x >= 0 && x < _largeur);
    assert(y >= 0 && y < _hauteur);

    return _cases[y*_largeur + x];
}

Joueur* Niveau::get_joueur()
{
    return _joueur;
}

const Joueur* Niveau::get_joueur() const
{
    return _joueur;
}

void Niveau::delete_joueur()
{
    _joueur = NULL;
}

std::list<MobileIA*>& Niveau::get_pnjs()
{
    return _pnjs;
}

const std::list<MobileIA*>& Niveau::get_pnjs() const
{
    return _pnjs;
}

void Niveau::delete_pnj(MobileIA* pnj)
{
    _pnjs.remove(pnj);
}

std::list<Bombe*>& Niveau::get_bombes_actives()
{
    return _bombes_actives;
}

const std::list<Bombe*>& Niveau::get_bombes_actives() const
{
    return _bombes_actives;
}

void Niveau::delete_bombe(Bombe* bombe)
{
    _bombes_actives.remove(bombe);
}

void Niveau::mise_a_jour()
{
    assert(_pret);

    typedef std::vector<Objet *> obj_vec_t;
    obj_vec_t objs;

    // Mettre à jour toutes les cases
    for (unsigned i = 0; i < _largeur * _hauteur; ++i)
    {
        _cases[i]->mise_a_jour();

        // Faire une liste des objets valides à mettre à jour
        Objet * obj = _cases[i]->get_objet();
        if (obj != NULL && obj->est_valide()){
            Joueur * joueur = dynamic_cast<Joueur *>(obj);
            if(joueur){
                _joueur = joueur;
            }
            MobileIA * mobileIA = dynamic_cast<MobileIA *>(obj);
            if (mobileIA){
                _pnjs.push_back(mobileIA);
                _pnjs.unique();
            }
            Bombe * bombe = dynamic_cast<Bombe *> (obj);
            if(bombe){
                _bombes_actives.push_back(bombe);
                _bombes_actives.unique();
            }
            objs.push_back(obj);
        }

    }

    // Mettre à jour les objets
    for (obj_vec_t::iterator i = objs.begin(); i != objs.end(); ++i)
        (*i)->mise_a_jour();
}
