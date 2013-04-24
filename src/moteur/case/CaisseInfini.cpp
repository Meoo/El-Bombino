/*
* CaisseInfini.cpp
 *
 *  Created on: 24 avr. 2013
 *      Author: Sanpas
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

bool CaisseInfini::est_praticable()
{
    return false;
}

void CaisseInfini::mise_a_jour()
{
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
}
