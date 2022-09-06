#ifndef WORLD_H
#define WORLD_H

#include <cinttypes>
#include <Drawable.hpp>
#include <vector>
#include <Player.hpp>
#include <Arduino.h>
#include <cmath>

class World
{
    private:
        std::vector<Drawable> m_world_objects;
        
        float far = 0.1f;
        float near = 20.f;

        glm::mat4 projection_matrix = glm::mat4(
        glm::vec4(0.1f/(float)tan(30.0 * PI/360.0), 0.f, 0.f, 0.f), // not multiplied by 2PI because its half the angle.
        glm::vec4(0.f, 0.1f/(float)tan(22.5f * PI/360.0), 0.f, 0.f),
        glm::vec4(0.f, 0.f, -(far + near)/(far-near), -2*(far*near)/(far-near)),
        glm::vec4(0.f, 0.f, -1.f, 0.f));

        Player player;
        // Apply viewing transform to every drawable in the world, as if seen from the player's (camera) viewpoint.
        void viewing_transform()
        {
            for(Drawable& d : m_world_objects)
                d.model_view_proj(player.generate_view_matrix(), projection_matrix);
        }

    public:
        void world_update();
        void add_drawable(const Drawable);
    
};

#endif