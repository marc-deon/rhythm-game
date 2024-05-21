#include <raylib.h>
#include "InputDisplay.hpp"

void InputDisplay::Draw() {
    const int screen_margin = 70;

    // DPAD Left
    DrawRectangle(
        screen_margin,  // x
        495,            // y
        19,             // w
        16,             // h
        IsKeyDown(KEY_LEFT) ? WHITE : GRAY
    );

    // DPAD UP
    DrawRectangle(
        89,         // x
        476,        // y
        16,         // w
        19,         // h
        IsKeyDown(KEY_UP) ? WHITE : GRAY
    );

    // DPAD RIGHT
    DrawRectangle(
        105,        // x
        495,        // y
        19,         // w
        16,         // h
        IsKeyDown(KEY_RIGHT) ? WHITE : GRAY
    );

    // DPAD Down
    DrawRectangle(
        89,         // x
        511,        // y
        16,         // w
        19,         // h
        IsKeyDown(KEY_DOWN) ? WHITE : GRAY
    );

    // KEY Z
    DrawRectangle(
        141,        // x
        485,        // y
        36,         // w
        36,         // h
        IsKeyDown(KEY_Z) ? GREEN : GRAY
    );

    // KEY X
    DrawRectangle(
        141+36+16,  // x
        485,        // y
        36,         // w
        36,         // h
        IsKeyDown(KEY_X) ? BLUE : GRAY
    );
}