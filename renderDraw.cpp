// On linux compile with:
// g++ -std=c++17 main.cpp -o prog -lSDL2 -ldl
// On windows compile with (if using mingw)
// g++ main.cpp -o prog.exe -lmingw32 -lSDL2main -lSDL2
// On Mac compile with:
// clang++ main.cpp -I/Library/Frameworks/SDL2.framework/Headers -F/Library/Frameworks -framework SDL2

// C++ Standard Libraries
#include <iostream>
#include <math.h>
// Third Party
#include <C:/Users/User/Desktop/DSA_Project/SDL2-2.0.18/i686-w64-mingw32/include/SDL2/SDL.h> // For Mac, use <SDL.h>

int main(int argc, char* argv[]){
    // Create a window data type
    // This pointer will point to the 
    // window that is allocated from SDL_CreateWindow
    SDL_Window* window=nullptr;

    // Initialize the video subsystem.
    // iF it returns less than 1, then an
    // error code will be received.
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        std::cout << "SDL could not be initialized: " <<
                  SDL_GetError();
    }else{
        std::cout << "SDL video system is ready to go\n";
    }
    // Request a window to be created for our platform
    // The parameters are for the title, x and y position,
    // and the width and height of the window.
    window = SDL_CreateWindow("C++ SDL2 Window",20, 20, 1920,1080,SDL_WINDOW_SHOWN);

    SDL_Renderer* renderer = nullptr;
    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    
    // Create a rectangle
    SDL_Rect rectangle;
    /*;*/

    double x, y, xC = 100;
    double theta, pi=3.14;
    int radiusC = 150;
    double inc = 0.1;
    int i;
    // Infinite loop for our application
    bool gameIsRunning = true;
    // Main application loop

    SDL_Event event;
        
        // (2) Handle Updates
        
        // (3) Clear and Draw the Screen
        // Gives us a clear "canvas"
        SDL_SetRenderDrawColor(renderer,0,0,0,SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        // Do our drawing
        for(i = 0, theta = 0; theta<=2*pi && i < 100; i++, theta+=inc)
        {
            x = xC + (radiusC*cos(theta))+ 960;
            y = radiusC*sin(theta) + 540;
            
            if(theta >= 2*pi-inc)
            {
                theta = 0.1;
                radiusC+=20;
            }

            rectangle.x = x;
            rectangle.y = y;
            rectangle.w = 10;
            rectangle.h = 10;
            SDL_SetRenderDrawColor(renderer,255,255,255,SDL_ALPHA_OPAQUE);
            SDL_RenderDrawRect(renderer, &rectangle);
        }
        
        //SDL_RenderDrawLine(renderer,5,5,100,120);

        //SDL_RenderDrawRect(renderer,&rectangle);


        // Finally show what we've drawn
        SDL_RenderPresent(renderer);
        bool end = false;

        while(!end){
            while(SDL_PollEvent(&event)){
                // Handle each specific event
                if(event.type == SDL_QUIT){
                    gameIsRunning= false;
                }
            }
        }

    // We destroy our window. We are passing in the pointer
    // that points to the memory allocated by the 
    // 'SDL_CreateWindow' function. Remember, this is
    // a 'C-style' API, we don't have destructors.
    SDL_DestroyWindow(window);
    
    // our program.
    SDL_Quit();
    return 0;
}