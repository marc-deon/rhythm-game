#include "Scene.hpp"
#include <raylib.h>

Scene::~Scene() {
    for (auto child : children) {
        delete child;
    }
    children.clear();
}

int Scene::Update() {
    for (auto child : children) {
        // Return -1 when this loop is no longer valid (e.g. switching scenes)
        auto val = child->Update();
        if (val)
            return val;
    }
    return 0;
}

void Scene::Draw() {
    ClearBackground(BLACK);
    for (auto child : children) {
        child->Draw();
    }
}
