/*
 * BombeGlacee.hpp
 *
 *  Created on: 10 mai 2013
 *      Author: Sanpas
 */

#ifndef BOMBEGLACEE_HPP_
#define BOMBEGLACEE_HPP_

#include <moteur/objets/Bombe.hpp>

class BombeGlacee: public Bombe
{
public:
                    BombeGlacee(Mobile * porteur, unsigned timer, unsigned puissance);
    virtual         ~BombeGlacee();

    virtual void    exploser();


};


#endif /* BOMBEGLACEE_HPP_ */
