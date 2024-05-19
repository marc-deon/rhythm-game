#pragma once
#include <vector>

namespace FocusStack {
//private:
    static std::vector<void*> focusStack;

//public:
    void Push(void* p);
    void Pop(void* p);
    void PopUntil(void* p);
    bool IsFocused(void* p);
    bool IsNotFocused(void* p);
    void ChangeTo(void* p);
    void Clear();
}