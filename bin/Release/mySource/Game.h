#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <iostream>
#include <memory>
#include <SFML/Graphics/RenderWindow.hpp>
#include "StateManager.h"
#include "AssertManager.h"

#define int_WinHeight static_cast<float>(600)
#define int_WinWidth static_cast<float>(1200)

enum AssertID
{
    CONSOLAS = 0
};

enum SortAlgorithm
{
    // Finished
    BUBBLE_SORT = 0,
    INSERTION_SORT,
    SELECTION_SORT,
    DOUBLE_SELECTION_SORT,
    COUNTING_SORT,
    LSD_RADIX_SORT,

    // Not finished
    MERGE_SORT,
    LOMUTO_QUICK_SORT,
    HOARE_QUICK_SORT
};

int  intarr_BtnCount[] = {10, 50, 100, 500, 1000, 5000};
int int_BlkCount = 100;
int int_BlkCountIdx = 2;
int int_SortAlgoIdx = 0;

struct Context
{
    std::unique_ptr<eng::AssertMan> uptr_Assert;
    std::unique_ptr<eng::StateMan> uptr_State;
    std::unique_ptr<sf::RenderWindow> uptr_Window;

    Context()
    {
        uptr_Assert = std::make_unique<eng::AssertMan>();
        uptr_State  = std::make_unique<eng::StateMan>();
        uptr_Window = std::make_unique<sf::RenderWindow>();
    }
};

class Game
{
    std::shared_ptr<Context> sptr_Context;
    sf::Image img_Icon;
    const sf::Time FPS = sf::seconds(1.0f / 60.0f);
    int i = 0;

public:
    Game();
    ~Game(){}

    void Run()
    {
        //sf::Clock clk_Main;
        //sf::Time time_SinceLastFrame = sf::Time::Zero;

        while(sptr_Context->uptr_Window->isOpen())    // Start the game loop
        {
            //time_SinceLastFrame += clk_Main.restart();

            //while(time_SinceLastFrame > FPS)
            //{
                //time_SinceLastFrame -= FPS;

                sptr_Context->uptr_State->ChangeState();
                sptr_Context->uptr_State->GetCurr()->ProcessInput();
                sptr_Context->uptr_State->GetCurr()->Update(FPS);
                sptr_Context->uptr_State->GetCurr()->Draw();
            //}
        }
    }
};



#endif // GAME_H_INCLUDED
