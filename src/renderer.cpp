#include <iostream> 
#include <fstream>
#include <complex>
#include <cmath>
#include <vector>
#include <string>
#include "renderer.hpp"

// global constexpr
constexpr double PI  = 3.141592653589793;
constexpr double TAU = 2.0 * PI;


// palette switching
Palette get_palette(PaletteType type)
{
    switch(type)
    {
        case PaletteType::sunset:        return {0.99, 0.20, 0.75};
        case PaletteType::ocean:         return {0.10, 0.40, 0.70};
        case PaletteType::fire:          return {0.00, 0.10, 0.20};
        case PaletteType::neon:          return {0.80, 0.50, 0.30};
        case PaletteType::blue_green:    return {0.04, 0.99, 0.25};
        case PaletteType::orange_valley: return {1.00, 0.20, 0.30};
        case PaletteType::rainbow:       return {0.00, 0.33, 0.67};
        case PaletteType::fire_ice:      return {0.00, 0.05, 0.05};
        case PaletteType::elec_magenta:  return {0.10, 0.50, 0.10};
        case PaletteType::emerald:       return {0.50, 0.20, 0.25};
        case PaletteType::elec_blue:     return {0.50, 0.10, 0.00};
        case PaletteType::type1:         return {0.66, 0.01, 0.66};
    }

    // fallback
    return {0.1, 0.4, 0.7};
}

// explicit constructor
Mandelbrot::Mandelbrot(int width, int height, int max_iteration, double zoom_factor)
    : width{width}, height{height}, max_iteration{max_iteration}, zoom_factor{zoom_factor} 
{
    // output image size
    image.resize(width * height);

    // base fractal set view values
    /* seahorse valley MB- r: -0.75, i: 0.1 */
    view.center_real = -0.5; // x axis(horizontal)
    view.center_img = 0.0; // y axis(vertical)
    view.real_span = 3.0 / zoom_factor;

    // set fractal type
    curr_fractal_type = FractalType::julia_classic;
    
    // set fractal color palette
    palette = get_palette(PaletteType::type1);
}

// render method
void Mandelbrot::render_fractal()
{
    // complex plane real values
    double real_min = view.center_real - view.real_span/2;
    double real_max = view.center_real + view.real_span/2;

    double aspect_ratio = static_cast<double>(height) / static_cast<double>(width);
    double img_span = view.real_span * aspect_ratio;

    // complex plane imaginary values
    double img_min = view.center_img - img_span / 2;
    double img_max = view.center_img + img_span / 2;

    for(int y = 0; y < height; ++y)
    {
        for(int x = 0; x < width; ++x)
        {
            // map each pixel on the complex plane
            std::complex<double> c;
            std::complex<double> z;

            // compute real and img values
            double compute_real = (real_min + (real_max - real_min) * static_cast<double>(x) / width);
            double compute_img = (img_max - (img_max - img_min) * static_cast<double>(y) / height);

            std::complex<double> pixel(compute_real, compute_img);

            // switch fractal formula
            switch(curr_fractal_type)
            {
                case FractalType::mandelbrot: 
                    c = pixel;
                    z = 0;
                break;

                case FractalType::mandelbrot_p3:
                    c = pixel;
                    z = 0;
                break;

                case FractalType::mandelbar:
                    c = pixel;
                    z = 0;
                break;

                case FractalType::mandelbrot_cos:
                    c = pixel;
                    z = 0;
                break;

                case FractalType::mandelbrot_sin:
                    c = pixel;
                    z = 0;
                break;

                case FractalType::julia_classic:
                    z = pixel;
                    c = std::complex<double>(-0.8, 0.156);
                break;

                case FractalType::julia_flower:
                    z = pixel;
                    c = std::complex<double>(0.35, 0.35);
                break;

                case FractalType::julia_cone:
                    z = pixel;
                    c = std::complex<double>(-0.4, 0.6);
                break;
                
                case FractalType::julia_spiral:
                    z = pixel;
                    c = std::complex<double>(0.285, 0.01);
                break;

                case FractalType::julia_snake:
                    z = pixel;
                    c = std::complex<double>(-0.835, 0.2321);
                break;
                    
                case FractalType::julia_silver_ratio:
                    z = pixel;
                    c = std::complex<double>(-0.75, 0.11);
                break;
            }

            int iterator = 0;

            // main formula loop
            while (std::abs(z) <= 2 && iterator < max_iteration)
            {
                if(curr_fractal_type == FractalType::mandelbrot_p3) 
                {
                    z = (z * z * z) + c;
                }
                else if(curr_fractal_type == FractalType::mandelbar)
                {
                    z = std::conj(z * z) + c;
                }
                else if(curr_fractal_type == FractalType::mandelbrot_cos)
                {
                    z = std::cos(z * z) + c;
                }
                else if(curr_fractal_type == FractalType::mandelbrot_sin)
                {
                    z = std::sin(z * z) + c;
                }
                else
                {
                    z = (z * z) + c;
                }
                iterator++;
            }

            image[y * width + x] = iterator;
        }
    }
}

// save in pgm format
void Mandelbrot::render_gray_scale(const std::string& file_name)
{
    std::ofstream ofs(file_name, std::ios::binary);

    ofs << "P5\n" << width << ' ' << height << "\n255\n";

    for(int i = 0; i < width * height; ++i)
    {
        int iteration_num = image[i];
        unsigned char color = 
            static_cast<unsigned char>(255 * iteration_num / max_iteration);
        ofs << color;
    }

    ofs.close();
}

// save in ppm format
void Mandelbrot::render_color(const std::string& file_name)
{
    std::ofstream ofs(file_name, std::ios::binary);

    ofs << "P6\n" << width << ' ' << height << "\n255\n";

    // convert division to multiplication
    double inv_max_iteration = 1.0 / max_iteration;

    for(int i = 0; i < width * height; ++i)
    {
        int iteration_num = image[i];
        unsigned char r, g, b;
        if(iteration_num == max_iteration)
        {
            // main set color black
            r = 1;
            g = 1;
            b = 1;
        }
        else
        {
            double t = iteration_num * inv_max_iteration;

            // color palette smoothening using std::cos()
            r = (int)(255 * (0.5 + 0.5 * std::cos(TAU * (t + palette.r_phase))));
            g = (int)(255 * (0.5 + 0.5 * std::cos(TAU * (t + palette.g_phase))));
            b = (int)(255 * (0.5 + 0.5 * std::cos(TAU * (t + palette.b_phase))));
        }

        ofs.write(reinterpret_cast<char*>(&r), 1);
        ofs.write(reinterpret_cast<char*>(&g), 1);
        ofs.write(reinterpret_cast<char*>(&b), 1);
    }

    ofs.close();
}
