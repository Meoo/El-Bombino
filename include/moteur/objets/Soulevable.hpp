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
    Soulevable();
    virtual ~Soulevable();

};
// class Soulevable

#endif // _SOULEVABLE_HPP_
