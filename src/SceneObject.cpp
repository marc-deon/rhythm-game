#include "SceneObject.hpp"
#include "stdio.h"

void SceneObject::Update() {
    for (auto child : children) {
        child.Update();
    }
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