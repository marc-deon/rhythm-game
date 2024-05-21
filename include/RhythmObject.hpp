#pragma once

#include "Conductor.hpp"
#include "SceneObject.hpp"

class RhythmObject : public SceneObject {
    public:
    Conductor* conductor;
};