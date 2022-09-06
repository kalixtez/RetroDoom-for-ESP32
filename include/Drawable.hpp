#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <cinttypes>
#include <glm/vec3.hpp>
#include <glm/matrix.hpp>
#include <vector>
#include <array>
#include <utility>
#include <Driver.hpp>
#include <TriangleRasterizer.hpp>

// Inherits from triangle, the reason for this is that some drawables will possess a texture while others will not. With this m_trigs could be an array of coloredTriangles or an array of normal Triangles.
struct Triangle
{
    public:
        typedef std::pair<glm::vec3, std::array<float, 0>> GenericVertices;
        std::array<GenericVertices, 3> vertices;
        //int vertex_attr;


        Triangle(GenericVertices v1, GenericVertices v2, GenericVertices v3)
        {
            vertices[0] = v1;
            vertices[1] = v2;
            vertices[2] = v3;
        }

};


class Drawable
{
    private:
        std::vector<Triangle> m_trigs;

    public:
        glm::vec3 m_pos;
        
        Drawable(glm::vec3 model_pos)
        {

        }

        Drawable(glm::vec3 model_pos, std::initializer_list<Triangle> trig_list);
        // Apply the model_view transformation to the drawable in question. View transformation is calculated based on the player position and direction of vision.
        void model_view_proj(glm::mat4 cam_matrix, glm::mat4 proj_matrix);

};

#endif