/**
 * @file   Utile.hpp
 * @author Bastien Brunnenstein
 * @author Pascal-Pierre Sanchez-Carrion
 */

#ifndef UTILE_HPP_
#define UTILE_HPP_

#include <string>

#include <SFML/Graphics.hpp>

namespace nsUtil
{
    std::string convertInt(int number);

    std::string SFKeyToString(sf::Keyboard::Key keycode);

    typedef enum direction {
        HAUT,BAS,DROITE,GAUCHE,ORIGINE,
    } direction_t;
}


#endif /* UTILE_HPP_ */
