/**
 * @file   Vide.hpp
 * @author Bastien Brunnenstein
 * @author Pascal-Pierre Sanchez-Carrion
 */

#ifndef VIDE_HPP_
#define VIDE_HPP_

#include <SFML/Graphics.hpp>


/**
 * @brief
 */
class Vide : public Case
{

public:

                    Vide(unsigned x, unsigned y, const sf::Texture & texture);
    virtual         ~Vide();

    virtual bool    est_praticable();
};
// class Vide


#endif /* VIDE_HPP_ */
