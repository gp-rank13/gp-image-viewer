#pragma once

#include <cstddef>
#include <gigperformer/sdk/GPMidiMessages.h>
#include <gigperformer/sdk/GPUtils.h>
#include <gigperformer/sdk/GigPerformerAPI.h>
#include "ImageViewer.h"

const std::string XMLProductDescription =
    R"xml(<Library>
    <Product Name="GP Image Viewer" Version="1.0" BuildDate="13/8/2023"></Product>
    <Description>Display images in a dedicated window</Description>
    "</Library>)xml";

class LibMain : public gigperformer::sdk::GigPerformerAPI
{
  protected:
    int GetMenuCount() override;
    std::string GetMenuName(int index) override;
    void InvokeMenu(int itemIndex) override;

    int RequestGPScriptFunctionSignatureList(GPScript_AllowedLocations location,
                                             ExternalAPI_GPScriptFunctionDefinition **list) override;

  public:
    LibMain(LibraryHandle handle) : GigPerformerAPI(handle)
    {
    }
    virtual ~LibMain()
    {
    }

    void OnOpen() override
    {
        ImageViewer::initialize();
    }

    void OnClose() override
    {
        ImageViewer::finalize();
    }

    void Initialization() override
    {
        registerCallback("OnOpen");
        registerCallback("OnClose");
    }

    std::string GetProductDescription() override
    {
        return XMLProductDescription;
    }
};
