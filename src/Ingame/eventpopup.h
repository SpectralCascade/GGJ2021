#ifndef EVENTPOPUP_H
#define EVENTPOPUP_H

#include <Ossium.h>

using namespace Ossium;

struct EventPopupSchema : public Schema<EventPopupSchema, 20>
{
    DECLARE_BASE_SCHEMA(EventPopupSchema, 20);
    
};

class GameController;

class EventPopup : public Component, public EventPopupSchema
{
public:
    CONSTRUCT_SCHEMA(Component, EventPopupSchema);
    DECLARE_COMPONENT(Component, EventPopup);
    
    void OnLoadFinish();

    void Show(std::string title, std::string desc, std::string opt1text, std::function<void()> opt1func);
    void Show(std::string title, std::string desc, std::string opt1text, std::function<void()> opt1func, std::string opt2text, std::function<void()> opt2func);
    void Hide();

    void Update();
    
private:
    std::function<void()> opt1;
    std::function<void()> opt2;

    GameController* game = nullptr;

    Timer fadeTimer;

    bool fadingIn = false;
    bool fadingOut = false;

    Text* title = nullptr;
    Text* description = nullptr;

    Button* optionButtons[2] = {nullptr, nullptr};
    Text* optionButtonsText[2] = {nullptr, nullptr};

    // Hacky fix
    Vector2 originalPositions[7];

};


#endif // EVENTPOPUP_H
