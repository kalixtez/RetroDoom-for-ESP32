#include <Player.hpp>

glm::mat4 Player::generate_view_matrix()
{
	glm::vec3 s = glm::normalize(glm::cross(m_look_dir, glm::vec3(0.0f, 1.0f, 0.0f)));
	glm::vec3 u = glm::normalize(glm::cross(s, m_look_dir));

	glm::mat4 viewm = glm::mat4(glm::vec4(s, 0.f), glm::vec4(u, 0.f), glm::vec4(-m_look_dir, 0.f), glm::vec4(0, 0, 0, 1.0f));
	viewm = glm::transpose(viewm);

    viewm = viewm * glm::mat4(glm::vec4(1.f, 0.f, 0.f, 0.f),
                      glm::vec4(0.f, 1.f, 0.f, 0.f),
                      glm::vec4(0.f, 0.f, 1.f, 0.f),
                      glm::vec4(-m_player_pos.x, -m_player_pos.y, -m_player_pos.z, 1.f)) ;
    return viewm;
}

void Player::update_pos(float timedelta)
{
    static float a = 0;
    m_player_pos = glm::vec3(cos(a*2 * PI/360.0f)*5, 0, sin(a*2 * PI/360.0f)*5);
    m_look_dir = glm::normalize(glm::vec3(0.f, 0.f, 0.f) - m_player_pos);
    a += 5.f;
    if(a > 360)
        a = 0.f;
}

void Player::update_dir(glm::vec2 joystic_input)
{
    // Rotation around the Y axis (pitch)
    glm::vec2 arch = joystic_input * float((1/4096)) * float(2 * PI);
    glm::mat3 rotY(glm::vec3(
    cos(arch.x), 0.f, -sin(arch.x)),
    glm::vec3(0.f, 1.f, 0.f),
    glm::vec3(sin(arch.x), 0, cos(arch.x)));
    
    // Rotation around the X axis matrix (Yaw)
    glm::mat3 rotX(
    glm::vec3(1.f, 0.f, 0.f),
    glm::vec3(0.f, cos(arch.y), sin(arch.y)),
    glm::vec3(-sin(arch.y), 0, cos(arch.y)));

    m_look_dir = rotY * (rotX * m_look_dir); // Update the direction vector according to the joystic movements.
    
}

void Player::handle_input()
{

}