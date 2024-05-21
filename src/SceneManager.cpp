#include "SceneManager.hpp"
#include "Metrohop/Metrohop.hpp"
#include "Batter/BatterScene.hpp"


namespace SceneManager {
    static Scene* currentScene = NULL;
    static Scene* nextScene = NULL;

    // Main menu button callback
    void cb_Metrohop() {
        SceneManager::ReplaceScene(SCENE_METROHOP);
    }

    // Main menu button callback
    void cb_Batter() {
        SceneManager::ReplaceScene(SCENE_BATTER);
        
    }

    Scene* CreateScene_MainMenu() {
        Scene* s = new Scene();
        s->name = "Main Menu";
        auto b1 = new TextButton(200, 300-10, "Metrohop", cb_Metrohop);
        auto b2 = new TextButton(600, 300-10, "Batter", cb_Batter);
        b1->right = b2;
        b2->left = b1;
        s->children.push_back(b1);
        s->children.push_back(b2);
        s->firstFocused = b1;
        return s;
    }

    void CheckToReplace() {
        // Check if we should swap
        if (nextScene == NULL)
            return;
        
        // This is supposedly safe to do even if null
        delete currentScene;
        
        // Do the swap
        currentScene = nextScene;

        // Reset nextScene so this doesn't run twice in a row
        nextScene = NULL;

        // We don't need to deallocate anything in the FS; that's handled above
        FocusStack::Clear();
        FocusStack::Push(currentScene->firstFocused);
    }

    // Queue scene replacement by enum
    void ReplaceScene(SCENES scene) {
        switch (scene) {
            case SCENE_MAINMENU:
                nextScene = CreateScene_MainMenu();
                break;
            case SCENE_METROHOP:
                nextScene = new Metrohop();
                break;
            case SCENE_BATTER:
                nextScene = new BatterScene();
                break;
            default:
                exit(1);
        }
    }

    Scene* GetCurrent() {
        return currentScene;
    }
}
