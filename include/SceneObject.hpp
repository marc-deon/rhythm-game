#pragma once
#include <vector>

class SceneObject {
    public:
        int x;
        int y;
        std::vector<SceneObject> children;
        virtual void Update();
        virtual void Draw();
    };