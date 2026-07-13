# Fractal Renderer

A C++ fractal renderer created to explore Mandelbrot, Julia and experimental fractals.

## What is this?

This is a CPU based Fractal Renderer that outputs static images of fractals based on the formula

\displaystyle f_{c}(z)=z^{2}+c

## Image output

Images are exported in the PPM(Portable Pixmap) format. PPM is a simple image format that can be written directly using C++ standard library without external dependencies.

## Features

### Fractals types

- ***Mandebrot types***
    - *Classic*
    - *Raised to power 3*
    - *Tricorn or Mandelbar*
    - *Cosine function*
    - *Sine function*

- ***Julia set types***
    - *Classic*
    - *Flower*
    - *Cone*
    - *Sprial*
    - *Snake*
    - *Silver ratio*

### Color Palette

 ***11 Unique Cosine based Palettes***

 - *Sunset*
 - *Ocean*
 - *Fire*
 - *Neon*
 - *Blue & Green*
 - *Orange Valley*
 - *Rainbow*
 - *Fire & Ice*
 - *Electric Magenta*
 - *Emerald*
 - *Electric Blue*

## Compile and Run
```bash
g++ main.cpp frames.cpp renderer.cpp -o run && ./run
```
