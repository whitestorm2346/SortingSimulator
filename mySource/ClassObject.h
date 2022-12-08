#ifndef CLASSOBJECT_H_INCLUDED
#define CLASSOBJECT_H_INCLUDED

#include <cstdlib>
#include <ctime>
#include <set>
#include <deque>

#define int_WinHeight static_cast<float>(600)
#define int_WinWidth static_cast<float>(1200)

namespace sf
{
    struct Button
    {
        sf::Text txt_Name;
        bool bl_IsSelected;
        bool bl_IsPressed;

        Button()
        {
            bl_IsSelected = false;
            bl_IsPressed = false;
        }
        ~Button(){}
    };
}

namespace obj
{
    class Block
    {
        float flt_Width;
        float flt_Height;
        sf::Color clr_Field;

    public:
        sf::RectangleShape rct_Field;
        float flt_XPos;
        float flt_YPos;
        int int_Idx;

        Block()
        {
            flt_Height = 0;
            flt_Width = 0;
            flt_XPos = 0;
            flt_YPos = 0;
            int_Idx = 0;
        }

        void fn_SetColor(sf::Color clr_Field = sf::Color::White)
        {
            this->clr_Field = clr_Field;

            rct_Field.setFillColor(clr_Field);
        }
        void fn_SetIdx(int int_Idx)
        {
            this->int_Idx = int_Idx;
        }
        void fn_SetSize(int int_Idx, int int_BlkCount)
        {
            flt_Width  = int_WinWidth / int_BlkCount;
            flt_Height = (int_Idx + 1) * (int_WinHeight / int_BlkCount);

            rct_Field.setSize(sf::Vector2f(flt_Width, flt_Height));
        }
        void fn_SetXPos(int int_Idx, int int_BlkCount)
        {
            flt_XPos = int_Idx * (int_WinWidth / int_BlkCount);
        }
        void fn_SetYPos(int int_Idx, int int_BlkCount)
        {
            flt_YPos = (int_WinHeight + 100) - (int_Idx + 1) * (int_WinHeight / int_BlkCount);
        }
        void fn_SetRctPos()
        {
            rct_Field.setPosition(sf::Vector2f(flt_XPos, flt_YPos));
        }
    };

    struct MergeSortIdx
    {
        int int_Start;
        int int_Mid;
        int int_End;
    };
}

namespace fn
{
    void PresetBlk(std::deque<obj::Block>& blk_Arr, int int_Size)
    {
        for(int i = 0; i < int_Size; i++)
        {
            blk_Arr[i].fn_SetColor();
            blk_Arr[i].fn_SetIdx(i);
            blk_Arr[i].fn_SetSize(i, int_Size);
            blk_Arr[i].fn_SetXPos(i, int_Size);
            blk_Arr[i].fn_SetYPos(i, int_Size);
            blk_Arr[i].fn_SetRctPos();
        }
    }

    void RandomBlk(std::deque<obj::Block>& blk_Arr, int int_Size)
    {
        std::srand(std::time(nullptr));

        std::set<int> set_Num;

        for(int i = 0, int_RandNum; i < int_Size; i++)
        {
            do
            {
                int_RandNum = rand() % int_Size;
            }
            while(set_Num.count(int_RandNum));

            set_Num.insert(int_RandNum);

            blk_Arr[i].int_Idx = int_RandNum;
            blk_Arr[i].fn_SetXPos(i, int_Size);
            blk_Arr[i].fn_SetYPos(int_RandNum, int_Size);
            blk_Arr[i].fn_SetSize(int_RandNum, int_Size);
            blk_Arr[i].fn_SetRctPos();
        }
    }
}

#endif // CLASSOBJECT_H_INCLUDED
