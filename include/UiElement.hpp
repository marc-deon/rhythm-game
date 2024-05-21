#pragma once
#include "SceneObject.hpp"

class UiElement : public SceneObject {
    public:
    UiElement *up = NULL;
    UiElement *down = NULL;
    UiElement *left = NULL;
    UiElement *right = NULL;

    int virtual Update();
};
