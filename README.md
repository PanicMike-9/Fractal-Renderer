# Fractal Renderer

A C++ fractal renderer created to explore Mandelbrot, Julia and experimental fractals.

## Overview

This is a CPU-based Fractal Renderer written in C++ that generates static images of fractals using the classic escape-time algorithm.

$${\displaystyle f_{c}(z)=z^{2}+c}$$

The renderer is centered around the classic Mandelbrot formula, while also supporting several modified and experimental fractal formulas.

This project was build to explore mathematics behind fractals while learning CPU-based rendering, image generation, file I/O, `std::complex`, and modern C++.

## Image output

Images are exported in the Portable Pixmap(PPM) format. PPM is a simple image format that can be written directly using C++ standard library without external image-procesing libraries.

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
## Technical Specification

- **Language**:      C++ 17
- **Rendering**:     CPU-based single threaded
- **Output Format**: Portable Pixmap(PPM)
- **Math Library**:  `std::complex`
- **Dependecies**:   None (C++ standard template library only)
