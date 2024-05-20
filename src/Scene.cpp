#include "Scene.hpp"
#include <raylib.h>

Scene::~Scene() {
    for (auto child : children) {
        delete child;
    }
}

void Scene::Update() {
    for (auto child : children) {
        child->Update();
    }
}

void Scene::Draw() {
    ClearBackground(BLACK);
    for (auto child : children) {
        child->Draw();
    }
}
