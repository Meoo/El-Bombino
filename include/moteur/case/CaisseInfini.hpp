/*
 * CaisseInfini.hpp
 *
 *  Created on: 24 avr. 2013
 *      Author: Sanpas
 */

#ifndef CAISSEINFINI_HPP_
#define CAISSEINFINI_HPP_

class CaisseInfini : public Case
{
        unsigned    _timer;
        bool        _timer_init;

public:

                    CaisseInfini(unsigned x, unsigned y, const sf::Texture & texture);
    virtual         ~CaisseInfini();

    virtual bool    est_praticable();
    virtual void    mise_a_jour();
};
// class CaisseInfini


#endif /* CAISSEINFINI_HPP_ */
