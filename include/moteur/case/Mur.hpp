/**
 * @file   Mur.hpp
 * @author Bastien Brunnenstein
 * @author Pascal-Pierre Sanchez-Carrion
 */

#ifndef MUR_HPP_
#define MUR_HPP_

#include <SFML/Graphics.hpp>


/**
 * @brief
 */
class Mur : public Case
{

public:

                    Mur(unsigned x, unsigned y, const sf::Texture & texture);
    virtual         ~Mur();

    virtual bool    est_praticable();
};
// class Mur

#endif /* MUR_HPP_ */
