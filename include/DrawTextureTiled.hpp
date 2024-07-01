#include <raylib.h>

// Draw part of a texture (defined by a rectangle) with rotation and scale tiled into dest.
void DrawTextureTiled(Texture2D texture, Rectangle source, Rectangle dest, Vector2 origin, float rotation, float scale, Color tint);

// Draw entire texture without rotation but with X and Y offset
void DrawTextureTiled(Texture2D texture, Rectangle dest, Vector2 offset, float scale);