#include <raylib.h>
#include "RhythmObject.hpp"
#include "Conductor.hpp"

class Metro_Light : public RhythmObject {
    private:
    Color color_active;
    Color color_inactive;
    Color color_current;
    float beat;

    public:

    ~Metro_Light();
    Metro_Light(Conductor* c, Color active, Color inactive, float beat);
    void Draw();
    // void Update();
};