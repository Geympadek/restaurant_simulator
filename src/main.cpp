#include "application.h"

using namespace engix;

void initLibraries();
void freeLibraries();

int main(int argc, char** argv)
{
    initLibraries();

    Application* game = nullptr;
    try
    {
        SDL_ShowCursor(SDL_DISABLE); 
        SDL_StopTextInput();
        game = new Application();
        game->loop();
    }
    catch(const std::runtime_error& e)
    {
        std::cout << e.what() << std::endl;
    }
    if (game != nullptr)
    {
        delete game;
    }
    
    freeLibraries();
    return 0;
}

void initLibraries()
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_SYSTEM, "SDL couldn\'t initializeSDL_Error: %s", SDL_GetError());
        exit(1);
    }
    int imageFlags = IMG_INIT_PNG | IMG_INIT_JPG;
    if (!(IMG_Init(imageFlags) & imageFlags))
    {
        SDL_LogError(SDL_LOG_CATEGORY_SYSTEM, "SDL_Image could not initialize! SDL_image Error: %s", IMG_GetError());
        SDL_Quit();
        exit(1);
    }
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        SDL_LogError(SDL_LOG_CATEGORY_SYSTEM, "SDL_Mixer could not initialize! SDL_Mixer Error: %s", Mix_GetError());
        IMG_Quit();
        SDL_Quit();
        exit(1);
    }
}

void freeLibraries()
{
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}
