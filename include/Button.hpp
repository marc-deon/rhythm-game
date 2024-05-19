#pragma once
#include "SceneObject.hpp"
#include "UiElement.hpp"
#include <string>


class Button : public UiElement {
    public:

    void (*cb_onPress)();

};

class TextButton : public Button {
    public:
    std::string text;
    
    void Draw() override;
    void Update() override;
    TextButton(int x, int y, std::string text);
    TextButton(int x, int y, std::string text, void (*onPress)());
};