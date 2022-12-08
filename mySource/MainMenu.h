#ifndef MAINMENU_H_INCLUDED
#define MAINMENU_H_INCLUDED

#include <memory>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Text.hpp>
#include "State.h"
#include "Game.h"
#include "StartState.h"
#include "Option.h"

class MainMenu: public eng::State
{
    std::shared_ptr<Context> sptr_Context;
    sf::Text txt_GameTitle;
    sf::Text txt_StartBtn;
    sf::Text txt_OptionBtn;
    sf::Text txt_ExitBtn;
    int  int_BtnIdx;
    bool bl_IsStartBtnSelected;
    bool bl_IsStartBtnPressed;
    bool bl_IsOptionSelected;
    bool bl_IsOptionPressed;
    bool bl_IsExitBtnSelected;
    bool bl_IsExitBtnPressed;

public:
    MainMenu(std::shared_ptr<Context>& sptr_Context)
    {
        this->sptr_Context = sptr_Context;
        bl_IsStartBtnSelected = true;
        bl_IsStartBtnPressed = false;
        bl_IsExitBtnSelected = false;
        bl_IsExitBtnPressed = false;
        bl_IsOptionSelected = false;
        bl_IsOptionPressed = false;
        int_BtnIdx = 0;
    }
    ~MainMenu(){}

    void SwitchBtn()
    {
        switch(int_BtnIdx)
        {
            case 0:
                bl_IsStartBtnSelected = true;
                bl_IsOptionSelected = bl_IsExitBtnSelected = false;

                break;

            case 1:
                bl_IsOptionSelected = true;
                bl_IsStartBtnSelected = bl_IsExitBtnSelected = false;

                break;

            case 2:
                bl_IsExitBtnSelected = true;
                bl_IsOptionSelected = bl_IsStartBtnSelected = false;

                break;
        }
    }
    void Init() override
    {
        sptr_Context->uptr_Assert->AddFont(CONSOLAS, "font/consola.ttf");

        // Title
        txt_GameTitle.setFont(sptr_Context->uptr_Assert->GetFont(CONSOLAS));
        txt_GameTitle.setString("Sort Simulator");
        txt_GameTitle.setCharacterSize(44);
        txt_GameTitle.setOrigin(txt_GameTitle.getLocalBounds().width / 2, txt_GameTitle.getLocalBounds().height / 2);
        txt_GameTitle.setPosition(sptr_Context->uptr_Window->getSize().x / 2, sptr_Context->uptr_Window->getSize().y / 2 - 125);

        // Start Button
        txt_StartBtn.setFont(sptr_Context->uptr_Assert->GetFont(CONSOLAS));
        txt_StartBtn.setString("start");
        txt_StartBtn.setCharacterSize(32);
        txt_StartBtn.setOrigin(txt_StartBtn.getLocalBounds().width / 2, txt_StartBtn.getLocalBounds().height / 2);
        txt_StartBtn.setPosition(sptr_Context->uptr_Window->getSize().x / 2, sptr_Context->uptr_Window->getSize().y / 2);

        // Option Button
        txt_OptionBtn.setFont(sptr_Context->uptr_Assert->GetFont(CONSOLAS));
        txt_OptionBtn.setString("option");
        txt_OptionBtn.setCharacterSize(32);
        txt_OptionBtn.setOrigin(txt_OptionBtn.getLocalBounds().width / 2, txt_OptionBtn.getLocalBounds().height / 2);
        txt_OptionBtn.setPosition(sptr_Context->uptr_Window->getSize().x / 2, sptr_Context->uptr_Window->getSize().y / 2 + 75);

        // Exit Button
        txt_ExitBtn.setFont(sptr_Context->uptr_Assert->GetFont(CONSOLAS));
        txt_ExitBtn.setString("exit");
        txt_ExitBtn.setCharacterSize(32);
        txt_ExitBtn.setOrigin(txt_ExitBtn.getLocalBounds().width / 2, txt_ExitBtn.getLocalBounds().height / 2);
        txt_ExitBtn.setPosition(sptr_Context->uptr_Window->getSize().x / 2, sptr_Context->uptr_Window->getSize().y / 2 + 150);
    }
    void ProcessInput() override
    {
        sf::Event event;    // Process events

        while(sptr_Context->uptr_Window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed) sptr_Context->uptr_Window->close();   // Close window : exit
            else if (event.type == sf::Event::KeyPressed)
            {
                switch(event.key.code)
                {
                    case sf::Keyboard::Up:
                        if(int_BtnIdx > 0) int_BtnIdx--;
                        SwitchBtn();

                        break;

                    case sf::Keyboard::Down:
                        if(int_BtnIdx < 2) int_BtnIdx++;
                        SwitchBtn();

                        break;

                    case sf::Keyboard::Enter:
                        bl_IsStartBtnPressed = false;
                        bl_IsExitBtnPressed  = false;
                        bl_IsOptionPressed   = false;

                        switch(int_BtnIdx)
                        {
                            case 0:
                                bl_IsStartBtnPressed = true;

                                break;

                            case 1:
                                bl_IsOptionPressed = true;

                                break;

                            case 2:
                                bl_IsExitBtnPressed = true;

                                break;
                        }

                        break;

                    default: break;
                }
            }
        }
    }
    void Update(sf::Time deltaTime)
    {
        if(bl_IsStartBtnSelected)
        {
            txt_StartBtn.setFillColor(sf::Color::Yellow);
            txt_OptionBtn.setFillColor(sf::Color::White);
            txt_ExitBtn.setFillColor(sf::Color::White);
        }
        else if(bl_IsOptionSelected)
        {
            txt_OptionBtn.setFillColor(sf::Color::Yellow);
            txt_StartBtn.setFillColor(sf::Color::White);
            txt_ExitBtn.setFillColor(sf::Color::White);
        }
        else if(bl_IsExitBtnSelected)
        {
            txt_ExitBtn.setFillColor(sf::Color::Yellow);
            txt_StartBtn.setFillColor(sf::Color::White);
            txt_OptionBtn.setFillColor(sf::Color::White);
        }

        if(bl_IsStartBtnPressed)
        {
            sptr_Context->uptr_State->Add(std::make_unique<StartSort>(sptr_Context), true);
        }
        else if(bl_IsOptionPressed)
        {
            sptr_Context->uptr_State->Add(std::make_unique<Option>(sptr_Context), true);
        }
        else if(bl_IsExitBtnPressed)
        {
            sptr_Context->uptr_Window->close();
        }
    }
    void Draw() override
    {
        sptr_Context->uptr_Window->clear(sf::Color::Black);
        sptr_Context->uptr_Window->draw(txt_GameTitle);
        sptr_Context->uptr_Window->draw(txt_StartBtn);
        sptr_Context->uptr_Window->draw(txt_OptionBtn);
        sptr_Context->uptr_Window->draw(txt_ExitBtn);
        sptr_Context->uptr_Window->display();
    }
};

Game::Game(): sptr_Context(std::make_shared<Context>())
{
    img_Icon.loadFromFile("mySource/Block.png");

    sptr_Context->uptr_Window->create(sf::VideoMode(int_WinWidth, int_WinHeight + 100), "Sort Simulator", sf::Style::Close);
    sptr_Context->uptr_Window->setIcon(img_Icon.getSize().x, img_Icon.getSize().y, img_Icon.getPixelsPtr());
    sptr_Context->uptr_State->Add(std::make_unique<MainMenu>(sptr_Context));
}

void StartSort::fn_Return()
{
    sptr_Context->uptr_State->Add(std::make_unique<MainMenu>(sptr_Context), true);
}

void Option::fn_Return()
{
    sptr_Context->uptr_State->Add(std::make_unique<MainMenu>(sptr_Context), true);
}

#endif // MAINMENU_H_INCLUDED
