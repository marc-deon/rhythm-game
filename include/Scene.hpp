#pragma once
#include <vector>
#include "SceneObject.hpp"
#include "Button.hpp"
#include "FocusStack.hpp"

class Scene {

    public:
        const char* name;
        void* firstFocused; // First UI object to be focused on (if any).
        std::vector<SceneObject*> children;
        void virtual Update();
        void virtual Draw();
        virtual ~Scene();
};

Scene* CreateScene_MainMenu();