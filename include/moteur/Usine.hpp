/**
 * @file   Usine.hpp
 * @author Bastien Brunnenstein
 * @author Pascal-Pierre Sanchez-Carrion
 */

#ifndef _USINE_HPP_
#define _USINE_HPP_

#include <string>

class Case;
class Objet;

namespace Usine
{
    Case * creer_case(const std::string & classe_case, unsigned x, unsigned y, const std::string & texture_case);
    Objet * creer_objet(const std::string & classe_objet, Case * cse);
}
// namespace Usine

#endif /* _USINE_HPP_ */
