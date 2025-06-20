#include "z3D/z3D.h"

s32 rSceneLayer;

void Scene_GetLoadedLayer(void** altHeaders) {
    if (altHeaders[gSaveContext.sceneLayer - 1] != NULL) {
        rSceneLayer = gSaveContext.sceneLayer;
    } else if (gSaveContext.sceneLayer == 3 && altHeaders[1] != NULL) {
        rSceneLayer = 2;
    } else {
        rSceneLayer = 0;
    }
}
