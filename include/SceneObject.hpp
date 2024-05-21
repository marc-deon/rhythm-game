#pragma once
#include <vector>

class SceneObject {
    public:
        int x;
        int y;
        std::vector<SceneObject> children;
        virtual int Update();
        virtual void Draw();
        virtual ~SceneObject();
    };