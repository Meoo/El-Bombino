/**
 * @file   Jeu.hpp
 * @author Bastien Brunnenstein
 */

#ifndef _JEU_HPP_
#define _JEU_HPP_

#include "Monde.hpp"
#include "Sauvegarde.hpp"

/**
 * @brief
 */
class Jeu
{
private:
    Jeu();

    std::vector<Monde>  _mondes;
    Sauvegarde          _sauvegarde;

    static Jeu          s_jeu;

public:
    virtual ~Jeu();

    static Jeu & instance();

};
// class Jeu

#endif // _JEU_HPP_
