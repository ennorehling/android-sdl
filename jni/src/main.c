#include <SDL.h>
#include <android/log.h>

#define APPNAME "SDL"

int SDL_main(int argc, char **argv)
{
    SDL_Window *win = 0;
    SDL_Renderer *ren = 0;
    SDL_Surface *bmp = 0;
    SDL_Texture* tex = 0;
    SDL_bool done = SDL_FALSE;

    __android_log_print(ANDROID_LOG_VERBOSE, APPNAME, "SDL_main: %s\n", SDL_GetError());

    if (SDL_Init(SDL_INIT_EVERYTHING) == -1){
        __android_log_print(ANDROID_LOG_VERBOSE, APPNAME, "SDL_Init: %s\n", SDL_GetError());
        return 1;
    }
    win = SDL_CreateWindow("Hello World!", 0, 0, 640, 480, SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN);
    if (win == 0){
        __android_log_print(ANDROID_LOG_ERROR, APPNAME, "SDL_CreateWindow: %s\n", SDL_GetError());
        return 1;
    }
    ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (ren == 0){
        __android_log_print(ANDROID_LOG_ERROR, APPNAME, "SDL_CreateRenderer: %s\n", SDL_GetError());
        return 1;
    }

    bmp = SDL_LoadBMP("image.bmp");
    if (!bmp) {
        __android_log_print(ANDROID_LOG_ERROR, APPNAME, "SDL_LoadBMP: %s\n", SDL_GetError());
        return 1;
    }
    tex = SDL_CreateTextureFromSurface(ren, bmp);
    SDL_FreeSurface(bmp);
    if (!tex) {
        __android_log_print(ANDROID_LOG_ERROR, APPNAME, "SDL_CreateTexture: %s\n", SDL_GetError());
        return 1;
    }

    __android_log_print(ANDROID_LOG_INFO, APPNAME, "SDL_Success: %s\n", SDL_GetError());
    while (!done) {
        SDL_Event event;
        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT || event.type == SDL_KEYDOWN || event.type == SDL_FINGERDOWN) {
                done = SDL_TRUE;
            }
        }

        SDL_SetRenderDrawColor(ren, 0xA0, 0xA0, 0xA0, 0xFF);
        SDL_RenderCopy(ren, tex, NULL, NULL);
        SDL_RenderPresent(ren);
    }

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}
