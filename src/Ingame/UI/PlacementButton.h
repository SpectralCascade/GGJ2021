#ifndef PLACEMENTBUTTON_H
#define PLACEMENTBUTTON_H

#include <Ossium.h>

using namespace Ossium;

struct PlacementButtonSchema : public Schema<PlacementButtonSchema, 20>
{
    DECLARE_BASE_SCHEMA(PlacementButtonSchema, 20);

    M(bool, supportClickAndPlace) = false;

};

/// A special type of button that spawns an entity with a PlacementButton component
/// TODO: Transfer to Ossium if feasible.
class PlacementButton : public Button, public PlacementButtonSchema
{
public:
    CONSTRUCT_SCHEMA(Button, PlacementButtonSchema);
    DECLARE_COMPONENT(Button, PlacementButton);

    // Called when the pointer is released after interacting with this button.
    // Value passed is the pointer position, corrected for the current viewport.
    Callback<Vector2> OnPlaceBegin;
    // Called when the pointer moves after placement has started.
    // Value passed is the pointer position, corrected for the current viewport.
    Callback<Vector2> OnPlaceMove;
    // Called when the pointer is released (or clicked again).
    // Value passed is the pointer position, corrected for the current viewport.
    Callback<Vector2> OnPlaceEnd;

protected:
    void OnPointerMove();
    void OnPointerUp();
    void OnClick();

    // Override required to handle mouse click off the button.
    void OnPointerEvent(const MouseInput& data);

private:
    // Is the pointer being dragged across the screen?
    bool isDragging = false;
    // Is a placement in progress?
    bool isPlacing = false;

};

#endif // PLACEMENTBUTTON_H
