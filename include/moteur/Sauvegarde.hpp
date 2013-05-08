/**
 * @file   Sauvegarde.hpp
 * @author Bastien Brunnenstein
 * @author Pascal-Pierre Sanchez-Carrion
 */

#ifndef _SAUVEGARDE_HPP_
#define _SAUVEGARDE_HPP_

#include "../Config.hpp"

/**
 * @brief
 */
class Sauvegarde
{
private:

public:
    Sauvegarde();
    virtual ~Sauvegarde();

    void    charger_sauvegarde();

    void    sauver_sauvegarde();
};
// class Sauvegarde

#endif // _SAUVEGARDE_HPP_
