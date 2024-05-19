#pragma once
#include <vector>
#include "SceneObject.hpp"
#include "Button.hpp"
#include "FocusStack.hpp"

class Scene {

    public:
        const char* name;
        void* firstFocused;
        std::vector<SceneObject*> children;
        void virtual Update();
        void virtual Draw();
};

Scene* CreateScene_MainMenu();