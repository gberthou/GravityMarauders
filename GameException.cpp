#include "GameException.h"

GameException::GameException(const std::string &msg):
    message(msg)
{
}

GameException::~GameException() throw()
{
}

const char *GameException::what() const throw()
{
    return message.c_str();
}

