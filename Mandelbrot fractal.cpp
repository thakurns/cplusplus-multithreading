#include <iostream>
#include <thread>
#include <vector>
#include <complex>

// Define the resolution of the image
const int WIDTH = 800;
const int HEIGHT = 800;

// Define the region of the complex plane to render
const double MIN_REAL = -2.0;
const double MAX_REAL = 1.0;
const double MIN_IMAG = -1.5;
const double MAX_IMAG = 1.5;

// Maximum number of iterations
const int MAX_ITERATIONS = 1000;

// Function to calculate the color of a pixel in the Mandelbrot set
int mandelbrot(int x, int y) {
    std::complex<double> z(0, 0);
    std::complex<double> c(
        x * (MAX_REAL - MIN_REAL) / (WIDTH - 1) + MIN_REAL,
        y * (MAX_IMAG - MIN_IMAG) / (HEIGHT - 1) + MIN_IMAG
    );

    int iterations = 0;
    while (abs(z) < 2.0 && iterations < MAX_ITERATIONS) {
        z = z * z + c;
        iterations++;
    }

    return iterations;
}

// Function to render a portion of the Mandelbrot set using multiple threads
void renderMandelbrot(int startY, int endY, std::vector<std::vector<int>>& image) {
    for (int y = startY; y < endY; y++) {
        for (int x = 0; x < WIDTH; x++) {
            int color = mandelbrot(x, y);
            image[y][x] = color;
        }
    }
}

int main111() {
    std::vector<std::vector<int>> image(HEIGHT, std::vector<int>(WIDTH));

    // Number of threads to use
    const int numThreads = std::thread::hardware_concurrency();

    // printing no. of to use.
    std::cout << numThreads << std::endl;

    // Divide the image into equal portions for each thread
    std::vector<std::thread> threads;
    for (int i = 0; i < numThreads; i++) {
        int startY = i * (HEIGHT / numThreads);
        int endY = (i + 1) * (HEIGHT / numThreads);
        threads.emplace_back(renderMandelbrot, startY, endY, std::ref(image));
    }

    // Wait for all threads to finish
    for (std::thread& thread : threads) {
        thread.join();
    }

    // Output the image (you can save it to a file or display it as needed)
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if (image[y][x] == MAX_ITERATIONS) {
                std::cout << " ";  // Inside the Mandelbrot set
            }
            else {
                std::cout << "*";  // Outside the Mandelbrot set
            }
        }
        std::cout << std::endl;
    }

    return 0;
}
