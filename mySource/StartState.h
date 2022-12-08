#ifndef STARTSTATE_H_INCLUDED
#define STARTSTATE_H_INCLUDED

#include <memory>
#include <deque>
#include <stack>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Time.hpp>
#include "Game.h"
#include "State.h"
#include "ClassObject.h"

class StartSort: public eng::State
{
    std::shared_ptr<Context> sptr_Context;
    std::deque<obj::Block> deq_BlkArr;
    std::deque<obj::Block> deq_LBlk;
    std::deque<obj::Block> deq_RBlk;
    std::stack<obj::MergeSortIdx> stk_MIdx;
    sf::Text txt_SortName;
    sf::Text txt_ResetBtn;
    sf::Text txt_StartBtn;
    sf::Text txt_ReturnBtn;
    int  int_BtnIdx;
    int  int_CheckBlkIdx;
    int  int_RCheckBlkIdx;
    int  int_MSCheckBlkIdx;
    int  int_SortIdx;
    int  int_MSortIdx;
    int  int_RSortIdx;
    int  int_MaxElemIdx;
    int  int_MinElemIdx;
    int  int_StepCount;
    bool bl_IsResetSelected;
    bool bl_IsResetPressed;
    bool bl_IsStartSelected;
    bool bl_IsStartPressed;
    bool bl_IsReturnSelected;
    bool bl_IsReturnPressed;
    bool bl_Sorted;
    bool bl_IsSorting;
    bool bl_IsChecking;
    bool bl_HaveSwitch;

public:
    StartSort(std::shared_ptr<Context>& sptr_Context)
    {
        this->sptr_Context = sptr_Context;
        bl_IsResetPressed = false;
        bl_IsResetSelected = true;
        bl_IsReturnPressed = false;
        bl_IsReturnSelected = false;
        bl_IsStartPressed = false;
        bl_IsStartSelected = false;
        bl_Sorted = true;
        bl_IsSorting = false;
        bl_IsChecking = false;
        int_BtnIdx = 0;
        int_CheckBlkIdx = 0;
        int_RCheckBlkIdx = int_BlkCount - 1;
        int_MinElemIdx = 0;
        int_MaxElemIdx = int_BlkCount - 1;
        int_SortIdx = 0;
        int_RSortIdx = int_BlkCount - 1;

        for(int i = 0; i < int_BlkCount; i++)
        {
            obj::Block blk_Elem;

            deq_BlkArr.push_back(blk_Elem);
        }
    }
    ~StartSort(){}

    void fn_Return();
    void fn_SetMergeSort(std::deque<obj::Block>& deq_BlkArr, int int_StartIdx, int int_EndIdx);

    void fn_BubbleSort();
    void fn_InsertionSort();
    void fn_SelectionSort();
    void fn_DoubleSelectionSort();
    void fn_MergeSort();
    void fn_QuickSortLomuto();
    void fn_QuickSortHoare();
    void fn_CountingSort();
    void fn_RadixSortLSD();

    void SwitchBtn()
    {
        switch(int_BtnIdx)
        {
            case 0:
                bl_IsResetSelected = true;
                bl_IsReturnSelected = bl_IsStartSelected = false;

                break;

            case 1:
                bl_IsStartSelected = true;
                bl_IsResetSelected = bl_IsReturnSelected = false;

                break;

            case 2:
                bl_IsReturnSelected = true;
                bl_IsResetSelected = bl_IsStartSelected = false;

                break;
        }
    }
    void Init() override
    {
        fn::PresetBlk(deq_BlkArr, int_BlkCount);

        // Sort Name
        txt_SortName.setFont(sptr_Context->uptr_Assert->GetFont(CONSOLAS));

        switch(int_SortAlgoIdx)
        {
            case BUBBLE_SORT: txt_SortName.setString("Bubble Sort"); break;
            case INSERTION_SORT: txt_SortName.setString("Insertion Sort"); break;
            case SELECTION_SORT: txt_SortName.setString("Selection Sort"); break;
            case DOUBLE_SELECTION_SORT: txt_SortName.setString("Double Selection Sort"); break;
            case MERGE_SORT: txt_SortName.setString("Merge Sort"); break;
            case LOMUTO_QUICK_SORT: txt_SortName.setString("Quick Sort (Lomuto Partition)"); break;
            case HOARE_QUICK_SORT: txt_SortName.setString("Quick Sort (Hoare Partition)"); break;
            case COUNTING_SORT: txt_SortName.setString("Counting Sort"); break;
            case LSD_RADIX_SORT: txt_SortName.setString("Radix Sort (LSD)"); break;
        }

        txt_SortName.setCharacterSize(36);
        txt_SortName.setPosition(0, 0);

        // Reset Button
        txt_ResetBtn.setFont(sptr_Context->uptr_Assert->GetFont(CONSOLAS));
        txt_ResetBtn.setString("Reset Blocks");
        txt_ResetBtn.setCharacterSize(24);
        txt_ResetBtn.setPosition(0, 50);

        // Start Button
        txt_StartBtn.setFont(sptr_Context->uptr_Assert->GetFont(CONSOLAS));
        txt_StartBtn.setString("Start Sorting");
        txt_StartBtn.setCharacterSize(24);
        txt_StartBtn.setPosition(0, 75);

        // Return Button
        txt_ReturnBtn.setFont(sptr_Context->uptr_Assert->GetFont(CONSOLAS));
        txt_ReturnBtn.setString("Return");
        txt_ReturnBtn.setCharacterSize(24);
        txt_ReturnBtn.setPosition(0, 100);
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
                        if((!bl_IsSorting && !bl_IsChecking) && int_BtnIdx > 0) int_BtnIdx--;
                        SwitchBtn();

                        break;

                    case sf::Keyboard::Down:
                        if((!bl_IsSorting && !bl_IsChecking) && int_BtnIdx < 2) int_BtnIdx++;
                        SwitchBtn();

                        break;

                    case sf::Keyboard::Enter:
                        switch(int_BtnIdx)
                        {
                            case 0:
                                bl_IsResetPressed = true;
                                txt_ResetBtn.setString("Reseting . . .");

                                break;

                            case 1:
                                if(!bl_Sorted)
                                {
                                    bl_IsStartPressed = true;
                                    txt_StartBtn.setString("Sorting . . .");
                                }

                                break;

                            case 2:
                                bl_IsReturnPressed = true;

                                break;
                        }

                        break;

                    case sf::Keyboard::Escape:
                        bl_IsReturnPressed = true;

                        break;

                    default: break;
                }
            }
        }
    }
    void Update(sf::Time deltaTime) override
    {
        if(bl_IsResetSelected)
        {
            txt_ResetBtn.setFillColor(sf::Color::Yellow);
            txt_StartBtn.setFillColor(sf::Color::White);
            txt_ReturnBtn.setFillColor(sf::Color::White);
        }
        else if(bl_IsStartSelected)
        {
            txt_StartBtn.setFillColor(sf::Color::Yellow);
            txt_ResetBtn.setFillColor(sf::Color::White);
            txt_ReturnBtn.setFillColor(sf::Color::White);
        }
        else if(bl_IsReturnSelected)
        {
            txt_ReturnBtn.setFillColor(sf::Color::Yellow);
            txt_StartBtn.setFillColor(sf::Color::White);
            txt_ResetBtn.setFillColor(sf::Color::White);
        }

        if(bl_IsReturnPressed) fn_Return();
    }
    void Draw() override
    {
        if(bl_IsSorting)
        {
            switch(int_SortAlgoIdx)
            {
                case BUBBLE_SORT: fn_BubbleSort(); break;
                case INSERTION_SORT: fn_InsertionSort(); break;
                case SELECTION_SORT: fn_SelectionSort(); break;
                case DOUBLE_SELECTION_SORT: fn_DoubleSelectionSort(); break;
                case MERGE_SORT: fn_MergeSort(); break;
                case LOMUTO_QUICK_SORT: fn_QuickSortLomuto(); break;
                case HOARE_QUICK_SORT: fn_QuickSortHoare(); break;
                case COUNTING_SORT: fn_CountingSort(); break;
                case LSD_RADIX_SORT: fn_RadixSortLSD(); break;

                default: break;
            }

            if(bl_Sorted)
            {
                txt_StartBtn.setString("Checking");

                bl_IsSorting = false;
                bl_IsChecking = true;
                int_SortIdx = 0;
            }
        }
        else if(bl_IsChecking)
        {
            deq_BlkArr[int_SortIdx++].fn_SetColor(sf::Color::Green);

            sptr_Context->uptr_Window->clear();
            sptr_Context->uptr_Window->draw(txt_SortName);
            sptr_Context->uptr_Window->draw(txt_ResetBtn);
            sptr_Context->uptr_Window->draw(txt_StartBtn);
            sptr_Context->uptr_Window->draw(txt_ReturnBtn);

            for(int i = 0; i < int_BlkCount; i++)
            {
                sptr_Context->uptr_Window->draw(deq_BlkArr[i].rct_Field);
            }

            sptr_Context->uptr_Window->display();

            if(int_SortIdx == int_BlkCount)
            {
                sptr_Context->uptr_Window->clear();
                sptr_Context->uptr_Window->draw(txt_SortName);
                sptr_Context->uptr_Window->draw(txt_ResetBtn);
                sptr_Context->uptr_Window->draw(txt_StartBtn);
                sptr_Context->uptr_Window->draw(txt_ReturnBtn);

                for(int i = 0; i < int_BlkCount; i++)
                {
                    deq_BlkArr[i].fn_SetColor();

                    sptr_Context->uptr_Window->draw(deq_BlkArr[i].rct_Field);
                }

                sptr_Context->uptr_Window->display();
                txt_StartBtn.setString("Start Sorting");

                bl_IsChecking = false;
            }
        }
        else
        {
            sptr_Context->uptr_Window->clear();
            sptr_Context->uptr_Window->draw(txt_SortName);
            sptr_Context->uptr_Window->draw(txt_ResetBtn);
            sptr_Context->uptr_Window->draw(txt_StartBtn);
            sptr_Context->uptr_Window->draw(txt_ReturnBtn);

            for(int i = 0; i < int_BlkCount; i++)
            {
                sptr_Context->uptr_Window->draw(deq_BlkArr[i].rct_Field);
            }

            sptr_Context->uptr_Window->display();

            if(bl_IsResetPressed)
            {
                fn::RandomBlk(deq_BlkArr, int_BlkCount);

                txt_ResetBtn.setString("Reset Blocks");

                bl_IsResetPressed = false;
                bl_Sorted = false;
            }
            else if(bl_IsStartPressed && !bl_Sorted)
            {
                bl_IsStartPressed = false;
                bl_IsSorting = true;

                switch(int_SortAlgoIdx)
                {
                    case BUBBLE_SORT:
                        int_SortIdx = 0;
                        int_CheckBlkIdx = int_BlkCount - 1;

                        break;

                    case INSERTION_SORT:
                        int_SortIdx = 1;
                        int_CheckBlkIdx = 1;

                        break;

                    case SELECTION_SORT:
                        int_MinElemIdx = 0;
                        int_SortIdx = 0;
                        int_CheckBlkIdx = 0;

                        break;

                    case DOUBLE_SELECTION_SORT:
                        int_MinElemIdx = 0;
                        int_SortIdx = 0;
                        int_CheckBlkIdx = 0;

                        int_MaxElemIdx = int_BlkCount - 1;
                        int_RSortIdx = int_BlkCount - 1;
                        int_RCheckBlkIdx = int_BlkCount - 1;

                        break;

                    case MERGE_SORT:
                        fn_SetMergeSort(deq_BlkArr, 0, int_BlkCount - 1);
                        int_StepCount = 0;

                        break;

                    case LOMUTO_QUICK_SORT:
                        break;

                    case HOARE_QUICK_SORT:
                        break;

                    case COUNTING_SORT:
                        int_SortIdx = 0;
                        int_StepCount = 0;
                        int_MaxElemIdx = 0;

                        break;

                    case LSD_RADIX_SORT:
                        int_SortIdx = 0;
                        int_StepCount = 0;
                        int_MaxElemIdx = 0;
                        deq_LBlk.clear();
                        deq_RBlk.clear();

                        for(int i = 0, j = 0; j < int_BlkCount; j++)
                        {
                            obj::Block blk_RVal;

                            if(i++ < 10) deq_LBlk.push_back(blk_RVal);

                            deq_RBlk.push_back(blk_RVal);
                        }

                        break;

                    default: break;
                }
            }
        }
    }
};

void StartSort::fn_BubbleSort()
{
    deq_BlkArr[int_SortIdx].fn_SetColor(sf::Color::Red);
    deq_BlkArr[int_SortIdx + 1].fn_SetColor(sf::Color::Red);

    if(deq_BlkArr[int_SortIdx].int_Idx > deq_BlkArr[int_SortIdx + 1].int_Idx)
    {
        obj::Block blk_TempRval = deq_BlkArr[int_SortIdx];

        deq_BlkArr[int_SortIdx] = deq_BlkArr[int_SortIdx + 1];
        deq_BlkArr[int_SortIdx + 1] = blk_TempRval;

        deq_BlkArr[int_SortIdx].fn_SetXPos(int_SortIdx, int_BlkCount);
        deq_BlkArr[int_SortIdx].fn_SetRctPos();

        deq_BlkArr[int_SortIdx + 1].fn_SetXPos(int_SortIdx + 1, int_BlkCount);
        deq_BlkArr[int_SortIdx + 1].fn_SetRctPos();
    }

    sptr_Context->uptr_Window->clear();
    sptr_Context->uptr_Window->draw(txt_SortName);
    sptr_Context->uptr_Window->draw(txt_ResetBtn);
    sptr_Context->uptr_Window->draw(txt_StartBtn);
    sptr_Context->uptr_Window->draw(txt_ReturnBtn);

    bl_Sorted = true;

    for(int i = 0; i < int_BlkCount; i++)
    {
        sptr_Context->uptr_Window->draw(deq_BlkArr[i].rct_Field);

        if(i < int_CheckBlkIdx && deq_BlkArr[i].int_Idx > deq_BlkArr[i + 1].int_Idx) bl_Sorted = false;
        if(i == int_CheckBlkIdx && deq_BlkArr[int_CheckBlkIdx].int_Idx == int_CheckBlkIdx) int_CheckBlkIdx--;
    }

    sptr_Context->uptr_Window->display();

    deq_BlkArr[int_SortIdx].fn_SetColor();
    deq_BlkArr[int_SortIdx + 1].fn_SetColor();

    if(++int_SortIdx >= int_CheckBlkIdx) int_SortIdx = 0;
}

void StartSort::fn_InsertionSort()
{
    bl_HaveSwitch = false;

    deq_BlkArr[int_SortIdx].fn_SetColor(sf::Color::Red);

    if(deq_BlkArr[int_SortIdx].int_Idx < deq_BlkArr[int_SortIdx - 1].int_Idx)
    {
        bl_HaveSwitch = true;

        obj::Block blk_TempRval = deq_BlkArr[int_SortIdx];

        deq_BlkArr[int_SortIdx] = deq_BlkArr[int_SortIdx - 1];
        deq_BlkArr[int_SortIdx - 1] = blk_TempRval;

        deq_BlkArr[int_SortIdx].fn_SetXPos(int_SortIdx, int_BlkCount);
        deq_BlkArr[int_SortIdx].fn_SetRctPos();

        deq_BlkArr[int_SortIdx - 1].fn_SetXPos(int_SortIdx - 1, int_BlkCount);
        deq_BlkArr[int_SortIdx - 1].fn_SetRctPos();
    }

    sptr_Context->uptr_Window->clear();
    sptr_Context->uptr_Window->draw(txt_SortName);
    sptr_Context->uptr_Window->draw(txt_ResetBtn);
    sptr_Context->uptr_Window->draw(txt_StartBtn);
    sptr_Context->uptr_Window->draw(txt_ReturnBtn);

    for(int i = 0; i < int_BlkCount; i++)
    {
        sptr_Context->uptr_Window->draw(deq_BlkArr[i].rct_Field);
    }

    sptr_Context->uptr_Window->display();

    deq_BlkArr[int_SortIdx].fn_SetColor();

    if(int_SortIdx == 1) deq_BlkArr[0].fn_SetColor();
    if(--int_SortIdx == 0 || !bl_HaveSwitch) int_SortIdx = ++int_CheckBlkIdx;

    bl_Sorted = (int_CheckBlkIdx == int_BlkCount);
}

void StartSort::fn_SelectionSort()
{
    if(deq_BlkArr[int_SortIdx].int_Idx < deq_BlkArr[int_MinElemIdx].int_Idx)
    {
        deq_BlkArr[int_MinElemIdx].fn_SetColor();

        int_MinElemIdx = int_SortIdx;
    }

    deq_BlkArr[int_SortIdx].fn_SetColor(sf::Color::Red);

    sptr_Context->uptr_Window->clear();
    sptr_Context->uptr_Window->draw(txt_SortName);
    sptr_Context->uptr_Window->draw(txt_ResetBtn);
    sptr_Context->uptr_Window->draw(txt_StartBtn);
    sptr_Context->uptr_Window->draw(txt_ReturnBtn);

    bl_Sorted = true;

    for(int i = 0; i < int_BlkCount; i++)
    {
        sptr_Context->uptr_Window->draw(deq_BlkArr[i].rct_Field);

        if(i < int_BlkCount - 1 && deq_BlkArr[i].int_Idx > deq_BlkArr[i + 1].int_Idx) bl_Sorted = false;
    }

    sptr_Context->uptr_Window->display();

    if(int_SortIdx != int_MinElemIdx)
    {
        deq_BlkArr[int_SortIdx].fn_SetColor();
        deq_BlkArr[int_MinElemIdx].fn_SetColor(sf::Color::Red);
    }
    else deq_BlkArr[int_SortIdx].fn_SetColor();

    if(++int_SortIdx == int_BlkCount)
    {
        if(int_CheckBlkIdx != int_MinElemIdx)
        {
            obj::Block blk_TempRval = deq_BlkArr[int_CheckBlkIdx];

            deq_BlkArr[int_CheckBlkIdx] = deq_BlkArr[int_MinElemIdx];
            deq_BlkArr[int_MinElemIdx] = blk_TempRval;

            deq_BlkArr[int_CheckBlkIdx].fn_SetXPos(int_CheckBlkIdx, int_BlkCount);
            deq_BlkArr[int_CheckBlkIdx].fn_SetRctPos();
            deq_BlkArr[int_CheckBlkIdx].fn_SetColor();

            deq_BlkArr[int_MinElemIdx].fn_SetXPos(int_MinElemIdx, int_BlkCount);
            deq_BlkArr[int_MinElemIdx].fn_SetRctPos();
        }

        deq_BlkArr[int_MinElemIdx].fn_SetColor();

        int_SortIdx = int_MinElemIdx = ++int_CheckBlkIdx;
    }
}

void StartSort::fn_DoubleSelectionSort()
{
    if(deq_BlkArr[int_SortIdx].int_Idx < deq_BlkArr[int_MinElemIdx].int_Idx)
    {
        deq_BlkArr[int_MinElemIdx].fn_SetColor();

        int_MinElemIdx = int_SortIdx;
    }

    if(deq_BlkArr[int_SortIdx].int_Idx > deq_BlkArr[int_MaxElemIdx].int_Idx)
    {
        deq_BlkArr[int_MaxElemIdx].fn_SetColor();

        int_MaxElemIdx = int_SortIdx;
    }

    deq_BlkArr[int_SortIdx].fn_SetColor(sf::Color::Red);

    sptr_Context->uptr_Window->clear();
    sptr_Context->uptr_Window->draw(txt_SortName);
    sptr_Context->uptr_Window->draw(txt_ResetBtn);
    sptr_Context->uptr_Window->draw(txt_StartBtn);
    sptr_Context->uptr_Window->draw(txt_ReturnBtn);

    bl_Sorted = true;

    for(int i = 0; i < int_BlkCount; i++)
    {
        sptr_Context->uptr_Window->draw(deq_BlkArr[i].rct_Field);

        if(i < int_BlkCount - 1 && deq_BlkArr[i].int_Idx > deq_BlkArr[i + 1].int_Idx) bl_Sorted = false;
    }

    sptr_Context->uptr_Window->display();

    if(int_SortIdx != int_MinElemIdx && int_SortIdx != int_MaxElemIdx)
    {
        deq_BlkArr[int_SortIdx].fn_SetColor();
        deq_BlkArr[int_MinElemIdx].fn_SetColor(sf::Color::Red);
        deq_BlkArr[int_MaxElemIdx].fn_SetColor(sf::Color::Red);
    }
    else deq_BlkArr[int_SortIdx].fn_SetColor();

    if(++int_SortIdx == int_RCheckBlkIdx + 1)
    {
        if(int_MinElemIdx == int_RCheckBlkIdx && int_MaxElemIdx == int_CheckBlkIdx)
        {
            obj::Block blk_TempRval = deq_BlkArr[int_CheckBlkIdx];

            deq_BlkArr[int_CheckBlkIdx] = deq_BlkArr[int_RCheckBlkIdx];
            deq_BlkArr[int_RCheckBlkIdx] = blk_TempRval;

            deq_BlkArr[int_CheckBlkIdx].fn_SetXPos(int_CheckBlkIdx, int_BlkCount);
            deq_BlkArr[int_CheckBlkIdx].fn_SetRctPos();
            deq_BlkArr[int_CheckBlkIdx].fn_SetColor();

            deq_BlkArr[int_RCheckBlkIdx].fn_SetXPos(int_RCheckBlkIdx, int_BlkCount);
            deq_BlkArr[int_RCheckBlkIdx].fn_SetRctPos();
        }
        else if(int_MinElemIdx == int_RCheckBlkIdx)
        {
            obj::Block blk_TempRval = deq_BlkArr[int_CheckBlkIdx];

            deq_BlkArr[int_CheckBlkIdx] = deq_BlkArr[int_MinElemIdx];
            deq_BlkArr[int_MinElemIdx] = blk_TempRval;

            deq_BlkArr[int_CheckBlkIdx].fn_SetXPos(int_CheckBlkIdx, int_BlkCount);
            deq_BlkArr[int_CheckBlkIdx].fn_SetRctPos();
            deq_BlkArr[int_CheckBlkIdx].fn_SetColor();

            deq_BlkArr[int_MinElemIdx].fn_SetXPos(int_MinElemIdx, int_BlkCount);
            deq_BlkArr[int_MinElemIdx].fn_SetRctPos();

            blk_TempRval = deq_BlkArr[int_RCheckBlkIdx];

            deq_BlkArr[int_RCheckBlkIdx] = deq_BlkArr[int_MaxElemIdx];
            deq_BlkArr[int_MaxElemIdx] = blk_TempRval;

            deq_BlkArr[int_RCheckBlkIdx].fn_SetXPos(int_RCheckBlkIdx, int_BlkCount);
            deq_BlkArr[int_RCheckBlkIdx].fn_SetRctPos();
            deq_BlkArr[int_RCheckBlkIdx].fn_SetColor();

            deq_BlkArr[int_MaxElemIdx].fn_SetXPos(int_MaxElemIdx, int_BlkCount);
            deq_BlkArr[int_MaxElemIdx].fn_SetRctPos();
        }
        else if(int_MaxElemIdx == int_CheckBlkIdx)
        {
            obj::Block blk_TempRval = deq_BlkArr[int_RCheckBlkIdx];

            deq_BlkArr[int_RCheckBlkIdx] = deq_BlkArr[int_MaxElemIdx];
            deq_BlkArr[int_MaxElemIdx] = blk_TempRval;

            deq_BlkArr[int_RCheckBlkIdx].fn_SetXPos(int_RCheckBlkIdx, int_BlkCount);
            deq_BlkArr[int_RCheckBlkIdx].fn_SetRctPos();
            deq_BlkArr[int_RCheckBlkIdx].fn_SetColor();

            deq_BlkArr[int_MaxElemIdx].fn_SetXPos(int_MaxElemIdx, int_BlkCount);
            deq_BlkArr[int_MaxElemIdx].fn_SetRctPos();

            blk_TempRval = deq_BlkArr[int_CheckBlkIdx];

            deq_BlkArr[int_CheckBlkIdx] = deq_BlkArr[int_MinElemIdx];
            deq_BlkArr[int_MinElemIdx] = blk_TempRval;

            deq_BlkArr[int_CheckBlkIdx].fn_SetXPos(int_CheckBlkIdx, int_BlkCount);
            deq_BlkArr[int_CheckBlkIdx].fn_SetRctPos();
            deq_BlkArr[int_CheckBlkIdx].fn_SetColor();

            deq_BlkArr[int_MinElemIdx].fn_SetXPos(int_MinElemIdx, int_BlkCount);
            deq_BlkArr[int_MinElemIdx].fn_SetRctPos();
        }
        else
        {
            if(int_CheckBlkIdx != int_MinElemIdx)
            {
                obj::Block blk_TempRval = deq_BlkArr[int_CheckBlkIdx];

                deq_BlkArr[int_CheckBlkIdx] = deq_BlkArr[int_MinElemIdx];
                deq_BlkArr[int_MinElemIdx] = blk_TempRval;

                deq_BlkArr[int_CheckBlkIdx].fn_SetXPos(int_CheckBlkIdx, int_BlkCount);
                deq_BlkArr[int_CheckBlkIdx].fn_SetRctPos();
                deq_BlkArr[int_CheckBlkIdx].fn_SetColor();

                deq_BlkArr[int_MinElemIdx].fn_SetXPos(int_MinElemIdx, int_BlkCount);
                deq_BlkArr[int_MinElemIdx].fn_SetRctPos();
            }

            if(int_RCheckBlkIdx != int_MaxElemIdx)
            {
                obj::Block blk_TempRval = deq_BlkArr[int_RCheckBlkIdx];

                deq_BlkArr[int_RCheckBlkIdx] = deq_BlkArr[int_MaxElemIdx];
                deq_BlkArr[int_MaxElemIdx] = blk_TempRval;

                deq_BlkArr[int_RCheckBlkIdx].fn_SetXPos(int_RCheckBlkIdx, int_BlkCount);
                deq_BlkArr[int_RCheckBlkIdx].fn_SetRctPos();
                deq_BlkArr[int_RCheckBlkIdx].fn_SetColor();

                deq_BlkArr[int_MaxElemIdx].fn_SetXPos(int_MaxElemIdx, int_BlkCount);
                deq_BlkArr[int_MaxElemIdx].fn_SetRctPos();
            }
        }


        deq_BlkArr[int_MinElemIdx].fn_SetColor();
        deq_BlkArr[int_MaxElemIdx].fn_SetColor();

        int_SortIdx = int_MinElemIdx = ++int_CheckBlkIdx;
        int_MaxElemIdx = --int_RCheckBlkIdx;
    }
}

void StartSort::fn_CountingSort()
{
    switch(int_StepCount)
    {
        case 0: // Get Max Value
            if(deq_BlkArr[int_SortIdx].int_Idx > deq_BlkArr[int_MaxElemIdx].int_Idx)
            {
                deq_BlkArr[int_MaxElemIdx].fn_SetColor();

                int_MaxElemIdx = int_SortIdx;
            }

            deq_BlkArr[int_SortIdx].fn_SetColor(sf::Color::Red);

            sptr_Context->uptr_Window->clear();
            sptr_Context->uptr_Window->draw(txt_SortName);
            sptr_Context->uptr_Window->draw(txt_ResetBtn);
            sptr_Context->uptr_Window->draw(txt_StartBtn);
            sptr_Context->uptr_Window->draw(txt_ReturnBtn);

            for(int i = 0; i < int_BlkCount; i++)
            {
                sptr_Context->uptr_Window->draw(deq_BlkArr[i].rct_Field);
            }

            sptr_Context->uptr_Window->display();

            if(int_SortIdx != int_MaxElemIdx)
            {
                deq_BlkArr[int_SortIdx].fn_SetColor();
                deq_BlkArr[int_MaxElemIdx].fn_SetColor(sf::Color::Red);
            }
            else deq_BlkArr[int_SortIdx].fn_SetColor();

            if(++int_SortIdx == int_BlkCount)
            {
                deq_BlkArr[int_MaxElemIdx].fn_SetColor();

                int_SortIdx = 0;
                int_StepCount++;
            }

            break;

        case 1: // Count Elements' numbers
            deq_BlkArr[int_SortIdx].fn_SetColor(sf::Color::Red);

            sptr_Context->uptr_Window->clear();
            sptr_Context->uptr_Window->draw(txt_SortName);
            sptr_Context->uptr_Window->draw(txt_ResetBtn);
            sptr_Context->uptr_Window->draw(txt_StartBtn);
            sptr_Context->uptr_Window->draw(txt_ReturnBtn);

            for(int i = 0; i < int_BlkCount; i++)
            {
                sptr_Context->uptr_Window->draw(deq_BlkArr[i].rct_Field);
            }

            sptr_Context->uptr_Window->display();

            deq_BlkArr[int_SortIdx].fn_SetColor();

            if(++int_SortIdx == int_BlkCount)
            {
                int_SortIdx = 0;
                int_StepCount++;
            }

            break;

        case 2: // print
            deq_BlkArr[int_SortIdx].fn_SetColor(sf::Color::Red);
            deq_BlkArr[int_SortIdx].fn_SetIdx(int_SortIdx);
            deq_BlkArr[int_SortIdx].fn_SetSize(int_SortIdx, int_BlkCount);
            deq_BlkArr[int_SortIdx].fn_SetXPos(int_SortIdx, int_BlkCount);
            deq_BlkArr[int_SortIdx].fn_SetYPos(int_SortIdx, int_BlkCount);
            deq_BlkArr[int_SortIdx].fn_SetRctPos();

            sptr_Context->uptr_Window->clear();
            sptr_Context->uptr_Window->draw(txt_SortName);
            sptr_Context->uptr_Window->draw(txt_ResetBtn);
            sptr_Context->uptr_Window->draw(txt_StartBtn);
            sptr_Context->uptr_Window->draw(txt_ReturnBtn);

            for(int i = 0; i < int_BlkCount; i++)
            {
                sptr_Context->uptr_Window->draw(deq_BlkArr[i].rct_Field);
            }

            sptr_Context->uptr_Window->display();

            deq_BlkArr[int_SortIdx].fn_SetColor();

            if(++int_SortIdx == int_BlkCount)
            {
                bl_Sorted = true;
            }

            break;
    }
}

void StartSort::fn_RadixSortLSD()
{
    switch(int_StepCount)
    {
        case 0: // Get Max Value
            if(deq_BlkArr[int_SortIdx].int_Idx > deq_BlkArr[int_MaxElemIdx].int_Idx)
            {
                deq_BlkArr[int_MaxElemIdx].fn_SetColor();

                int_MaxElemIdx = int_SortIdx;
            }

            deq_BlkArr[int_SortIdx].fn_SetColor(sf::Color::Red);

            sptr_Context->uptr_Window->clear();
            sptr_Context->uptr_Window->draw(txt_SortName);
            sptr_Context->uptr_Window->draw(txt_ResetBtn);
            sptr_Context->uptr_Window->draw(txt_StartBtn);
            sptr_Context->uptr_Window->draw(txt_ReturnBtn);

            for(int i = 0; i < int_BlkCount; i++)
            {
                sptr_Context->uptr_Window->draw(deq_BlkArr[i].rct_Field);
            }

            sptr_Context->uptr_Window->display();

            if(int_SortIdx != int_MaxElemIdx)
            {
                deq_BlkArr[int_SortIdx].fn_SetColor();
                deq_BlkArr[int_MaxElemIdx].fn_SetColor(sf::Color::Red);
            }
            else deq_BlkArr[int_SortIdx].fn_SetColor();

            if(++int_SortIdx == int_BlkCount)
            {
                deq_BlkArr[int_MaxElemIdx].fn_SetColor();

                int_SortIdx = 0;
                int_CheckBlkIdx = 1; // int_Exp
                int_MaxElemIdx = deq_BlkArr[int_MaxElemIdx].int_Idx; // int_MaxElem

                int_StepCount = 1;
            }

            break;

        case 1: // Sorting
            deq_BlkArr[int_SortIdx].fn_SetColor(sf::Color::Red);
            deq_LBlk[(deq_BlkArr[int_SortIdx].int_Idx / int_CheckBlkIdx) % 10].int_Idx++;

            sptr_Context->uptr_Window->clear();
            sptr_Context->uptr_Window->draw(txt_SortName);
            sptr_Context->uptr_Window->draw(txt_ResetBtn);
            sptr_Context->uptr_Window->draw(txt_StartBtn);
            sptr_Context->uptr_Window->draw(txt_ReturnBtn);

            for(int i = 0; i < int_BlkCount; i++)
            {
                sptr_Context->uptr_Window->draw(deq_BlkArr[i].rct_Field);
            }

            sptr_Context->uptr_Window->display();

            deq_BlkArr[int_SortIdx].fn_SetColor();

            if(++int_SortIdx == int_BlkCount)
            {
                int_SortIdx = 0;
                int_RSortIdx = int_BlkCount - 1;
                int_StepCount = 2;

                for(int i = 1; i < 10; i++)
                {
                    deq_LBlk[i].int_Idx += deq_LBlk[i - 1].int_Idx;
                }

                for(int i = int_BlkCount - 1; i >= 0; i--)
                {
                    deq_RBlk[--(deq_LBlk[(deq_BlkArr[i].int_Idx / int_CheckBlkIdx) % 10].int_Idx)] = deq_BlkArr[i];
                }

                deq_BlkArr = deq_RBlk;
            }

            break;

        case 2: // Displaying
            deq_BlkArr[int_SortIdx].fn_SetColor(sf::Color::Red);
            deq_BlkArr[int_SortIdx].fn_SetXPos(int_SortIdx, int_BlkCount);
            deq_BlkArr[int_SortIdx].fn_SetYPos(deq_BlkArr[int_SortIdx].int_Idx, int_BlkCount);
            deq_BlkArr[int_SortIdx].fn_SetSize(deq_BlkArr[int_SortIdx].int_Idx, int_BlkCount);
            deq_BlkArr[int_SortIdx].fn_SetRctPos();

            sptr_Context->uptr_Window->clear();
            sptr_Context->uptr_Window->draw(txt_SortName);
            sptr_Context->uptr_Window->draw(txt_ResetBtn);
            sptr_Context->uptr_Window->draw(txt_StartBtn);
            sptr_Context->uptr_Window->draw(txt_ReturnBtn);

            for(int i = 0; i < int_BlkCount; i++)
            {
                sptr_Context->uptr_Window->draw(deq_BlkArr[i].rct_Field);
            }

            sptr_Context->uptr_Window->display();

            deq_BlkArr[int_SortIdx].fn_SetColor();

            if(++int_SortIdx == int_BlkCount)
            {
                int_CheckBlkIdx *= 10;
                int_SortIdx = 0;
                int_StepCount = 1;

                for(int i = 0; i < 10; i++)
                {
                    deq_LBlk[i].int_Idx = 0;
                }
            }

            if(int_MaxElemIdx / int_CheckBlkIdx == 0) bl_Sorted = true;

            break;
    }
}

void StartSort::fn_SetMergeSort(std::deque<obj::Block>& deq_BlkArr, int int_StartIdx, int int_EndIdx)
{
    if(int_StartIdx < int_EndIdx)
    {
        obj::MergeSortIdx msi_Rval;
        int int_MidIdx = int_StartIdx + (int_EndIdx - 1) / 2;

        fn_SetMergeSort(deq_BlkArr, int_MidIdx + 1, int_EndIdx);
        fn_SetMergeSort(deq_BlkArr, int_StartIdx, int_MidIdx);

        msi_Rval.int_Start = int_StartIdx;
        msi_Rval.int_Mid = int_MidIdx;
        msi_Rval.int_End = int_EndIdx;

        stk_MIdx.push(msi_Rval);
    }

    return;
}

void StartSort::fn_MergeSort()
{
    switch(int_StepCount)
    {
        case 0: // Init
            int_SortIdx  = stk_MIdx.top().int_Start;
            int_MSortIdx = stk_MIdx.top().int_Mid;
            int_RSortIdx = stk_MIdx.top().int_End;

            int_CheckBlkIdx = 0;
            int_RCheckBlkIdx = 0;
            int_MSCheckBlkIdx = int_SortIdx;

            deq_LBlk.clear();
            deq_RBlk.clear();

            int_StepCount++;

            sptr_Context->uptr_Window->clear();
            sptr_Context->uptr_Window->draw(txt_SortName);
            sptr_Context->uptr_Window->draw(txt_ResetBtn);
            sptr_Context->uptr_Window->draw(txt_StartBtn);
            sptr_Context->uptr_Window->draw(txt_ReturnBtn);

            for(int i = 0; i < int_BlkCount; i++)
            {
                sptr_Context->uptr_Window->draw(deq_BlkArr[i].rct_Field);
            }

            sptr_Context->uptr_Window->display();

            break;

        case 1: // Divide
            if(int_CheckBlkIdx < int_MSortIdx - int_SortIdx + 1)
            {
                obj::Block blk_Elem = deq_BlkArr[int_SortIdx + int_CheckBlkIdx];

                deq_LBlk.push_back(blk_Elem);

                deq_BlkArr[int_SortIdx + int_CheckBlkIdx].fn_SetColor(sf::Color::Red);
            }

            if(int_RCheckBlkIdx < int_RSortIdx - int_MSortIdx)
            {
                obj::Block blk_Elem = deq_BlkArr[int_MSortIdx + 1 + int_RCheckBlkIdx];

                deq_LBlk.push_back(blk_Elem);

                deq_BlkArr[int_MSortIdx + int_RCheckBlkIdx + 1].fn_SetColor(sf::Color::Red);
            }

            sptr_Context->uptr_Window->clear();
            sptr_Context->uptr_Window->draw(txt_SortName);
            sptr_Context->uptr_Window->draw(txt_ResetBtn);
            sptr_Context->uptr_Window->draw(txt_StartBtn);
            sptr_Context->uptr_Window->draw(txt_ReturnBtn);

            for(int i = 0; i < int_BlkCount; i++)
            {
                sptr_Context->uptr_Window->draw(deq_BlkArr[i].rct_Field);
            }

            sptr_Context->uptr_Window->display();

            if(int_CheckBlkIdx < int_MSortIdx - int_SortIdx + 1)
            {
                deq_BlkArr[int_SortIdx + int_CheckBlkIdx].fn_SetColor();

                int_CheckBlkIdx++;
            }
            if(int_RCheckBlkIdx < int_RSortIdx - int_MSortIdx)
            {
                deq_BlkArr[int_MSortIdx + int_RCheckBlkIdx + 1].fn_SetColor();

                int_RCheckBlkIdx++;
            }

            if(int_CheckBlkIdx >= int_MSortIdx - int_SortIdx + 1 && int_RCheckBlkIdx >= int_RSortIdx - int_MSortIdx)
            {
                int_CheckBlkIdx = 0;
                int_RCheckBlkIdx = 0;
                int_StepCount++;
            }

            break;

        case 2: // Merge
            if(int_CheckBlkIdx < int_MSortIdx - int_SortIdx + 1 && int_RCheckBlkIdx < int_RSortIdx - int_MSortIdx)
            {
                if(deq_LBlk[int_CheckBlkIdx].int_Idx <= deq_RBlk[int_RCheckBlkIdx].int_Idx)
                {
                    deq_BlkArr[int_MSCheckBlkIdx] = deq_LBlk[int_CheckBlkIdx++];
                }
                else
                {
                    deq_BlkArr[int_MSCheckBlkIdx] = deq_RBlk[int_RCheckBlkIdx++];
                }

                deq_BlkArr[int_MSCheckBlkIdx].fn_SetColor(sf::Color::Red);
                deq_BlkArr[int_MSCheckBlkIdx].fn_SetXPos(int_MSCheckBlkIdx, int_BlkCount);
                deq_BlkArr[int_MSCheckBlkIdx].fn_SetRctPos();
            }
            else if(int_CheckBlkIdx < int_MSortIdx - int_SortIdx + 1)
            {
                deq_BlkArr[int_MSCheckBlkIdx] = deq_LBlk[int_CheckBlkIdx++];
            }
            else if(int_RCheckBlkIdx < int_RSortIdx - int_MSortIdx)
            {
                deq_BlkArr[int_MSCheckBlkIdx] = deq_RBlk[int_RCheckBlkIdx++];
            }
            else
            {
                stk_MIdx.pop();

                int_StepCount = 0;
            }

            if(!(int_CheckBlkIdx >= int_MSortIdx - int_SortIdx + 1 && int_RCheckBlkIdx >= int_RSortIdx - int_MSortIdx))
            {
                deq_BlkArr[int_MSCheckBlkIdx].fn_SetColor(sf::Color::Red);
                deq_BlkArr[int_MSCheckBlkIdx].fn_SetXPos(int_MSCheckBlkIdx, int_BlkCount);
                deq_BlkArr[int_MSCheckBlkIdx].fn_SetRctPos();
            }

            sptr_Context->uptr_Window->clear();
            sptr_Context->uptr_Window->draw(txt_SortName);
            sptr_Context->uptr_Window->draw(txt_ResetBtn);
            sptr_Context->uptr_Window->draw(txt_StartBtn);
            sptr_Context->uptr_Window->draw(txt_ReturnBtn);

            for(int i = 0; i < int_BlkCount; i++)
            {
                sptr_Context->uptr_Window->draw(deq_BlkArr[i].rct_Field);
            }

            sptr_Context->uptr_Window->display();

            if(!(int_CheckBlkIdx >= int_MSortIdx - int_SortIdx + 1 && int_RCheckBlkIdx >= int_RSortIdx - int_MSortIdx))
            {
                deq_BlkArr[int_MSCheckBlkIdx++].fn_SetColor();
            }

            break;
    }
}

void StartSort::fn_QuickSortLomuto()
{

}

void StartSort::fn_QuickSortHoare()
{

}

#endif // STARTSTATE_H_INCLUDED
