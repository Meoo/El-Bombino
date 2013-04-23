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
    _sprite.setPosition(porteur->get_position_objet_souleve());
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
    bool r_bas = true, r_haut = true, r_droite = true, r_gauche = true;
    for (unsigned i = 1; i <= _puissance; ++i)
    {
        if(bas->est_praticable() && r_bas)
        {
            r_bas = bas->enflammer();
            bas = bas->get_case_bas();
        }
        if(haut->est_praticable() && r_haut)
        {
            r_haut = haut->enflammer();
            haut = haut->get_case_haut();
        }
        if(droite->est_praticable() && r_droite)
        {
            r_droite = droite->enflammer();
            droite = droite->get_case_droite();
        }
        if(gauche->est_praticable() && r_gauche)
        {
            r_gauche = gauche->enflammer();
            gauche = gauche->get_case_gauche();
        }
    }
}

void Bombe::blesser()
{
    if (get_porteur())
        exploser();

    else if (_timer > 4)
        _timer = 4;
}
