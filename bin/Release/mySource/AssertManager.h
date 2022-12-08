#ifndef ASSERTMANAGER_H_INCLUDED
#define ASSERTMANAGER_H_INCLUDED

#include <map>
#include <memory>
#include <string>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>

namespace eng
{
    class AssertMan
    {
        std::map<int, std::unique_ptr<sf::Texture> > map_Texture;
        std::map<int, std::unique_ptr<sf::Font> > map_Font;

    public:
        AssertMan(){}
        ~AssertMan(){}

        void AddTexture(int int_Idx, const std::string& str_FilePath, bool bl_WantRepeated = false)
        {
            auto Texture = std::make_unique<sf::Texture>();

            if(Texture->loadFromFile(str_FilePath))
            {
                Texture->setRepeated(bl_WantRepeated);
                map_Texture[int_Idx] = std::move(Texture);
            }
        }
        void AddFont(int int_Idx, const std::string& str_FilePath)
        {
            auto Font = std::make_unique<sf::Font>();

            if(Font->loadFromFile(str_FilePath)) map_Font[int_Idx] = std::move(Font);
        }

        const sf::Texture& GetTexture(int int_Idx) const
        {
            return *(map_Texture.at(int_Idx).get());
        }
        const sf::Font& GetFont(int int_Idx) const
        {
            return *(map_Font.at(int_Idx).get());
        }
    };
}

#endif // ASSERTMANAGER_H_INCLUDED
