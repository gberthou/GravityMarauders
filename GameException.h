#ifndef GAME_EXCEPTION_H
#define GAME_EXCEPTION_H

#include <exception>
#include <string>

class GameException: public std::exception
{
    public:
        GameException(const std::string &message);
        virtual ~GameException() throw();

        virtual const char *what() const throw();

    protected:
        std::string message;
};

#endif

