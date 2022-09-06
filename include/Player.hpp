#ifndef PLAYER_H
#define PLAYER_H

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/matrix.hpp>
#include <Arduino.h>
#include <cmath>

class Player
{
    private:
        glm::vec3 m_player_pos = glm::vec3{0.0f, 0.0f, 5.0f};
        glm::vec3 m_look_dir = glm::vec3{0.0f, 0.0f, -1.0f};
        glm::vec3 m_player_speed = glm::vec3{0.0f, 0.0f, 0.0f};
        glm::vec3 m_up_ref = glm::vec3{0.0f, 1.0f, 0.0f};

    public:
        glm::mat4 generate_view_matrix();
        void update_pos(float timedelta);
        void update_dir(glm::vec2 joystic_input);

        void handle_input();
};

#endif