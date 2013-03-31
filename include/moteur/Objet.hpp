/**
 * @file   Objet.hpp
 * @author Bastien Brunnenstein
 */

#ifndef _OBJET_HPP_
#define _OBJET_HPP_

#include <SFML/Graphics.hpp>

class Case;

/**
 * @brief
 */
class Objet : public sf::Sprite
{
private:
    Case * _case;

public:
    Objet();
    virtual ~Objet();

};
// class Objet

#endif // _OBJET_HPP_
