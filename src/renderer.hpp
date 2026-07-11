#pragma once

#include <string>
#include <vector>

// multiple fractal formulas
enum class FractalType
{
    mandelbrot,
    mandelbrot_p3,
    mandelbar,
    mandelbrot_cos,
    mandelbrot_sin,
    julia_classic,
    julia_flower,
    julia_cone,
    julia_spiral, 
    julia_snake, 
    julia_silver_ratio, 
};

// choose from multiple types
enum class PaletteType
{
    sunset,
    ocean,
    fire,
    neon,
    blue_green,
    orange_valley,
    rainbow,
    fire_ice,
    elec_magenta,
    emerald,
    elec_blue,
    type1,
};

// palette phases struct
struct Palette
{
    double r_phase;
    double g_phase;
    double b_phase;
};

// palette switching
Palette get_palette(PaletteType type);

// camera for the set(centers mandelbrot set)
struct FractalView
{
    double center_real; 
    double center_img;
    double real_span;
};

class Mandelbrot
{
    public:
        std::vector<int> image;

        // width and height for the fractal set
        int width;
        int height;

        // zoom factor
        double zoom_factor{0.0};

        // FractalView for julia set centering(mandelbrot is shifted to left)
        FractalView view;

        // complex plane real values
        double real_min = view.center_real - view.real_span/2;
        double real_max = view.center_real + view.real_span/2;

        double aspect_ratio = static_cast<double>(height) / static_cast<double>(width);
        double img_span = view.real_span * aspect_ratio;

        // complex plane imaginary values
        double img_min = view.center_img - img_span / 2;
        double img_max = view.center_img + img_span / 2;

        // max amount of iteration
        const int max_iteration;

        // enum class for multiple formulas
        FractalType curr_fractal_type;

        // custom palette
        Palette palette;

        Mandelbrot(int width, int height, int max_iteration, double zoom_factor = 1.0);
        void render_fractal();
        void render_gray_scale(const std::string& file_name);
        void render_color(const std::string& file_name);
};
        /*
         * Todo *
         * Add function to create multiple formulas ✅
         * add time bench mark using chrono ✅
         * fix the aspect ratio problem(the stretch) ✅ 
         * add zoom logic ✅
         * add a struct Palette✅
         * add a enum class PaletteType✅
         * add input validation✅
         */
