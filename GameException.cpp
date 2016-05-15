#include "GameException.h"

GameException::GameException(const std::string &m):
    message(m)
{
}

GameException::~GameException() throw()
{
}

const char *GameException::what() const throw()
{
    return message.c_str();
}

