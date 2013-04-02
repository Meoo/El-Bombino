/**
 * @file   Monde.hpp
 * @author Bastien Brunnenstein
 */

#ifndef _MONDE_HPP_
#define _MONDE_HPP_

#include "Niveau.hpp"

/**
 * @brief
 */
class Monde
{
private:
    std::vector<Niveau> _niveaux;
    Niveau *            _niveau_courant;

public:
    Monde();
    virtual ~Monde();

};
// class Monde

#endif // _MONDE_HPP_
