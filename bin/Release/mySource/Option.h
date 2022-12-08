#ifndef OPTION_H_INCLUDED
#define OPTION_H_INCLUDED

#include <memory>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Text.hpp>
#include "Game.h"
#include "State.h"

class Option: public eng::State
{
    std::shared_ptr<Context> sptr_Context;
    sf::Text txt_OptionTitle;
    sf::Text txt_ReturnBtn;
    sf::Text txt_SetBlkCount;
    sf::Text txt_SetSortAlgo;
    sf::Text txt_BlkCount;
    sf::Text txt_SortAlgo;
    int  int_BtnIdx;

    bool bl_SetBlkCountSelected;
    bool bl_SetBlkCountPressed;
    bool bl_SetSortAlgoSelected;
    bool bl_SetSortAlgoPressed;
    bool bl_ReturnSelected;
    bool bl_ReturnPressed;

public:
    Option(std::shared_ptr<Context>& sptr_Context)
    {
        this->sptr_Context = sptr_Context;
        bl_SetBlkCountPressed = false;
        bl_SetBlkCountSelected = true;
        bl_SetSortAlgoPressed = false;
        bl_SetSortAlgoSelected = false;
        bl_ReturnPressed = false;
        bl_ReturnSelected = false;
        int_BtnIdx = 0;
    }
    ~Option(){}

    void fn_BlkCountSetText()
    {
        switch(int_BlkCountIdx)
        {
            case 0: txt_BlkCount.setString("10"); break;
            case 1: txt_BlkCount.setString("50"); break;
            case 2: txt_BlkCount.setString("100"); break;
            case 3: txt_BlkCount.setString("500"); break;
            case 4: txt_BlkCount.setString("1000"); break;
            case 5: txt_BlkCount.setString("5000"); break;
        }

        txt_BlkCount.setOrigin(txt_BlkCount.getLocalBounds().width / 2, txt_BlkCount.getLocalBounds().height / 2);
        txt_BlkCount.setPosition(sptr_Context->uptr_Window->getSize().x / 2, sptr_Context->uptr_Window->getSize().y / 2 - 50);
    }
    void fn_SortAlgoSetText()
    {
        switch(int_SortAlgoIdx)
        {
            case BUBBLE_SORT: txt_SortAlgo.setString("Bubble Sort"); break;
            case INSERTION_SORT: txt_SortAlgo.setString("Insertion Sort"); break;
            case SELECTION_SORT: txt_SortAlgo.setString("Selection Sort"); break;
            case DOUBLE_SELECTION_SORT: txt_SortAlgo.setString("Double Selection Sort"); break;
            case MERGE_SORT: txt_SortAlgo.setString("Merge Sort"); break;
            case LOMUTO_QUICK_SORT: txt_SortAlgo.setString("Quick Sort (Lomuto Partition)"); break;
            case HOARE_QUICK_SORT: txt_SortAlgo.setString("Quick Sort (Hoare Partition)"); break;
            case COUNTING_SORT: txt_SortAlgo.setString("Counting Sort"); break;
            case LSD_RADIX_SORT: txt_SortAlgo.setString("Radix Sort (LSD)"); break;
        }

        txt_SortAlgo.setOrigin(txt_SortAlgo.getLocalBounds().width / 2, txt_SortAlgo.getLocalBounds().height / 2);
        txt_SortAlgo.setPosition(sptr_Context->uptr_Window->getSize().x / 2, sptr_Context->uptr_Window->getSize().y / 2 + 125);
    }
    void fn_Return();
    void SwitchBtn()
    {
        switch(int_BtnIdx)
        {
            case 0:
                bl_SetBlkCountSelected = true;
                bl_SetSortAlgoSelected = bl_ReturnSelected = false;

                break;

            case 1:
                bl_SetSortAlgoSelected = true;
                bl_SetBlkCountSelected = bl_ReturnSelected = false;

                break;

            case 2:
                bl_ReturnSelected = true;
                bl_SetBlkCountSelected = bl_SetSortAlgoSelected = false;

                break;
        }
    }
    void Init() override
    {
        // OPtion Title
        txt_OptionTitle.setFont(sptr_Context->uptr_Assert->GetFont(CONSOLAS));
        txt_OptionTitle.setString("Options");
        txt_OptionTitle.setCharacterSize(44);
        txt_OptionTitle.setOrigin(txt_OptionTitle.getLocalBounds().width / 2, txt_OptionTitle.getLocalBounds().height / 2);
        txt_OptionTitle.setPosition(sptr_Context->uptr_Window->getSize().x / 2, 75);

        // Set Block Count
        txt_SetBlkCount.setFont(sptr_Context->uptr_Assert->GetFont(CONSOLAS));
        txt_SetBlkCount.setString("Block Count Setting");
        txt_SetBlkCount.setCharacterSize(36);
        txt_SetBlkCount.setOrigin(txt_SetBlkCount.getLocalBounds().width / 2, txt_SetBlkCount.getLocalBounds().height / 2);
        txt_SetBlkCount.setPosition(sptr_Context->uptr_Window->getSize().x / 2, sptr_Context->uptr_Window->getSize().y / 2 - 100);


        // Block Count
        txt_BlkCount.setFont(sptr_Context->uptr_Assert->GetFont(CONSOLAS));
        txt_BlkCount.setCharacterSize(28);
        fn_BlkCountSetText();

        // Set Sort Algorithm
        txt_SetSortAlgo.setFont(sptr_Context->uptr_Assert->GetFont(CONSOLAS));
        txt_SetSortAlgo.setString("Sort Algorithm Setting");
        txt_SetSortAlgo.setCharacterSize(36);
        txt_SetSortAlgo.setOrigin(txt_SetSortAlgo.getLocalBounds().width / 2, txt_SetSortAlgo.getLocalBounds().height / 2);
        txt_SetSortAlgo.setPosition(sptr_Context->uptr_Window->getSize().x / 2, sptr_Context->uptr_Window->getSize().y / 2 + 75);

        // Sort Algorithm
        txt_SortAlgo.setFont(sptr_Context->uptr_Assert->GetFont(CONSOLAS));
        txt_SortAlgo.setCharacterSize(28);
        fn_SortAlgoSetText();


        // Return Button
        txt_ReturnBtn.setFont(sptr_Context->uptr_Assert->GetFont(CONSOLAS));
        txt_ReturnBtn.setString("Return");
        txt_ReturnBtn.setCharacterSize(36);
        txt_ReturnBtn.setOrigin(txt_ReturnBtn.getLocalBounds().width / 2, txt_ReturnBtn.getLocalBounds().height / 2);
        txt_ReturnBtn.setPosition(sptr_Context->uptr_Window->getSize().x / 2, sptr_Context->uptr_Window->getSize().y / 2 + 225);
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

                    case sf::Keyboard::Right:
                        if(bl_SetBlkCountSelected)
                        {
                            int_BlkCountIdx++;

                            if(int_BlkCountIdx > 5) int_BlkCountIdx = 0;

                            fn_BlkCountSetText();
                        }
                        else if(bl_SetSortAlgoSelected)
                        {
                            int_SortAlgoIdx++;

                            if(int_SortAlgoIdx > LSD_RADIX_SORT) int_SortAlgoIdx = 0;

                            fn_SortAlgoSetText();
                        }

                        break;

                    case sf::Keyboard::Left:
                        if(bl_SetBlkCountSelected)
                        {
                            int_BlkCountIdx--;

                            if(int_BlkCountIdx < 0) int_BlkCountIdx = 5;

                            fn_BlkCountSetText();
                        }
                        else if(bl_SetSortAlgoSelected)
                        {
                            int_SortAlgoIdx--;

                            if(int_SortAlgoIdx < 0) int_SortAlgoIdx = LSD_RADIX_SORT;

                            fn_SortAlgoSetText();
                        }

                        break;

                    case sf::Keyboard::Enter:
                        bl_SetBlkCountPressed = false;
                        bl_SetSortAlgoPressed = false;
                        bl_ReturnPressed = false;

                        switch(int_BtnIdx)
                        {
                            case 0:
                                bl_SetBlkCountPressed = true;

                                break;

                            case 1:
                                bl_SetSortAlgoPressed = true;

                                break;

                            case 2:
                                bl_ReturnPressed = true;

                                break;
                        }

                        break;

                    case sf::Keyboard::Escape:
                        bl_ReturnPressed = true;

                        break;

                    default: break;
                }
            }
        }
    }
    void Update(sf::Time deltaTime) override
    {
        if(bl_SetBlkCountSelected)
        {
            txt_SetBlkCount.setFillColor(sf::Color::Yellow);
            txt_SetSortAlgo.setFillColor(sf::Color::White);
            txt_ReturnBtn.setFillColor(sf::Color::White);
        }
        else if(bl_SetSortAlgoSelected)
        {
            txt_SetSortAlgo.setFillColor(sf::Color::Yellow);
            txt_SetBlkCount.setFillColor(sf::Color::White);
            txt_ReturnBtn.setFillColor(sf::Color::White);
        }
        else if(bl_ReturnSelected)
        {
            txt_ReturnBtn.setFillColor(sf::Color::Yellow);
            txt_SetSortAlgo.setFillColor(sf::Color::White);
            txt_SetBlkCount.setFillColor(sf::Color::White);
        }

        int_BlkCount = intarr_BtnCount[int_BlkCountIdx];

        if(bl_ReturnPressed) fn_Return();
    }
    void Draw() override
    {
        sptr_Context->uptr_Window->clear();
        sptr_Context->uptr_Window->draw(txt_OptionTitle);
        sptr_Context->uptr_Window->draw(txt_SetBlkCount);

        if(bl_SetBlkCountSelected) sptr_Context->uptr_Window->draw(txt_BlkCount);

        sptr_Context->uptr_Window->draw(txt_SetSortAlgo);

        if(bl_SetSortAlgoSelected) sptr_Context->uptr_Window->draw(txt_SortAlgo);

        sptr_Context->uptr_Window->draw(txt_ReturnBtn);
        sptr_Context->uptr_Window->display();
    }
};

#endif // OPTION_H_INCLUDED
