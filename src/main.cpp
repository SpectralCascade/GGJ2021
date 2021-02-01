#include <Ossium.h>
#include <OssiumEditor.h>

using namespace Ossium;
using namespace Ossium::Editor;
using namespace std;

int main(int argc, char* argv[])
{

#ifdef OSSIUM_DEBUG
    try {
#endif
    InitialiseOssium();

#ifdef OSSIUM_EDITOR
    ResourceController resources;

    SDL_LogSetAllPriority(SDL_LOG_PRIORITY_VERBOSE);

    EditorController* editor = new EditorController(&resources);

    while (editor->Update())
    {
        // Update until the editor stops running.
    }

    resources.FreeAll();

    delete editor;
    editor = nullptr;
#else // Open new scope such that we clean up objects in the correct order.
{
    Config config;
    config.windowTitle = "Expedition Lost";
    for (int i = 1; i < argc; i++)
    {
        config.startScenes.push_back(argv[i]);
    }
    if (config.startScenes.empty())
    {
        config.startScenes.push_back("assets/Scenes/Game.json");
    }

    // Minimum supported resolution for the prototype.
    config.windowWidth = 1280;
    config.windowHeight = 720;

    EngineSystem engine(config);

    while (engine.Update())
    {
        // Do nothing
    }

}
#endif // OSSIUM_EDITOR

#ifdef OSSIUM_DEBUG
    }
    catch (exception& e)
    {
        Log.Error("Exception occurred! Message: {0}\n\nTerminating Ossium engine...", e.what());
        SDL_ShowSimpleMessageBox(
            SDL_MESSAGEBOX_ERROR,
            "An exception has occurred!",
             Format("{0}\n\nOssium will terminate after this message is closed.", e.what()).c_str(),
             NULL
        );
    }
#endif

    TerminateOssium();
    return 0;
}
