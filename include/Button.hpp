#pragma once
#include "SceneObject.hpp"
#include "UiElement.hpp"
#include <string>


class Button : public UiElement {
    public:

    int (*cb_onPress)();

};

class TextButton : public Button {
    public:
    std::string text;
    
    void Draw() override;
    int Update() override;
    TextButton(int x, int y, std::string text);
    TextButton(int x, int y, std::string text, int (*onPress)());
};