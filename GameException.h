#ifndef GAME_EXCEPTION_H
#define GAME_EXCEPTION_H

#include <exception>
#include <string>

class GameException: public std::exception
{
    public:
        explicit GameException(const std::string &msg);
        virtual ~GameException() throw();

        virtual const char *what() const throw();

    protected:
        std::string message;
};

#endif

