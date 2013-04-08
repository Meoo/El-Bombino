/**
 * @file   ExceptionRessource.hpp
 * @author Bastien Brunnenstein
 * @author Pascal-Pierre Sanchez-Carrion
 */

#ifndef _EXCEPTIONRESSOURCE_HPP_
#define _EXCEPTIONRESSOURCE_HPP_

#include "../Exception.hpp"

class ExceptionRessource: public Exception
{
public:
    ExceptionRessource(const std::string & fichier,
            const std::string & erreur) throw () :
            Exception(fichier + " : " + erreur)
    {
    }

    virtual ~ExceptionRessource() throw ()
    {
    }
};
// class ExceptionRessource

#endif /* _EXCEPTIONRESSOURCE_HPP_ */
