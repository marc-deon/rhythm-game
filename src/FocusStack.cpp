#include "FocusStack.hpp"

namespace FocusStack {
    void Push(void* p) {
        focusStack.push_back(p);
    }

    void* Pop() {
        auto p = focusStack.back();
        focusStack.pop_back();
        return p;
    }

    void PopUntil(void* p) {
        while (focusStack.back() != p) {
            focusStack.pop_back();
        };
    }

    bool IsFocused(void* p) {
        return focusStack.back() == p;
    }

    bool IsNotFocused(void* p) {
        return focusStack.back() != p;
    }

    void ChangeTo(void* p) {
        focusStack.pop_back();
        focusStack.push_back(p);
    }

    void Clear() {
        // for (auto p : focusStack) {
        //     free(p);
        // }
        
        focusStack.clear();
    }
}