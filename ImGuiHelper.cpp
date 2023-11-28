#include"ImGuiHelper.h"
#include"Globals.h"

void RenderImGuiGeneralControls() {

    // Create a window and add controls
    ImGui::Begin("Controls");

    // Toggle axes
    if (ImGui::Button(axes ? "Hide Axes" : "Show Axes")) {
        axes = !axes;
    }

    // Toggle lighting
    if (ImGui::Button(light ? "Turn Off Lighting" : "Turn On Lighting")) {
        light = !light;
    }

    // Switch projection mode
    if (ImGui::Button(mode ? "Perspective Projection" : "Orthogonal Projection")) {
        mode = !mode;
    }

    // Toggle light movement
    if (ImGui::Button(move ? "Stop Light Movement" : "Start Light Movement")) {
        move = !move;
    }


    // Change field of view angle
    ImGui::SliderInt("Field of View", &fov, 1, 179);

    // Switch scene/object
    if (ImGui::Button("Next Object")) {
        obj = (obj + 1) % 3;
    }
    if (ImGui::Button("Previous Object")) {
        obj = (obj + 2) % 3;
    }

    // Terrain controls
    ImGui::Text("Terrain Controls");
    ImGui::SliderFloat("Scale", &uScale, 1.0f, 10.0f);
    ImGui::SliderFloat("Persistence", &uPersistence, 0.1f, 10.0f);
    ImGui::SliderFloat("Lacunarity", &uLacunarity, 1.1f, 10.0f);
    ImGui::SliderFloat("Exponentiation", &uExponentiation, 1.0f, 10.0f);
    ImGui::SliderFloat("Height", &uHeight, 1.0f, 10.0f);
    ImGui::SliderInt("Octaves", &uOctaves, 1, 10);
    ImGui::SliderInt("Tile Size", &uTileSize, 1, 10);
    ImGui::SliderInt("Plane Size", &planeSize, 1, 20);

    // End the ImGui frame
    ImGui::End();
}

