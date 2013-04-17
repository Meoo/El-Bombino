/**
 * @file   Bombe.hpp
 * @author Bastien Brunnenstein
 * @author Pascal-Pierre Sanchez-Carrion
 */

#include <moteur/objets/Bombe.hpp>
#include <moteur/Jeu.hpp>
#include <moteur/Case.hpp>


Bombe::Bombe(Mobile* porteur, unsigned timer, unsigned puissance) :
        Soulevable(porteur), _sprite(Jeu::instance().get_texture("bombe")), _timer(timer), _puissance(puissance)
{

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
    _timer -= 1;
    if(_timer == 0)exploser();
}

void Bombe::exploser()
{
    //faire exploser la bombe.
    // TODO enflammer la distance ?
    //detruire();
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
