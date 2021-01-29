#include "PlacementButton.h"

REGISTER_COMPONENT(PlacementButton);

void PlacementButton::OnPointerMove()
{
    Vector2 pos = GetLastMousePosition();
    if (!isPlacing && IsPressed())
    {
        // Must be dragging
        isPlacing = true;
        isDragging = true;
        OnPlaceBegin(pos);
    }
    else if (isPlacing)
    {
        OnPlaceMove(pos);
    }
}

void PlacementButton::OnPointerUp()
{
    Button::OnPointerUp();
    if (isDragging || !IsHovered())
    {
        isDragging = false;
        isPlacing = false;
        Vector2 pos = GetLastMousePosition();
        OnPlaceEnd(pos);
    }
}

void PlacementButton::OnClick()
{
    Button::OnClick();
    if (supportClickAndPlace)
    {
        isPlacing = !isPlacing;

        Vector2 pos = GetLastMousePosition();
        isPlacing ? OnPlaceBegin(pos) : OnPlaceEnd(pos);
    }
    else
    {
        isDragging = false;
        isPlacing = false;
    }
}

void PlacementButton::OnPointerEvent(const MouseInput& data)
{
    bool wasDragging = isDragging;
    Button::OnPointerEvent(data);

    // Check for click release outside of the button
    if (supportClickAndPlace && !wasDragging && !isDragging && isPlacing && !IsHovered() && data.type == MOUSE_BUTTON_LEFT && !data.state)
    {
        Vector2 mpos = GetLastMousePosition();
        OnPlaceEnd(mpos);
        isDragging = false;
        isPlacing = false;
    }
}
