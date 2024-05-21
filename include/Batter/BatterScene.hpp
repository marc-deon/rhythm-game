#include "Scene.hpp"
#include <raylib.h>
#include "Conductor.hpp"
#include "StreamConductor.hpp"
#include "RhythmObject.hpp"
#include "BeatmapWithVisualizer.hpp"
#include "Baseball.hpp"
#include "Batter.hpp"
#include "Metronome.hpp"
#include "InputDisplay.hpp"

class BatterScene : public Scene {
    private:
    bool should_display_score = false;
    bool perfect = true;
    float score = 0;
    const float maxScore = 56 * 2;
    const float score_threshhold_great = .90;
    const float score_threshhold_ok    = .60;

    Sound se_bad = LoadSound("sfx/game_button.mp3");
    Sound se_good = LoadSound("sfx/good.mp3");
    Sound se_perfect = LoadSound("sfx/perfect.mp3");

    StreamConductor conductor = StreamConductor("music/airbatter.ogg");
    BeatmapWithVisualizer beatmap = BeatmapWithVisualizer(&conductor, "beatmaps/airbatter-shortlong-quantized.bm");
    Metronome metronome = Metronome(&conductor);
    Batter batter;
    Baseball baseball;
    InputDisplay inputdisplay;

    void DisplayScore(); // After player loses, swap to a subscene that just shows score

    public:
    void Update() override;
    void Draw() override;
    BatterScene();
    ~BatterScene();

};