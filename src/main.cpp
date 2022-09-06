#include <Arduino.h>
#include <TriangleRasterizer.hpp>
#include <BMPDecoder.hpp>
#include <World.hpp>
#include <utility>
#include <array>

DriverLCD _lcd_main_driver = DriverLCD(RESET_LCD, CHIP_ENABLE, DATA_COMMAND, DIN_I2C, CLK_SIGNAL);
TrigRasterizer _main_rasterizer = TrigRasterizer();
BMP trollface_img = BMPDecoder::load("/trollface");
World world;


void setup() {

  Serial.begin(9600);
  _lcd_main_driver.init(ADDRMODE_HORIZONTAL);
  digitalWrite(CHIP_ENABLE, LOW);
  digitalWrite(CHIP_ENABLE, HIGH);
  _lcd_main_driver.clr_scr();

/*
  _main_rasterizer.interpolate_and_draw({15, 47}, {25, 37}, {5, 26});
  _main_rasterizer.interpolate_and_draw({35, 17}, {5, 23}, {16, 30});
  _main_rasterizer.interpolate_and_draw({50, 30}, {65, 10}, {41, 16});
  _main_rasterizer.interpolate_and_draw({1, 17}, {12, 11}, {3, 2});
  _main_rasterizer.interpolate_and_draw({18, 11}, {33, 16}, {24, 5});
  _main_rasterizer.interpolate_and_draw({68, 30}, {75, 38}, {56, 46});
  _main_rasterizer.interpolate_and_draw({36, 35}, {45, 41}, {41, 47});
  
*/

  //_lcd_main_driver.draw_pixel(40, 45);
  
  /*
  _lcd_main_driver.draw_pixel(0, 0);
  _lcd_main_driver.draw_pixel(0, 1);
  _lcd_main_driver.draw_pixel(0, 2);
  _lcd_main_driver.draw_pixel(0, 3);
  _lcd_main_driver.draw_pixel(0, 4);
  _lcd_main_driver.draw_pixel(1, 4);
  _lcd_main_driver.draw_pixel(2, 4);
  _lcd_main_driver.draw_pixel(3, 4);
  _lcd_main_driver.draw_pixel(4, 4);
  _lcd_main_driver.draw_pixel(4, 3);
  _lcd_main_driver.draw_pixel(4, 2);
  _lcd_main_driver.draw_pixel(4, 1);
  _lcd_main_driver.draw_pixel(4, 0);
  _lcd_main_driver.draw_pixel(3, 0);
  _lcd_main_driver.draw_pixel(2, 0);
  _lcd_main_driver.draw_pixel(1, 0);
  */

 
  world.add_drawable(Drawable(glm::vec3(0.0, 0.f, 0.f),
   {

    Triangle(
      std::make_pair(glm::vec3(-0.5f, 0.f, -0.5f), std::array<float, 0>()),
      std::make_pair(glm::vec3(-0.5f, 1.f, -0.5f), std::array<float, 0>()),
      std::make_pair(glm::vec3(-0.5f, 0.f, 0.5f), std::array<float, 0>())
    ),

    Triangle(
      std::make_pair(glm::vec3(-0.5f, 0.f, 0.5f), std::array<float, 0>()),
      std::make_pair(glm::vec3(-0.5f, 1.f, 0.5f), std::array<float, 0>()),
      std::make_pair(glm::vec3(-0.5f, 1.f, -0.5), std::array<float, 0>())
    ),

    Triangle(
      std::make_pair(glm::vec3(-0.5f, 0.f, 0.5f), std::array<float, 0>()),
      std::make_pair(glm::vec3(-0.5f, 1.f, 0.5f), std::array<float, 0>()),
      std::make_pair(glm::vec3(0.5f, 0.f, 0.5f), std::array<float, 0>())
    ),

    Triangle(
      std::make_pair(glm::vec3(0.5f, 0.f, 0.5f), std::array<float, 0>()),
      std::make_pair(glm::vec3(0.5f, 1.f, 0.5f), std::array<float, 0>()),
      std::make_pair(glm::vec3(-0.5f, 1.f, 0.5f), std::array<float, 0>())
    ),

    Triangle(
      std::make_pair(glm::vec3(0.5f, 0.f, 0.5f), std::array<float, 0>()),
      std::make_pair(glm::vec3(0.5f, 1.f, 0.5f), std::array<float, 0>()),
      std::make_pair(glm::vec3(0.5f, 0.f, -0.5f), std::array<float, 0>())
    ),

    Triangle(
      std::make_pair(glm::vec3(0.5f, 0.f, -0.5f), std::array<float, 0>()),
      std::make_pair(glm::vec3(0.5f, 1.f, -0.5f), std::array<float, 0>()),
      std::make_pair(glm::vec3(0.5f, 1.f, 0.5f), std::array<float, 0>())
    ),

    Triangle(
      std::make_pair(glm::vec3(-0.5f, 0.f, -0.5f), std::array<float, 0>()),
      std::make_pair(glm::vec3(-0.5f, 1.f, -0.5f), std::array<float, 0>()),
      std::make_pair(glm::vec3(0.5f, 0.f, -0.5f), std::array<float, 0>())
    ),

    Triangle(
      std::make_pair(glm::vec3(0.5f, 0.f, -0.5f), std::array<float, 0>()),
      std::make_pair(glm::vec3(0.5f, 1.f, -0.5f), std::array<float, 0>()),
      std::make_pair(glm::vec3(-0.5f, 1.f, -0.5f), std::array<float, 0>())
    )
    }
    ));
  //Serial.println("Final");
}

void loop() {

 _lcd_main_driver.clr_scr();
  world.world_update();
 _lcd_main_driver.display_mem();
 _lcd_main_driver.clr_z();
 delay(50);

}