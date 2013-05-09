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
    if(porteur->est_joueur())
        Jeu::instance().get_monde_courant().get_niveau_courant().ajouter_bombe_active(this);
}


Bombe::~Bombe()
{
    Jeu::instance().get_monde_courant().get_niveau_courant().delete_bombe(this);
}


void Bombe::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_sprite, states);
}// draw()


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
}// mse_a_jour()


void Bombe::exploser()
{
    if (!est_valide()) return;

    //Faire exploser la bombe
    detruire();
    get_case()->enflammer();
    get_case()->enflammer_direction(Case::HAUT, _puissance);
    get_case()->enflammer_direction(Case::BAS, _puissance);
    get_case()->enflammer_direction(Case::GAUCHE, _puissance);
    get_case()->enflammer_direction(Case::DROITE, _puissance);
}// exploser()


void Bombe::blesser()
{
    if (get_porteur())
        exploser();

    else if (_timer > 4)
        _timer = 4;
}// blesser()


// fin implementation class Bombe
