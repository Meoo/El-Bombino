/**
 * @file   CaisseInfini.cpp
 * @author Bastien Brunnenstein
 * @author Pascal-Pierre Sanchez-Carrion
 */

#include <moteur/Case.hpp>
#include <moteur/objets/Caisse.hpp>
#include <moteur/case/CaisseInfini.hpp>

CaisseInfini::CaisseInfini(unsigned x, unsigned y, const sf::Texture& texture): Case(x,y,texture), _timer(0), _timer_init(false)
{
    new Caisse(this);
}

CaisseInfini::~CaisseInfini()
{
}

void CaisseInfini::mise_a_jour()
{
    Case::mise_a_jour();
    if(get_objet() == NULL)
    {
        if(!_timer_init)
        {
            _timer_init = true;
            _timer = CAISSEINFINI_COLDOWN;
        }
        else if(_timer_init && _timer > 0)
        {
            --_timer;
        }
        else if(_timer_init && _timer == 0)
        {
            _timer = 0;
            _timer_init = false;
            new Caisse(this);
        }
    }
}// mise_a_jour()


// fin implementation class CaisseInfini
