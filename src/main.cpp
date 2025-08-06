#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include <vector>

struct rect {
    int x, y, w, h;
    int r, g, b;

    rect(int x, int y, int w, int h, int r, int g, int b) : x(x), y(y), w(w), h(h), r(r), g(g), b(b) {}
    rect(int x, int y, int w, int h) : x(x), y(y), w(w), h(h), r(0), g(0), b(0) {}
    rect() : x(0), y(0), w(0), h(0), r(0), g(0), b(0) {}

    bool contains(int px, int py) const {
        return px >= x && px < x + w && py >= y && py < y + h;
    }
    bool contains(const rect& r) const {
        return contains(r.x, r.y) && contains(r.x + r.w - 1, r.y + r.h - 1);
    }
    bool intersects(const rect& r) const {
        return !(x + w <= r.x || x >= r.x + r.w || y + h <= r.y || y >= r.y + r.h);
    }
    rect intersection(const rect& r) const {
        if (!intersects(r)) return rect();
        int nx = std::max(x, r.x);
        int ny = std::max(y, r.y);
        int nw = std::min(x + w, r.x + r.w) - nx;
        int nh = std::min(y + h, r.y + r.h) - ny;
        return rect(nx, ny, nw, nh);
    }
    rect union_rect(const rect& r) const {
        int nx = std::min(x, r.x);
        int ny = std::min(y, r.y);
        int nw = std::max(x + w, r.x + r.w) - nx;
        int nh = std::max(y + h, r.y + r.h) - ny;
        return rect(nx, ny, nw, nh);
    }
    void move(int dx, int dy) {
        x += dx;
        y += dy;
    }
    void resize(int dw, int dh) {
        w += dw;
        h += dh;
    }
    void print() const {
        std::cout << "Rect(" << x << ", " << y << ", " << w << ", " << h << ")\n";
    }
};


int main(int argc, char* argv[]) {
    if(SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("SDL_Init() error: %s", SDL_GetError());
    }

    SDL_Window* window = SDL_CreateWindow("SDL Window", 
                                        SDL_WINDOWPOS_UNDEFINED, 
                                        SDL_WINDOWPOS_UNDEFINED, 
                                        600, 800, 
                                        SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN_DESKTOP);

    if (!window) {
        SDL_Log("SDL_CreateWindow() error: %s", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        SDL_Log("SDL_CreateRenderer() error: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    SDL_Texture *tex = IMG_LoadTexture(renderer, "taco.png");
    if(!tex) {
        SDL_Log("IMG_Load() error: %s", IMG_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }


    bool running = true;
    Uint64 now = SDL_GetPerformanceCounter();
    Uint64 last = 0;
    Uint64 totalFrames = 0;
    double totalTime = 0.0;
    double deltaTime = 0.0;


    std::vector<rect> rectangles;

    for(int i = 0; i < 1000; i++) {
        rectangles.push_back(rect(rand() % 1080, rand() % 1920, rand() % 100 + 1, rand() % 100 + 1));
    }

    while(running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }


        last = now;
        now = SDL_GetPerformanceCounter();

        Uint64 freq = SDL_GetPerformanceFrequency();
        deltaTime = (now - last) / freq;


        // Clear screen before rendering!!
        SDL_SetRenderDrawColor(renderer, 25, 25, 25, 255);
        SDL_RenderClear(renderer);


        for(int i = 0; i < 1000; i++) {
            rectangles[i].move(rand() % 5 - 2, rand() % 5 - 2);
            rectangles[i].resize(rand() % 3 - 1, rand() % 3 - 1);
            rectangles[i].r = rand() % 256;
            rectangles[i].g = rand() % 256;
            rectangles[i].b = rand() % 256;
            if (rectangles[i].x < 0) rectangles[i].x = 0;
            if (rectangles[i].y < 0) rectangles[i].y = 0;
            // if (rectangles[i].x + rectangles[i].w > 640) rectangles[i].x = 640 - rectangles[i].w;
            // if (rectangles[i].y + rectangles[i].h > 480) rectangles[i].y = 480 - rectangles[i].h;
            // printf("Rect %d: ", i);
            // rectangles[i].print();
        }

        for(int i = 0; i < 1000; i++) {
            SDL_SetRenderDrawColor(renderer, rectangles[i].r, rectangles[i].g, rectangles[i].b, 255);
            SDL_Rect sdlRect = { rectangles[i].x, rectangles[i].y, rectangles[i].w, rectangles[i].h };
            // SDL_RenderFillRect(renderer, &sdlRect);
            SDL_SetTextureColorMod(tex, rectangles[i].r, rectangles[i].g, rectangles[i].b);
            SDL_SetTextureAlphaMod(tex, 255);
            SDL_RenderCopy(renderer, tex, nullptr, &sdlRect);
        }

        // Present rendered content!!
        SDL_RenderPresent(renderer);

        totalFrames++;
        totalTime += deltaTime;


        double fps = 1.0 / deltaTime;
        double avg_fps = (double)freq * totalFrames / totalTime;

        std::string currfps = "Current: " + std::to_string(fps);
        std::string avgfps  = "Average: " + std::to_string(avg_fps);
        printf("%s | %s\n", currfps.c_str(), avgfps.c_str());
    }

    SDL_DestroyTexture(tex);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}