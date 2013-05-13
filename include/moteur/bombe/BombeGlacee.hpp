/**
 * @file   BombeGlacee.hpp
 * @author Bastien Brunnenstein
 * @author Pascal-Pierre Sanchez-Carrion
 */

#ifndef BOMBEGLACEE_HPP_
#define BOMBEGLACEE_HPP_

#include <moteur/objets/Bombe.hpp>

/**
 * @brief
 */
class BombeGlacee: public Bombe
{
public:
                    BombeGlacee(Mobile * porteur, unsigned timer, unsigned puissance);
    virtual         ~BombeGlacee();

    virtual void    exploser();


};
// class BombeGlacee

#endif /* BOMBEGLACEE_HPP_ */
