#pragma once
#include "Scene.hpp"

enum SCENES {
    SCENE_MAINMENU,
    SCENE_METROHOP,
    SCENE_BATTER,
    SCENE_MAX_COUNT
};

namespace SceneManager {
    

    void ReplaceScene(SCENES scene);
    void CheckToReplace();
    Scene* GetCurrent();
    // I don't know if I'll actually need these, so don't implement yet
    // void AddAsChild(SceneObject obj);

}