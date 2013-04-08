/**
 * @file   Soulevable.hpp
 * @author Bastien Brunnenstein
 */

#ifndef _SOULEVABLE_HPP_
#define _SOULEVABLE_HPP_

#include "../Objet.hpp"

class Mobile;

/**
 * @brief
 */
class Soulevable : public Objet
{
private:
    Mobile * _porteur;

public:
    Soulevable(Case * cse);
    virtual ~Soulevable();

    Mobile * get_poteur();

};
// class Soulevable

#endif // _SOULEVABLE_HPP_
