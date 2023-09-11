#include "LibMain.h"
#include <array>

namespace gigperformer
{
namespace sdk
{

GigPerformerAPI *CreateGPExtension(LibraryHandle handle)
{
    return new LibMain(handle);
}

} // namespace sdk
} // namespace gigperformer

// List of menu items
std::vector<std::string> menuNames = {
    "Show Window",
    "Hide Window",
    "Toggle Full Screen"
};

int LibMain::GetMenuCount()
{
    return static_cast<int>(menuNames.size());
}

std::string LibMain::GetMenuName(int index)
{
    std::string text;
    if (index >= 0 && static_cast<std::size_t>(index) < menuNames.size())
    {
        text = menuNames[index];
    }
    return text;
}

void LibMain::InvokeMenu(int index)
{
    if (index >= 0 && static_cast<std::size_t>(index) < menuNames.size())
    {
        switch (index)
        {
        case 0:
            ImageViewer::showWindow();
            break;
        case 1:
            ImageViewer::hideWindow();
            break;
        case 2:
            ImageViewer::toggleFullScreenWindow();
            break;
        default:
            break;
        }
    }
}

extern "C" void ShowImageViewer(GPRuntimeEngine *)
{
    juce::MessageManager::getInstance()->callAsync([]() { ImageViewer::showWindow(); });
}

extern "C" void ShowImageViewerFullScreen(GPRuntimeEngine *vm)
{
    bool isFullScreen = GP_VM_PopBoolean(vm);
    juce::MessageManager::getInstance()->callAsync([=]() { ImageViewer::showWindowFullScreen(isFullScreen); });
}

extern "C" void HideImageViewer(GPRuntimeEngine *)
{
    juce::MessageManager::getInstance()->callAsync([]() { ImageViewer::hideWindow(); });
}

extern "C" void DisplayImage(GPRuntimeEngine *vm)
{
    char buffer[100];
    GP_VM_PopString(vm, buffer, 100);
    std::string s = buffer;
    juce::MessageManager::getInstance()->callAsync([=]() { ImageViewer::displayImage(s); });
}

ExternalAPI_GPScriptFunctionDefinition functionList[] = {
    {"Show", "", "", "Show the image viewer", ShowImageViewer},
    {"ShowFullScreen", "isFullScreen : Boolean", "", "Show the image viewer in full screen mode", ShowImageViewerFullScreen},
    {"Hide", "", "", "Hide the image viewer", HideImageViewer},
    {"DisplayImage", "path : String", "", "Specify the file path of the image to be displayed", DisplayImage},
};

int LibMain::RequestGPScriptFunctionSignatureList(GPScript_AllowedLocations, // these are allowed in any script
                                                  ExternalAPI_GPScriptFunctionDefinition **list)
{
    *list = functionList;
    int count = sizeof(functionList) / sizeof(ExternalAPI_GPScriptFunctionDefinition);
    return count;
}
