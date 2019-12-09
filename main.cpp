#include <iostream>

#include "sdlgl/graphics/graphics.h"
#include <sdlgl/game/clock.h>
#include <sdlgl/game/scene.h>
#include <sdlgl/input/inputs.h>
#include <stdlib.h>
#include <time.h>

#include <sdlgl/ui/fps_display.h>
#include <sdlgl/ui/entity_count.h>

#include "entities/knight.h"


#define KEY_TOGGLE_DEBUG_VISUALS SDL_SCANCODE_TILDE


int main() {

    srand(time(NULL));

    Clock clock;
    Inputs inputs;

    // Load a window
    Graphics graphics(640, 480);

    // Load resources
    graphics.get_resources()->load_resources("resources.json");

    // Create and populate scene
    Scene scene(&inputs, &graphics);
    scene.add_entity(new FPS_Display(
        &scene, "base_text", {0, 0, 0, 255}));
    scene.add_entity(new EntityCount(
        &scene, "base_text", {0, 0, 0, 255}));
    scene.add_entity(new Knight(
        &scene, 100, 100, {255, 255, 255, 255}));

    // Enter a simple update loop
    bool loop = true;
    while (loop) {

        inputs.update();
        clock.tick();
        graphics.clear_screen({255, 255, 255, 255});
        
        scene.update(clock.get_delta());
        scene.render();

        graphics.present_renderer(clock.get_delta());

        // If ESC or 'X' button is pressed, leave the update loop and exit
        if (inputs.get_quit()) {
            loop = false;
        }

        // If tilde key is pressed, toggle debug visuals
        if (inputs.is_key_down_event(SDL_SCANCODE_GRAVE)) {
            graphics.toggle_debug_visuals();
        }

    }

    return 0;
}
