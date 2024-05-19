#include "UiElement.hpp"
#include "FocusStack.hpp"
#include <raylib.h>
#include <stdio.h>

void UiElement::Update() {
    // printf("    UiElement.Update\n");
    if (! FocusStack::IsFocused(this))
        return;
    
    // printf("Focused\n");
    if (IsKeyPressed(KEY_UP) && up)
        FocusStack::ChangeTo(up);
    else if (IsKeyPressed(KEY_DOWN) && down)
        FocusStack::ChangeTo(down);
    else if (IsKeyPressed(KEY_LEFT) && left)
        FocusStack::ChangeTo(left);
    else if (IsKeyPressed(KEY_RIGHT) && right)
        FocusStack::ChangeTo(right);
}
