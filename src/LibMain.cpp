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
    "Show",
    "Hide",
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
        default:
            break;
        }
    }
}

extern "C" void ShowImageViewer(GPRuntimeEngine *)
{
    juce::MessageManager::getInstance()->callAsync([]() { ImageViewer::showWindow(); });
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
    juce::MessageManager::getInstance()->callAsync([s]() { ImageViewer::displayImage(s); });
}

ExternalAPI_GPScriptFunctionDefinition functionList[] = {
    {"Show", "", "", "Show the image viewer", ShowImageViewer},
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
