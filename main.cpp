#include <iostream>
#include <SDL2/SDL.h>

using namespace std;

struct Point {
    float x;
    float y;
};

const int WINDOW_WIDTH = 1000;
const int WINDOW_HEIGHT = 1000;
const int POINTS = 32768;
//const int POINTS = 262144;

Point points[POINTS];
int current_point = 0;

int main()
{
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    // initialize sdl
    SDL_Init(SDL_INIT_EVERYTHING);

    window = SDL_CreateWindow(
        NULL,
        SDL_WINDOWPOS_CENTERED_DISPLAY(1),
        SDL_WINDOWPOS_CENTERED_DISPLAY(1),
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_BORDERLESS
    );

    renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

    // vertici del triangolo
    Point p1 {
        .x = WINDOW_WIDTH / 2,
        .y = 10
    };
    Point p2 {
        .x = 10,
        .y = WINDOW_HEIGHT - 10
    };
    Point p3 {
        .x = WINDOW_WIDTH - 10,
        .y = WINDOW_HEIGHT - 10
    };

    // punto centrale iniziale
    Point p {
        .x = WINDOW_WIDTH / 2,
        .y = WINDOW_HEIGHT / 2
    };

    points[current_point] = p;

    while (true) {

        // process input
        SDL_PumpEvents();
        const Uint8 *keyboardState = SDL_GetKeyboardState(NULL);

        if (keyboardState[SDL_SCANCODE_ESCAPE]) {
            break;
        }

        // render everything
        SDL_RenderDrawPoint(renderer, p1.x, p1.y);
        SDL_RenderDrawPoint(renderer, p2.x, p2.y);
        SDL_RenderDrawPoint(renderer, p3.x, p3.y);

        for (Point p: points)
            SDL_RenderDrawPoint(renderer, p.x, p.y);

        SDL_RenderPresent(renderer);

        current_point++;

        if (current_point % 5000 == 0)
            cout << "rendered " << current_point << " dots of " << POINTS << endl;
        else if (current_point == (POINTS - 1)) {
            cout << "rendered " << current_point << " dots. DONE." << endl;
            break;
        }

        // new point generation
        int idx_vertice = rand() % 3;

        Point new_point;
        Point last_point = points[current_point-1];
        if (idx_vertice == 0) {
            new_point.x = (p1.x + last_point.x) / 2;
            new_point.y = (p1.y + last_point.y) / 2;
        }
        else if (idx_vertice == 1) {
            new_point.x = (p2.x + last_point.x) / 2;
            new_point.y = (p2.y + last_point.y) / 2;
        }
        else {
            new_point.x = (p3.x + last_point.x) / 2;
            new_point.y = (p3.y + last_point.y) / 2;
        }
        points[current_point] = new_point;
    }

    cout << "Press enter to exit program." << endl;
    cin.ignore();

    //    destroy stuff
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
