/**
 * @file   Utile.hpp
 * @author Bastien Brunnenstein
 * @author Pascal-Pierre Sanchez-Carrion
 */

#ifndef UTILE_HPP_
#define UTILE_HPP_

#include <string>

#include <SFML/Graphics.hpp>


/**
 * @brief
 */
namespace nsUtil
{
    std::string convertInt(int number);

    std::string SFKeyToString(sf::Keyboard::Key keycode);

    typedef enum direction {
        HAUT,
        DROITE,
        BAS,
        GAUCHE,
        ORIGINE,
    } direction_t;
}
// namespace Utile

#endif /* UTILE_HPP_ */
