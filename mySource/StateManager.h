#ifndef STATEMANAGER_H_INCLUDED
#define STATEMANAGER_H_INCLUDED

#include <stack>
#include <memory>
#include "State.h"

namespace eng
{
    class StateMan
    {
        std::stack<std::unique_ptr<State> > stk_State;
        std::unique_ptr<State> uptr_State;
        bool bl_Add;
        bool bl_Replace;
        bool bl_Remove;

    public:
        StateMan()
        {
            bl_Add = bl_Remove = bl_Replace = false;
        }
        ~StateMan(){}

        void Add(std::unique_ptr<State> uptr_Add, bool bl_Replace = false)
        {
            bl_Add = true;
            uptr_State = std::move(uptr_Add);

            this->bl_Replace = bl_Replace;
        }
        void Pop()
        {
            bl_Remove = true;
        }
        void ChangeState()
        {
            if(bl_Remove && !stk_State.empty())
            {
                stk_State.pop();
            }

            if(bl_Add)
            {
                if(bl_Replace && !stk_State.empty())
                {
                    stk_State.pop();
                    bl_Replace = false;
                }

                stk_State.push(std::move(uptr_State));
                stk_State.top()->Init();
                bl_Add = false;
            }
        }
        std::unique_ptr<State>& GetCurr()
        {
            return stk_State.top();
        }
    };
}

#endif // STATEMANAGER_H_INCLUDED
