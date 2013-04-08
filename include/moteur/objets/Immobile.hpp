/**
 * @file   Immobile.hpp
 * @author Bastien Brunnenstein
 */

#ifndef _IMMOBILE_HPP_
#define _IMMOBILE_HPP_

#include "../Objet.hpp"

/**
 * @brief
 */
class Immobile : public Objet
{
private:

public:
    Immobile(Case * cse);
    virtual ~Immobile();

    virtual void mise_a_jour();
};
// class Immobile

#endif // _IMMOBILE_HPP_
