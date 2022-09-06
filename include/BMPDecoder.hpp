#ifndef BMP_DEC
#define BMP_DEC

#include <cinttypes>
#include <SPIFFS.h>
#include <Driver.hpp>
#include <cmath>

struct BMP
    {
        uint8_t** bmp_data;
        uint8_t width;
        uint8_t height;

        public:
            void draw_bmp()
            {
                for(unsigned int row = 0; row < height; row++)
                {
                    for(unsigned int column = 0; column < width; column++)
                    {
                        //Serial.print(bmp_data[row][column], HEX);
                        if(bmp_data[row][column] == 1)
                            DriverLCD::draw_pixel(column, row);
                    }
                }
            }

            void free()
            {
                for(unsigned int rs = 0; rs < height; rs++)
                    delete[] bmp_data[rs];
                delete[] bmp_data;
            }
    };

class BMPDecoder
{

    public:
        BMPDecoder();
        static BMP load(const char* path)
        {
            if(!SPIFFS.begin(true)){
                Serial.println("An Error has occurred while mounting SPIFFS");
            }

            File img_bmp = SPIFFS.open(path);
            uint8_t width = 0;
            uint8_t height = 0;

            img_bmp.seek(18);   // offsets 18 and 22 of a BMP file contain both a 4 byte uint, these are the bmp's width and height respectively.
            img_bmp.read(&width, 1);

            img_bmp.seek(22);
            img_bmp.read(&height, 1);// Because the maximum width and height are both less than 255 and thus can be encoded in a single byte, only the first byte of the 4 has to be read.

            img_bmp.seek(54); // The bmp pixel array starts at offset 54.

            uint8_t** img = new uint8_t*[height]; 
            for(unsigned int i = 0; i < height; i++)
                img[i] = new uint8_t[width];

            uint8_t byte_i;
            int row = 0;
            for(unsigned int i = 0; i < (uint16_t) width*height; i++)
            {
                img_bmp.read(&byte_i, 1); // Read a byte and skip 2, so we do jumps in threes, reading the first byte of every pixel, which is the one we care for.
                img_bmp.seek(2, fs::SeekCur);

                if(byte_i == 0x00)
                    img[row][i%width] = 0x01;
                else
                    img[row][i%width] = 0x00;
                if(i%84 == 0 && i != 0)
                    row++;
                    //_lcd_main_driver.draw_pixel((((i/3))%84), ((i/3)/84));
            }

            img_bmp.close();

            return {.bmp_data = img, .width = width, .height = height};
        }

    static BMP rotate(BMP* bmp, float degrees)
    {
        // First create a new buffer where the rotated image  projection will be.
        // Then, for every pixel, do the transformation.
        uint8_t** nb = new uint8_t*[bmp->height];
        float rad = degrees/360 * TWO_PI;
        for(unsigned int i = 0; i < bmp->height; i++)
            nb[i] = new uint8_t[bmp->width];

        for(unsigned int r=0; r < bmp->height; r++)
        {
            for(unsigned int c = 0; c < bmp->width; c++)
                nb[r][c] = 0;
        }

        for(int y = 0; y < bmp->height; y++)
        {
            for(int x = 1; x < bmp->width; x++)
            {
                float k = x-42;
                int x_p;

                x_p = (int)floor(((k)*cos(rad))) + 42;
                nb[y][x_p] = bmp->bmp_data[y][x];
            }
        }
        
        return {.bmp_data = nb, .width = bmp->width, .height = bmp->height};
    }

};



#endif