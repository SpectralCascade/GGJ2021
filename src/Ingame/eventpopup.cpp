#include "eventpopup.h"
#include "GameController.h"

REGISTER_COMPONENT(EventPopup);

using namespace std;

void EventPopup::OnLoadFinish()
{
    game = entity->FindAndGetComponent<GameController>("Root");
    optionButtonsText[0] = entity->FindAndGetComponent<Text>("Opt1Text", entity);
    optionButtons[0] = entity->FindAndGetComponent<Button>("Opt1Button", entity);
    optionButtonsText[1] = entity->FindAndGetComponent<Text>("Opt2Text", entity);
    optionButtons[1] = entity->FindAndGetComponent<Button>("Opt2Button", entity);
    title = entity->FindAndGetComponent<Text>("Title", entity);
    description = entity->FindAndGetComponent<Text>("Description", entity);
    optionButtons[0]->OnClicked += [&] (Button& caller) { this->opt1(); Hide(); };
    optionButtons[1]->OnClicked += [&] (Button& caller) { this->opt2(); Hide(); };
}

void EventPopup::Show(string title, string desc, string opt1text, function<void()> opt1func)
{
    Show(title, desc, opt1text, opt1func, "", [] () {});
}

void EventPopup::Show(string title, string desc, string opt1text, function<void()> opt1func, string opt2text, function<void()> opt2func)
{
    fadingIn = true;
    fadingOut = false;

    auto renderer = entity->GetService<Renderer>();
    Vector2 dim = Vector2(renderer->GetWidth(), renderer->GetHeight());
    GetTransform()->SetLocalPosition(Vector2(0, dim.y));
    entity->SetActive(true);

    opt1 = opt1func;
    opt2 = opt2func;

    this->title->text = title;
    this->title->dirty = true;
    description->text = desc;
    description->dirty = true;

    optionButtonsText[0]->text = opt1text;
    optionButtonsText[0]->dirty = true;

    if (!opt2text.empty())
    {
        optionButtons[1]->GetEntity()->SetActive(true);
        optionButtonsText[1]->text = opt2text;
        optionButtonsText[1]->dirty = true;
        auto box = optionButtons[0]->GetEntity()->GetComponent<BoxLayout>();
        if (box->anchorMax.x != 0.5f)
        {
            box->anchorMax.x = 0.5f;
            box->LayoutRefresh();
        }
        optionButtons[1]->GetEntity()->SetActive(true);
    }
    else
    {
        optionButtons[1]->GetEntity()->SetActive(false);
        auto box = optionButtons[0]->GetEntity()->GetComponent<BoxLayout>();
        box->anchorMax.x = 0.98f;
        box->LayoutRefresh();
    }

    fadeTimer.Start();
}

void EventPopup::Hide()
{
    fadingOut = true;
    fadingIn = false;

    fadeTimer.Start();
    entity->SetActive(false);
}

void EventPopup::Update()
{
    /*static bool firstUpdate = true;
    if (firstUpdate)
    { 
        // Hacky fix for positioning
        originalPositions[0] = GetTransform()->GetLocalPosition();
        originalPositions[1] = optionButtons[0]->GetTransform()->GetLocalPosition();
        originalPositions[2] = optionButtons[1]->GetTransform()->GetLocalPosition();
        originalPositions[3] = optionButtonsText[0]->GetTransform()->GetLocalPosition();
        originalPositions[4] = optionButtonsText[1]->GetTransform()->GetLocalPosition();
        originalPositions[5] = title->GetTransform()->GetLocalPosition();
        originalPositions[6] = description->GetTransform()->GetLocalPosition();

        for (int i = 0; i < 7; i++)
        {
            Log.Info("Original position {0} = {1}", i, originalPositions[i]);
        }

        firstUpdate = false;
    }

    if ((fadingIn || fadingOut) && fadeTimer.IsStarted())
    {
        auto renderer = entity->GetService<Renderer>();
        Vector2 dim = Vector2(renderer->GetWidth(), renderer->GetHeight());
        Vector2 target = Vector2::Zero;
        Vector2 origin = Vector2(0, dim.y);
        if (fadingIn)
        {
            fadingOut = false;
        }
        else
        {
            // Swap
            dim = target;
            target = origin;
            origin = dim;
        }
        float seconds = (float)fadeTimer.GetTicks() / 1000.0f;
        float delay = 0.5f;

        //entity->Find("EventPopupChild", entity)->GetTransform()->SetWorldPosition(originalPositions[0] + origin.Lerp(target, seconds / delay));
        optionButtons[0]->GetTransform()->SetLocalPosition(originalPositions[1] + origin.Lerp(target, seconds / delay));
        optionButtons[1]->GetTransform()->SetLocalPosition(originalPositions[2] + origin.Lerp(target, seconds / delay));
        optionButtonsText[0]->GetTransform()->SetLocalPosition(originalPositions[3] + origin.Lerp(target, seconds / delay));
        optionButtonsText[1]->GetTransform()->SetLocalPosition(originalPositions[4] + origin.Lerp(target, seconds / delay));
        title->GetTransform()->SetLocalPosition(originalPositions[5] + origin.Lerp(target, seconds / delay));
        description->GetTransform()->SetLocalPosition(originalPositions[6] + origin.Lerp(target, seconds / delay));

        if (seconds >= delay)
        {
            fadeTimer.Stop();
            fadingIn = false;
            fadingOut = false;
        }

    }*/
}
