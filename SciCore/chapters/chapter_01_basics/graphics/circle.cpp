#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

// Color structure for RGB values
struct Color {
    int r, g, b;
};

// Predefined colors
inline constexpr Color BLACK = {0, 0, 0};
inline constexpr Color RED = {255, 0, 0};
inline constexpr Color GREEN = {0, 255, 0};
inline constexpr Color YELLOW = {255, 255, 0};
inline constexpr Color BLUE = {0, 0, 255};
inline constexpr Color MAGENTA = {255, 0, 255};
inline constexpr Color CYAN = {0, 255, 255};
inline constexpr Color WHITE = {255, 255, 255};

// Simple Sixel image class with higher precision
class SixelImage {
private:
    int width, height;
    std::vector<int> pixels; // Store color indices
    
public:
    SixelImage(int w, int h) : width(w), height(h), pixels(w * h, 0) {}
    
    void set_pixel(int x, int y, int color_index) {
        if (x >= 0 && x < width && y >= 0 && y < height) {
            pixels[y * width + x] = color_index;
        }
    }
    
    int get_pixel(int x, int y) const {
        if (x >= 0 && x < width && y >= 0 && y < height) {
            return pixels[y * width + x];
        }
        return 0;
    }
    
    std::string to_sixel(Color fg_color) const {
        std::ostringstream output;
        
        // Start Sixel sequence
        output << "\033Pq";
        
        // Define color 1 as our foreground color
        int r_pct = (fg_color.r * 100) / 255;
        int g_pct = (fg_color.g * 100) / 255;
        int b_pct = (fg_color.b * 100) / 255;
        
        output << "#1;2;" << r_pct << ";" << g_pct << ";" << b_pct;
        
        // Select color 1
        output << "#1";
        
        // Process image in bands of 6 pixels high
        for (int band = 0; band < (height + 5) / 6; ++band) {
            output << "$"; // Carriage return to start of line
            
            for (int x = 0; x < width; ++x) {
                int sixel_value = 0;
                
                // Check 6 vertical pixels
                for (int i = 0; i < 6; ++i) {
                    int y = band * 6 + i;
                    if (y < height && get_pixel(x, y) == 1) {
                        sixel_value |= (1 << i);
                    }
                }
                
                output << char(sixel_value + 63);
            }
            
            // Move to next line
            if (band < (height + 5) / 6 - 1) {
                output << "-"; // Line feed
            }
        }
        
        // End Sixel sequence
        output << "\033\\";
        
        return output.str();
    }
};

// Draw filled circle function with WHITE as default color and higher precision
void draw_circle(int x, int y, float radius, Color c = WHITE) {
    // Calculate canvas size - make sure we have enough space
    // Add extra margin to ensure full circle visibility
    int margin = static_cast<int>(radius) + 20;
    int img_width = x + margin;
    int img_height = y + margin;
    
    SixelImage image(img_width, img_height);
    
    // Draw filled circle with sub-pixel precision using supersampling
    int supersample = 3; // 3x3 supersampling for smoother edges
    
    for (int img_y = 0; img_y < img_height; ++img_y) {
        for (int img_x = 0; img_x < img_width; ++img_x) {
            int hit_count = 0;
            
            // Supersample for anti-aliasing
            for (int sy = 0; sy < supersample; ++sy) {
                for (int sx = 0; sx < supersample; ++sx) {
                    float sample_x = img_x + (sx + 0.5f) / supersample - x;
                    float sample_y = img_y + (sy + 0.5f) / supersample - y;
                    float distance = std::sqrt(sample_x * sample_x + sample_y * sample_y);
                    
                    if (distance <= radius) {
                        hit_count++;
                    }
                }
            }
            
            // If more than half the samples are inside, draw the pixel
            if (hit_count > (supersample * supersample) / 2) {
                image.set_pixel(img_x, img_y, 1);
            }
        }
    }
    
    // Output Sixel data
    std::cout << image.to_sixel(c);
    std::cout.flush();
}

// Draw circle outline only with WHITE as default color and higher precision
void draw_circle_outline(int x, int y, float radius, float thickness = 2.0f, Color c = WHITE) {
    int margin = static_cast<int>(radius + thickness) + 20;
    int img_width = x + margin;
    int img_height = y + margin;
    
    SixelImage image(img_width, img_height);
    
    // Higher precision outline with supersampling
    int supersample = 3;
    
    for (int img_y = 0; img_y < img_height; ++img_y) {
        for (int img_x = 0; img_x < img_width; ++img_x) {
            int hit_count = 0;
            
            for (int sy = 0; sy < supersample; ++sy) {
                for (int sx = 0; sx < supersample; ++sx) {
                    float sample_x = img_x + (sx + 0.5f) / supersample - x;
                    float sample_y = img_y + (sy + 0.5f) / supersample - y;
                    float distance = std::sqrt(sample_x * sample_x + sample_y * sample_y);
                    
                    if (distance >= radius - thickness && distance <= radius + thickness) {
                        hit_count++;
                    }
                }
            }
            
            if (hit_count > (supersample * supersample) / 2) {
                image.set_pixel(img_x, img_y, 1);
            }
        }
    }
    
    std::cout << image.to_sixel(c);
    std::cout.flush();
}

int main() {
    std::cout << "Drawing circles with Sixel graphics (high precision):\n\n";
    
    // Draw a filled white circle (using default color)
    std::cout << "White filled circle:\n";
    draw_circle(100, 100, 40.0f);
    std::cout << "\n\n";
    
    std::cout << "Red filled circle:\n";
    draw_circle(80, 80, 35.0f, RED);
    std::cout << "\n\n";
    
    std::cout << "Blue circle outline:\n";
    draw_circle_outline(90, 90, 50.0f, 4.0f, BLUE);
    std::cout << "\n\n";
    
    std::cout << "Cyan filled circle:\n";
    draw_circle(100, 100, 45.0f, CYAN);
    std::cout << "\n\n";
    
    std::cout << "Yellow circle at different position:\n";
    draw_circle(120, 80, 30.0f, YELLOW);
    std::cout << "\n\n";
    
    std::cout << "Green precise outline:\n";
    draw_circle_outline(100, 100, 60.0f, 3.0f, GREEN);
    std::cout << "\n\n";
    
    return 0;
}
