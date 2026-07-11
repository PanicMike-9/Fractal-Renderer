#include <iostream>
#include <chrono>
#include <cmath>

#include "frames.hpp"

// multiple images with different zoom values
void generate_frames()
{
    int width, height, max_iteration, total_frames;
    double base_zoom;
    std::cout << "ENTER WIDTH, HEIGHT, MAX_ITERATION, BASE_ZOOM && TOTAL_FRAMES IN ORDER: ";

    // input validation
    while(true)
    {
        if(std::cin >> width >> height >> max_iteration >> base_zoom >> total_frames &&
                width > 0 && height > 0 && max_iteration > 0 && base_zoom > 0 && total_frames > 0 &&  
                width <= 5120 && height <= 5120 && max_iteration <= 5000 && base_zoom <= 100 && total_frames <= 150)
        {
            break;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout  << "** INVALID INPUT! **\n"  
                   << "** VALUES SHOULD BE **\n"
                   << "*  WIDTH/HEIGHT:   1-5120 \n"
                   << "*  MAX_ITERATION:  1-1500 \n"
                   << "*  BASE_ZOOM:      1x-100x  \n"
                   << "*  TOTAL_FRAMES:   1-150  \n";
        std::cout << "\nENTER WIDTH, HEIGHT, MAX_ITERATION, BASE_ZOOM && TOTAL_FRAMES IN ORDER: ";
    }

    std::cout << "GENERATING FRAMES...\n";

    auto start_anim = std::chrono::steady_clock::now();

    for(int frame = 0; frame < total_frames; ++frame)
    {
        double zoom = base_zoom * exp(-0.05 * frame); // zoom by 5%

        MB fractal(width, height, max_iteration, zoom);

        fractal.render_fractal();

        // filename with index
        char filename[100];
        sprintf(filename, "frm_%04d.ppm", frame);

        fractal.render_color(filename);
    } 

    auto end_anim = std::chrono::steady_clock::now();

    auto duration_anim = std::chrono::duration_cast<std::chrono::seconds>(end_anim - start_anim);

    std::cout << "TOTAL ANIMATION RENDER DURATION: " << duration_anim.count() << "s \n";

    std::cout << "FRAME GENERATION COMPLETED!\n";
}

