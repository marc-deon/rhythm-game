#pragma once
#include "Scene.hpp"

enum SCENES {
    SCENE_MAINMENU,
    SCENE_METROHOP,
    SCENE_BATTER
};

namespace SceneManager {
    static Scene* currentScene = NULL;

    void ReplaceScene(SCENES scene);
    void ReplaceScene(Scene* scene);
    Scene* GetCurrent();
    // I don't know if I'll actually need these, so don't implement yet
    // void AddAsChild(SceneObject obj);

}