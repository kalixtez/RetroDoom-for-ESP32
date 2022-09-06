#include <Drawable.hpp>

extern TrigRasterizer _main_rasterizer;

Drawable::Drawable(glm::vec3 model_pos, std::initializer_list<Triangle> trig_list):
            m_pos(model_pos)
        {
            for(const Triangle& trig : trig_list) // Initialize the triangle array with the initializer list.
                m_trigs.push_back(trig);
        }

void Drawable::model_view_proj(glm::mat4 cam_matrix, glm::mat4 proj_matrix)
        {
            glm::mat4 mvp = proj_matrix * cam_matrix * glm::mat4(glm::vec4(1.0f, 0.f, 0.f, 0.f), glm::vec4(0.f, 1.f, 0.f, 0.f), glm::vec4(0.f, 0.f, 1.f, 0.f), glm::vec4(m_pos, 1.f)); // Model view matrix specific to the model.
            for(const Triangle& trig : m_trigs)
            {
                    glm::vec4 projected = mvp * glm::vec4(trig.vertices[0].first, 1.0f);
                    glm::vec3 perspective_divided = glm::vec3(projected.x/projected.w, projected.y/projected.w, projected.z/projected.w);
                    float dz0 = perspective_divided.z;
                    /*
                    Serial.print("VERTEX 0:\n\n");

                    Serial.print("Before projection:\n");

                    Serial.print("X: ");
                    Serial.println(trig.vertices[0].first.x);
                    Serial.print("Y: ");
                    Serial.println(trig.vertices[0].first.y);
                    Serial.print("Z: ");
                    Serial.println(trig.vertices[0].first.z);

                    Serial.print("Proj0 W: ");
                    Serial.println(projected.w);

                    Serial.print("Proj0 X: ");
                    Serial.println(perspective_divided.x);
                    Serial.print("Proj0 Y:");
                    Serial.println(perspective_divided.y);
                    Serial.print("Proj0 Z: ");
                    Serial.println(perspective_divided.z);
                    */

                    uint8_t px = (uint8_t)((perspective_divided.x + 1) * 83/2);
                    uint8_t py = (uint8_t)((perspective_divided.y + 1) * 47/2);

                    /*
                    Serial.print("V0 X: ");
                    Serial.println(px);

                    Serial.print("V0 Y: ");
                    Serial.println(py);

                    Serial.print("\n\n");
                   

                    */
                    projected = mvp * glm::vec4(trig.vertices[1].first, 1.0f);
                    perspective_divided = glm::vec3(projected.x/projected.w, projected.y/projected.w, projected.z/projected.w);
                    float dz1 = perspective_divided.z;
                    /*
                    Serial.print("VERTEX 1:\n\n");

                    Serial.print("Before projection:\n");

                    Serial.print("X: ");
                    Serial.println(trig.vertices[1].first.x);
                    Serial.print("Y: ");
                    Serial.println(trig.vertices[1].first.y);
                    Serial.print("Z: ");
                    Serial.println(trig.vertices[1].first.z);

                    Serial.print("Proj1 W: ");
                    Serial.println(projected.w);

                    Serial.print("Proj1 X: ");
                    Serial.println(perspective_divided.x);
                    Serial.print("Proj1 Y:");
                    Serial.println(perspective_divided.y);
                    Serial.print("Proj1 Z: ");
                    Serial.println(perspective_divided.z);
                    */

                    uint8_t px1 = (uint8_t)((perspective_divided.x + 1) * 83/2);
                    uint8_t py1 = (uint8_t)((perspective_divided.y + 1) * 47/2);

                    /*
                    Serial.print("V1 X: ");
                    Serial.println(px1);

                    Serial.print("V1 Y: ");
                    Serial.println(py1);

                    Serial.print("\n\n");
                    */

                    projected = mvp * glm::vec4(trig.vertices[2].first, 1.0f);
                    perspective_divided = glm::vec3(projected.x/projected.w, projected.y/projected.w, projected.z/projected.w);
                    float dz2 = perspective_divided.z;

                    /*
                    Serial.print("VERTEX 2:\n\n");

                    Serial.print("Before projection:\n");

                    Serial.print("X: ");
                    Serial.println(trig.vertices[2].first.x);
                    Serial.print("Y: ");
                    Serial.println(trig.vertices[2].first.y);
                    Serial.print("Z: ");
                    Serial.println(trig.vertices[2].first.z);

                    Serial.print("Proj2 W: ");
                    Serial.println(projected.w);

                    Serial.print("Proj2 X: ");
                    Serial.println(perspective_divided.x);
                    Serial.print("Proj2 Y:");
                    Serial.println(perspective_divided.y);
                    Serial.print("Proj2 Z: ");
                    Serial.println(perspective_divided.z);
                    */

                    uint8_t px2 = (uint8_t)((perspective_divided.x + 1) * 83/2);
                    uint8_t py2 = (uint8_t)((perspective_divided.y + 1) * 47/2);
                    
                    /*
                    Serial.print("V2 X: ");
                    Serial.println(px2);

                    Serial.print("V2 Y: ");
                    Serial.println(py2);

                    Serial.print("\n\n");
                    */
                     _main_rasterizer.interpolate_and_draw({px, py, dz0}, {px1, py1, dz1}, {px2, py2, dz2});
                    
                
            }
        }