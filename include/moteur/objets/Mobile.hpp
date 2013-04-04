/**
 * @file   Mobile.hpp
 * @author Bastien Brunnenstein
 */

#ifndef _MOBILE_HPP_
#define _MOBILE_HPP_

#include "../Objet.hpp"

class Soulevable;

/**
 * @brief
 */
class Mobile : public Objet
{
private:
    Soulevable * _objet_souleve;

public:
    Mobile();
    virtual ~Mobile();

    Soulevable * get_objet_souleve();

    virtual void mise_a_jour();
};
// class Mobile

#endif // _MOBILE_HPP_
