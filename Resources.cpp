#include <string>
#include <sstream>

#include <Resources.h>
#include <GameException.h>

using namespace Resources;

sf::Texture Resources::texSpaceships[SPACESHIP_COUNT];

static void loadTextureFromFile(const std::string &filename,
                                sf::Texture &texture)
{
    if(!texture.loadFromFile(filename))
    {
        std::ostringstream oss;
        oss << "Cannot load texture '" << filename << '\'';
        throw GameException(oss.str());
    }
}

void Resources::LoadTextures()
{
    const std::string SPACESHIP_FILENAMES[SPACESHIP_COUNT] = {
        "img/spaceship0.png"
    };

    for(unsigned int i = 0; i < SPACESHIP_COUNT; ++i)
        loadTextureFromFile(SPACESHIP_FILENAMES[i], texSpaceships[i]);
}

sf::Sprite Resources::CreateCenteredSprite(const sf::Texture &texture)
{
    sf::Sprite ret(texture);
    sf::Vector2u dimensions = texture.getSize();
    ret.setOrigin(dimensions.x / 2.f, dimensions.y / 2.f);
    return ret;
}

