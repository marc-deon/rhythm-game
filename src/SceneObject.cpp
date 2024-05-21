#include "SceneObject.hpp"
#include "stdio.h"

int SceneObject::Update() {
    for (auto child : children) {
        auto val = child.Update();
        if (val)
            return val;
    }
    return 0;
}


void SceneObject::Draw() {
    for (auto child : children) {
        child.Draw();
    }
}

SceneObject::~SceneObject() {
    for (auto child : children) {
        delete &child;
    }
    children.clear();
}