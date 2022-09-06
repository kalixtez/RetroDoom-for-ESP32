#include <World.hpp>

void World::world_update()
{
    viewing_transform();
    player.update_pos(0);
}

void World::add_drawable(const Drawable nd)
{
    m_world_objects.push_back(nd);
}