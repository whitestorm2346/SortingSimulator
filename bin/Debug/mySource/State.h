#ifndef STATE_H_INCLUDED
#define STATE_H_INCLUDED

#include <SFML/System/Time.hpp>

namespace eng
{
    class State
    {
    public:
        State(){};
        virtual ~State(){};

        virtual void Init() = 0;
        virtual void ProcessInput() = 0;
        virtual void Update(sf::Time deltaTime) = 0;
        virtual void Draw() = 0;
    };
}

#endif // STATE_H_INCLUDED
