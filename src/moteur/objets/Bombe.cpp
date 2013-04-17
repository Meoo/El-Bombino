/**
 * @file   Bombe.hpp
 * @author Bastien Brunnenstein
 * @author Pascal-Pierre Sanchez-Carrion
 */

#include <moteur/objets/Bombe.hpp>
#include <moteur/objets/Mobile.hpp>
#include <moteur/Jeu.hpp>
#include <moteur/Case.hpp>


Bombe::Bombe(Mobile* porteur, unsigned timer, unsigned puissance) :
        Soulevable(porteur), _sprite(Jeu::instance().get_texture("bombe")), _timer(timer), _puissance(puissance)
{
    _sprite.setOrigin(_sprite.getTexture()->getSize().x/2, _sprite.getTexture()->getSize().y/2);
}

Bombe::~Bombe()
{
}

void Bombe::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_sprite, states);
}


void Bombe::mise_a_jour()
{
    Soulevable::mise_a_jour();

    if (get_porteur() == NULL)
    {
        _sprite.setPosition(get_case()->get_x() * TILE_SIZE + TILE_SIZE / 2,
                            get_case()->get_y() * TILE_SIZE + TILE_SIZE / 2);
    }
    else
    {
        _sprite.setPosition(get_porteur()->get_position_objet_souleve());
    }

    if (_timer < 35)
    {
        float perc = (50 - _timer) / 50.f;
        float fac = 1 + perc / 10.f;
        unsigned char col = (unsigned char)((1 - perc) * 255);

        _sprite.setScale(fac, fac);
        _sprite.setColor(sf::Color(255, col, col));
    }

    _timer -= 1;
    if (_timer == 0) exploser();
}

void Bombe::exploser()
{
    if (!est_valide()) return;

    //Faire exploser la bombe
    detruire();
    get_case()->enflammer();

    Case *droite = get_case()->get_case_droite();
    Case *gauche = get_case()->get_case_gauche();
    Case *haut   = get_case()->get_case_haut();
    Case *bas    = get_case()->get_case_bas();
    for (unsigned i = 1; i <= _puissance; ++i)
    {
        if(bas->est_praticable())
        {
            bas->enflammer();
            bas = bas->get_case_bas();
        }
        if(haut->est_praticable())
        {
            haut->enflammer();
            haut = haut->get_case_haut();
        }
        if(droite->est_praticable())
        {
            droite->enflammer();
            droite = droite->get_case_droite();
        }
        if(gauche->est_praticable())
        {
            gauche->enflammer();
            gauche = gauche->get_case_gauche();
        }
    }
}

void Bombe::blesser()
{
    exploser();
}
