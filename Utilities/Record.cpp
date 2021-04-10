#include "Constants.h"
#include "Record.h"

Record::Record(Scene& scene):
    colided(false),
    material_ptr(nullptr),
    sceneHit(),
    localHit(),
    sceneNormal(),
    col(black),
    sceneRay(),
    lightDir(),
    sceneRef(scene),
    t(0.0),
    u(0.0),
    v(0.0)
{}

Record::Record(const Record& recentHits):
    colided(recentHits.colided),
    material_ptr(recentHits.material_ptr),
    sceneHit(recentHits.sceneHit),
    localHit(recentHits.localHit),
    sceneNormal(recentHits.sceneNormal),
    col(recentHits.col),
    sceneRay(recentHits.sceneRay),
    lightDir(recentHits.lightDir),
    sceneRef(recentHits.sceneRef),
    t(recentHits.t),
    u(recentHits.u),
    v(recentHits.v)
{}

Record::~Record()
{}