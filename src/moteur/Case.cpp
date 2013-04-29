/**
 * @file   Case.cpp
 * @author Bastien Brunnenstein
 * @author Pascal-Pierre Sanchez-Carrion
 */

#include <moteur/Case.hpp>
#include <moteur/Objet.hpp>
#include <moteur/Jeu.hpp>

Case::Case(unsigned x, unsigned y, const sf::Texture & texture) :
        _objet(NULL), _texture(&texture), _feu_duree(0), _feu_effet(0), _x(x), _y(y)
{
}

Case::~Case()
{
    if (_objet != NULL)
        delete _objet;
}

Objet * Case::get_objet()
{
    return _objet;
}

const Objet * Case::get_objet() const
{
    return _objet;
}

bool Case::enflammer(unsigned duree, const sf::Color& couleur, objet_effet_t effet)
{
    _feu_duree = duree;
    _feu_couleur = couleur;
    _feu_effet = effet;

    // TODO Toujours bloquer les flammes si objet?
    if (_objet != NULL && _objet->est_valide())
    {
        return false;
    }

    return true;
}

bool Case::est_en_feu() const
{
    return _feu_duree > 10;
}

unsigned Case::get_duree_flammes() const
{
    return _feu_duree;
}

bool Case::est_praticable()
{
    return true;
}

void Case::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    sf::Sprite sprite(*_texture);
    sprite.setPosition((float) _x * TILE_SIZE,
            (float) _y * TILE_SIZE + (float) TILE_SIZE
                    - (float) sprite.getTexture()->getSize().y);
    target.draw(sprite, states);

    if (_feu_duree > 0)
    {
        sf::Color col (_feu_couleur);
        if (_feu_duree < 15)
        {
            col.a = (_feu_duree * 255) / 15;
        }

        sf::Sprite feu(Jeu::instance().get_texture("feu"));
        feu.setPosition((float) _x * TILE_SIZE, (float) _y * TILE_SIZE);
        feu.setColor(col);
        target.draw(feu, states);
    }
}

void Case::set_objet(Objet * objet)
{
    assert(objet == NULL || _objet == NULL);

    _objet = objet;
}

unsigned Case::get_x() const
{
    return _x;
}

unsigned Case::get_y() const
{
    return _y;
}

void Case::mise_a_jour()
{
    if (_objet != NULL)
    {
        if (_objet->est_valide())
        {
            if (est_en_feu())
                (_objet->*_feu_effet)();
        }
        else
        {
            Objet *obj = _objet;
            _objet = NULL;
            obj->laisser_tomber_objet(this);
            delete obj;
        }
    }

    if (_feu_duree > 0)
        _feu_duree--;
}

Case * Case::get_case_droite()
{
    return Jeu::instance().get_monde_courant().
                get_niveau_courant().get_case(_x + 1, _y);
}

const Case * Case::get_case_droite() const
{
    return Jeu::instance().get_monde_courant().
                get_niveau_courant().get_case(_x + 1, _y);
}

Case * Case::get_case_gauche()
{
    return Jeu::instance().get_monde_courant().
                get_niveau_courant().get_case(_x - 1, _y);
}

const Case * Case::get_case_gauche() const
{
    return Jeu::instance().get_monde_courant().
                get_niveau_courant().get_case(_x - 1, _y);
}

Case * Case::get_case_haut()
{
    return Jeu::instance().get_monde_courant().
                get_niveau_courant().get_case(_x, _y - 1);
}

const Case * Case::get_case_haut() const
{
    return Jeu::instance().get_monde_courant().
                get_niveau_courant().get_case(_x, _y - 1);
}

Case * Case::get_case_bas()
{
    return Jeu::instance().get_monde_courant().
                get_niveau_courant().get_case(_x, _y + 1);
}

const Case * Case::get_case_bas() const
{
    return Jeu::instance().get_monde_courant().
                get_niveau_courant().get_case(_x, _y + 1);
}
