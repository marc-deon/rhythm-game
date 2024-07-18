#include "Scene.hpp"
#include <raylib.h>
#include "Conductor.hpp"
#include "StreamConductor.hpp"
#include "RhythmObject.hpp"
#include "BeatmapWithVisualizer.hpp"
#include "Metronome.hpp"
#include "InputDisplay.hpp"

class FlystarScene : public Scene {
    private:
    const int junna = 36;
    const int nana = 39;

    bool should_display_score = false;
    bool perfect = true;
    float score = 0;
    const float maxScore = 148 * 2;
    const float score_threshhold_great = .90;
    const float score_threshhold_ok    = .60;

    Sound se_bad = LoadSound("sfx/game_button.mp3");
    Sound se_good = LoadSound("sfx/good.mp3");
    Sound se_perfect = LoadSound("sfx/perfect.mp3");

    StreamConductor conductor = StreamConductor("music/flystar.ogg");
    BeatmapWithVisualizer beatmap = BeatmapWithVisualizer(&conductor, "fly me to the star.bm");
    Metronome metronome = Metronome(&conductor);

    InputDisplay inputdisplay;

    void DisplayScore(); // After player loses, swap to a subscene that just shows score

    public:
    void Update() override;
    void Draw() override;
    void CheckAndScore(KeyboardKey key, int subtype);
    FlystarScene();
    ~FlystarScene();

};