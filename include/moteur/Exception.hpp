/**
 * @file   Exception.hpp
 * @author Bastien Brunnenstein
 * @author Pascal-Pierre Sanchez-Carrion
 */

#ifndef _EXCEPTION_HPP_
#define _EXCEPTION_HPP_

#include "../Config.hpp"

#include <exception>

class Exception: public std::exception
{
private:
    const std::string message;

public:
    Exception(const std::string & message) throw () :
            std::exception(), message(message)
    {
    }

    virtual ~Exception() throw ()
    {
    }

    virtual const char* what() const throw ()
    {
        return message.c_str();
    }
};
// class Exception

#endif /* _EXCEPTION_HPP_ */
