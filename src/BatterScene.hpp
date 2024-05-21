#include "Scene.hpp"
#include <raylib.h>
#include "Conductor.hpp"
#include "StreamConductor.hpp"
#include "RhythmObject.hpp"
#include "BeatmapWithVisualizer.hpp"
#include "Baseball.hpp"
#include "Batter.hpp"
#include "Metronome.hpp"

class BatterScene : public Scene {
    private:
    bool perfect = true;
    int score;
    int maxScore;
    int score_great;
    int score_ok;
    int score_bad;

    Sound se_bad = LoadSound("sfx/game_button.mp3");
    Sound se_good = LoadSound("sfx/good.mp3");
    Sound se_perfect = LoadSound("sfx/perfect.mp3");

    StreamConductor conductor = StreamConductor("music/airbatter.ogg");
    BeatmapWithVisualizer beatmap = BeatmapWithVisualizer(&conductor, "beatmaps/airbatter-shortlong-quantized.bm");
    Metronome metronome = Metronome(&conductor);
    Batter batter;
    Baseball baseball;
    
    void DisplayScore(); // After player loses, swap to a subscene that just shows score

    public:
    int Update() override;
    void Draw() override;
    BatterScene();
    ~BatterScene();

};