/**
 * @file   Bombe.hpp
 * @author Bastien Brunnenstein
 * @author Pascal-Pierre Sanchez-Carrion
 */

#include <moteur/objets/Bombe.hpp>
#include <moteur/Jeu.hpp>
#include <moteur/Case.hpp>


Bombe::Bombe(Mobile* porteur) :
        Soulevable(porteur), _sprite(Jeu::instance().get_texture("bombe")), _timer(0)
{

}

Bombe::~Bombe()
{
}

void Bombe::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(_sprite, states);
}

void Bombe::deposer(Case* cse)
{
    Soulevable::deposer(cse);
    //initialisation du timer;
}

void Bombe::mise_a_jour()
{
    Soulevable::mise_a_jour();
    //mise_a_jour du timer;
}
