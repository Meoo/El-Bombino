/**
 * @file   Niveau.cpp
 * @author Bastien Brunnenstein
 * @author Pascal-Pierre Sanchez-Carrion
 */

#include <moteur/Niveau.hpp>
#include <moteur/exceptions/ExceptionRessource.hpp>
#include <moteur/Jeu.hpp>
#include <moteur/Menu.hpp>
#include <moteur/Monde.hpp>
#include <moteur/Case.hpp>
#include <moteur/objets/Joueur.hpp>
#include <moteur/objets/MobileIA.hpp>
#include <moteur/objets/Bombe.hpp>

#include <fstream>

Niveau::Niveau(const std::string & fic) :
        _fichier_rc(fic), _largeur(0), _hauteur(0), _cases(NULL), _joueur(NULL), _fini(false), _timer_fini(50), _timer_game_over(50)
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
}// charger()


void Niveau::liberer()
{
    for (unsigned i = 0; i < _largeur * _hauteur; ++i)
        delete _cases[i];
    delete _cases;
    _cases = NULL;
    _largeur = 0;
    _hauteur = 0;
    _fini = false;
    _pnjs.clear();

#ifndef NDEBUG
    _pret = false;
#endif
}// liberer()


void Niveau::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    assert(_pret);
    if(_largeur * TILE_SIZE <= WINDOW_WIDTH && _hauteur * TILE_SIZE <= WINDOW_HEIGHT)
        target.setView(sf::View(
                        sf::Vector2f(_largeur * TILE_SIZE / 2, _hauteur * TILE_SIZE / 2),
                        sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT)));
    else if(_joueur != NULL)
        target.setView(sf::View(sf::Vector2f(_joueur->get_case()->get_y() / 2 + WINDOW_WIDTH / 2, _joueur->get_case()->get_x() / 2 + WINDOW_HEIGHT / 2),
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

    if (_joueur != NULL)
    {
        target.setView(sf::View(sf::FloatRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT)));

        // Dessiner l'interface
        sf::RectangleShape rect(sf::Vector2f(350, 28));
        rect.setFillColor(sf::Color(0,0,0,128));

        target.draw(rect);

        // La puissance
        char text_c[10];
        sprintf(text_c, "%d", _joueur->get_puissance_bombe());

        sf::Text text(text_c, Jeu::instance().get_default_font(), 18);
        text.setPosition(10, 3);

        target.draw(text);

        sf::Sprite sprite(Jeu::instance().get_texture("bonus_puissance"));
        sprite.setScale(0.5, 0.5);
        sprite.setPosition(30, 5);

        target.draw(sprite);

        // Le nombre de bombes
        sprintf(text_c, "%d", _joueur->get_nb_bombe_simultanee());

        text.setString(text_c);
        text.setPosition(70, 3);

        target.draw(text);

        sprite.setTexture(Jeu::instance().get_texture("bonus_bombe"));
        sprite.setPosition(90, 5);

        target.draw(sprite);

        // La vitesse
        sprintf(text_c, "%.1f", _joueur->get_vitesse());

        text.setString(text_c);
        text.setPosition(130, 3);

        target.draw(text);

        sprite.setTexture(Jeu::instance().get_texture("bonus_vitesse"));
        sprite.setPosition(160, 5);

        target.draw(sprite);

        // Les vies
        sprintf(text_c, "%d", _joueur->get_vie());

        text.setString(text_c);
        text.setPosition(200, 3);

        target.draw(text);

        sprite.setTexture(Jeu::instance().get_texture("bonus_vie"));
        sprite.setPosition(220, 5);

        target.draw(sprite);

        // si bonus special
        if(_joueur->get_bonus_soulevable())
        {
            sprite.setTexture(Jeu::instance().get_texture("bonus_gant"));
            sprite.setPosition(260, 5);

            target.draw(sprite);
        }
        else if(_joueur->get_bonus_bombe_spe())
        {
            sprite.setTexture(Jeu::instance().get_texture("bonus_bombe_special"));
            sprite.setPosition(260, 5);

            target.draw(sprite);
        }
        else
        {
            sprite.setTexture(Jeu::instance().get_texture("aucun_bonus_special"));
            sprite.setPosition(260, 5);

            target.draw(sprite);
        }

        sprintf(text_c, "%d", _pnjs.size());

        text.setString(text_c);
        text.setPosition(300, 3);

        target.draw(text);
    }

}// draw()


Case * Niveau::get_case(unsigned x, unsigned y)
{
    assert(_pret);
    assert(x >= 0 && x < _largeur);
    assert(y >= 0 && y < _hauteur);

    return _cases[y*_largeur + x];
}// get_case()


const Case * Niveau::get_case(unsigned x, unsigned y) const
{
    assert(_pret);
    assert(x >= 0 && x < _largeur);
    assert(y >= 0 && y < _hauteur);

    return _cases[y*_largeur + x];
}// get_case()


Joueur* Niveau::get_joueur()
{
    return _joueur;
}// get_joueur()


const Joueur* Niveau::get_joueur() const
{
    return _joueur;
}// get_joueur()


void Niveau::delete_joueur()
{
    _joueur = NULL;
}// delete_joueur()


std::list<MobileIA*>& Niveau::get_pnjs()
{
    return _pnjs;
}// get_pnjs()


const std::list<MobileIA*>& Niveau::get_pnjs() const
{
    return _pnjs;
}// get_pnjs()


void Niveau::delete_pnj(MobileIA* pnj)
{
    _pnjs.remove(pnj);
}// delete_pnj()


std::list<Bombe*>& Niveau::get_bombes_actives()
{
    return _bombes_actives;
}// get_bombes_actives()


const std::list<Bombe*>& Niveau::get_bombes_actives() const
{
    return _bombes_actives;
}// get_bombes_actives()


void Niveau::delete_bombe(Bombe* bombe)
{
    _bombes_actives.remove(bombe);
}// delete_bombe()


void Niveau::ajouter_bombe_active(Bombe *bombe)
{
    _bombes_actives.push_back(bombe);
}// ajouter_bombe_active()


void Niveau::ajouter_pnj(MobileIA* pnj)
{
    _pnjs.push_back(pnj);
}// ajouter_pnj()


void Niveau::ajouter_joueur(Joueur* joueur)
{
    assert(_joueur == NULL);

    _joueur = joueur;
}// ajouter_joueur()


bool Niveau::est_fini()
{
    return _fini;
}// est_fini()


void Niveau::mise_a_jour()
{
    assert(_pret);

    for (unsigned i = 0; i < _largeur * _hauteur; ++i)
    {
        _cases[i]->get_case_info()._danger_explosion = -1;
        _cases[i]->get_case_info()._distance = -1;
        _cases[i]->get_case_info()._distance_cacher = -1;
        _cases[i]->get_case_info()._direction = nsUtil::ORIGINE;
    }

    // Lancer la génération des informations sur les cases pour IA
    if(_joueur != NULL)
    {
       generer_info_case(_joueur->get_case());
       generer_info_case_cacher(_joueur->get_case());
    }

    typedef std::vector<Objet *> obj_vec_t;
    obj_vec_t objs;



    // Mettre à jour toutes les cases
    for (unsigned i = 0; i < _largeur * _hauteur; ++i)
    {
        _cases[i]->mise_a_jour();

        // Faire une liste des objets valides à mettre à jour
        Objet * obj = _cases[i]->get_objet();
        if (obj != NULL && obj->est_valide())
            objs.push_back(obj);
    }

    // Mettre à jour les objets
    for (obj_vec_t::iterator i = objs.begin(); i != objs.end(); ++i)
        (*i)->mise_a_jour();

    if(_pnjs.size() == 0 && _joueur)
    {
        if(_timer_fini == 0)
            _fini = true;
        else if (_timer_fini > 0)
            --_timer_fini;
    }
    if(!_joueur)
    {
        if(_timer_game_over == 0)
            Jeu::instance().get_menu()->active_menu(Menu::GAME_OVER);
        else
            --_timer_game_over;
    }

}// mise_a_jour()


void Niveau::generer_info_case(Case* cse, unsigned distance /*= 0*/, nsUtil::direction_t direction /*= nsUtil::ORIGINE*/)
{
    Soulevable * soulevable = dynamic_cast<Soulevable *> (cse->get_objet());
    if (!cse->est_praticable()  || soulevable) return;
    if (_joueur->get_case() == cse || cse->get_case_info()._distance >= distance)
    {
        if(cse->get_case_info()._distance == distance)
        {
            if(rand()%2 == 0) cse->get_case_info()._direction = direction;
        }
        else
        {
            cse->get_case_info()._distance = distance;
            cse->get_case_info()._direction = direction;
            switch (direction) {
                case nsUtil::GAUCHE:
                    generer_info_case(cse->get_case_bas(), distance+1, nsUtil::HAUT);
                    generer_info_case(cse->get_case_droite(), distance+1, nsUtil::GAUCHE);
                    generer_info_case(cse->get_case_haut(), distance+1, nsUtil::BAS);
                    break;
                case nsUtil::DROITE:
                    generer_info_case(cse->get_case_bas(), distance+1, nsUtil::HAUT);
                    generer_info_case(cse->get_case_gauche(), distance+1, nsUtil::DROITE);
                    generer_info_case(cse->get_case_haut(), distance+1, nsUtil::BAS);
                    break;
                case nsUtil::BAS:
                    generer_info_case(cse->get_case_gauche(), distance+1, nsUtil::DROITE);
                    generer_info_case(cse->get_case_droite(), distance+1, nsUtil::GAUCHE);
                    generer_info_case(cse->get_case_haut(), distance+1, nsUtil::BAS);
                    break;
                case nsUtil::HAUT:
                    generer_info_case(cse->get_case_bas(), distance+1, nsUtil::HAUT);
                    generer_info_case(cse->get_case_droite(), distance+1, nsUtil::GAUCHE);
                    generer_info_case(cse->get_case_gauche(), distance+1, nsUtil::DROITE);
                    break;
                case nsUtil::ORIGINE:
                    generer_info_case(cse->get_case_haut(), distance+1, nsUtil::BAS);
                    generer_info_case(cse->get_case_bas(), distance+1, nsUtil::HAUT);
                    generer_info_case(cse->get_case_droite(), distance+1, nsUtil::GAUCHE);
                    generer_info_case(cse->get_case_gauche(), distance+1, nsUtil::DROITE);
            }
        }
    }
}// genere_infocase()


void Niveau::generer_info_case_cacher(Case* cse, unsigned distance /*= 0*/, nsUtil::direction_t direction /*= nsUtil::ORIGINE*/)
{
    if (!cse->est_praticable()) return;
    if (_joueur->get_case() == cse || cse->get_case_info()._distance_cacher >= distance)
    {
        if(cse->get_case_info()._distance_cacher == distance)
        {
            if(rand()%2 == 0) cse->get_case_info()._direction_cacher = direction;
        }
        else
        {
            cse->get_case_info()._distance_cacher = distance;
            cse->get_case_info()._direction_cacher = direction;
            switch (direction) {
                case nsUtil::GAUCHE:
                    generer_info_case_cacher(cse->get_case_bas(), distance+1, nsUtil::HAUT);
                    generer_info_case_cacher(cse->get_case_droite(), distance+1, nsUtil::GAUCHE);
                    generer_info_case_cacher(cse->get_case_haut(), distance+1, nsUtil::BAS);
                    break;
                case nsUtil::DROITE:
                    generer_info_case_cacher(cse->get_case_bas(), distance+1, nsUtil::HAUT);
                    generer_info_case_cacher(cse->get_case_gauche(), distance+1, nsUtil::DROITE);
                    generer_info_case_cacher(cse->get_case_haut(), distance+1, nsUtil::BAS);
                    break;
                case nsUtil::BAS:
                    generer_info_case_cacher(cse->get_case_gauche(), distance+1, nsUtil::DROITE);
                    generer_info_case_cacher(cse->get_case_droite(), distance+1, nsUtil::GAUCHE);
                    generer_info_case_cacher(cse->get_case_haut(), distance+1, nsUtil::BAS);
                    break;
                case nsUtil::HAUT:
                    generer_info_case_cacher(cse->get_case_bas(), distance+1, nsUtil::HAUT);
                    generer_info_case_cacher(cse->get_case_droite(), distance+1, nsUtil::GAUCHE);
                    generer_info_case_cacher(cse->get_case_gauche(), distance+1, nsUtil::DROITE);
                    break;
                case nsUtil::ORIGINE:
                    generer_info_case_cacher(cse->get_case_haut(), distance+1, nsUtil::BAS);
                    generer_info_case_cacher(cse->get_case_bas(), distance+1, nsUtil::HAUT);
                    generer_info_case_cacher(cse->get_case_droite(), distance+1, nsUtil::GAUCHE);
                    generer_info_case_cacher(cse->get_case_gauche(), distance+1, nsUtil::DROITE);
            }
        }
    }
}// genere_infocase()

// fin implementation class Niveau


