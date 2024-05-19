#include "SceneObject.hpp"
#include "stdio.h"

void SceneObject::Update() {
    // printf("SceneObject.Update");
    for (auto child : children) {
        child.Update();
    }
}


void SceneObject::Draw() {
    // printf("so.draw \n");
    for (auto child : children) {
        child.Draw();
    }
}

