
#include "ImageViewer.h"
#include "BinaryData.h"
#include <juce_events/juce_events.h>

ImageViewer *ImageViewer::viewer = nullptr;

ImageViewer::ImageViewer()
{
    image.reset(new ImageComponent());
    addAndMakeVisible(image.get());
    defaultImage = ImageFileFormat::loadFrom(BinaryData::DefaultImage_png, (size_t)BinaryData::DefaultImage_pngSize);
    image->setImage(defaultImage);

    setSize(720, 480);

    window.reset(new MyDocumentWindow());
    window->setContentNonOwned(this, true);
    window->setResizable(true, true);
    window->setUsingNativeTitleBar(true);

    #if JUCE_WINDOWS
        window->getPeer()->setIcon(getWindowIcon());
    #endif
}

ImageViewer::~ImageViewer()
{
    image = nullptr;
}

void ImageViewer::paint(juce::Graphics &g)
{
    g.fillAll(juce::Colours::black);
}

void ImageViewer::resized()
{
    image->setBounds(0, 0, getWidth(), getHeight());
}


void ImageViewer::initialize()
{
    juce::MessageManager::getInstance()->callAsync([]() {
        if (viewer == nullptr)
        {
            viewer = new ImageViewer();
            viewer->window->setTopLeftPosition(100, 100);
        }
        jassert(viewer != nullptr);
        viewer->window->setVisible(false);
    });
}

void ImageViewer::finalize()
{
    if (viewer != nullptr)
    {
        delete viewer;
        viewer = nullptr;
    }
}

void ImageViewer::showWindow()
{
    viewer->window->setVisible(true);
    viewer->window->toFront(true);
}

void ImageViewer::hideWindow()
{
    viewer->window->setVisible(false);
}

void ImageViewer::toggleFullScreenWindow()
{
    bool isFullScreen = viewer->window->isFullScreen();
    #ifdef JUCE_WINDOWS
        isFullScreen = Desktop::getInstance().getKioskModeComponent() == getTopLevelComponent();
    #endif
    ImageViewer::showWindowFullScreen(!isFullScreen);
}

void ImageViewer::showWindowFullScreen(bool isFullScreen)
{
    #ifdef JUCE_WINDOWS
        Desktop::getInstance().setKioskModeComponent(isFullScreen ? getTopLevelComponent() : nullptr, false);
        if (!isFullScreen) viewer->window->getPeer()->setIcon(getWindowIcon());
    #else
        viewer->window->setFullScreen(isFullScreen);
    #endif
}

void ImageViewer::displayImage(String path)
{
    Image imageFile = ImageFileFormat::loadFrom(File(path));
    if (imageFile.isValid())
    {
        viewer->image->setImage(imageFile);
    }
    else
    {
        viewer->image->setImage(viewer->defaultImage);
    }
}

Image ImageViewer::getWindowIcon()
{
    Image img;
    String imageBase64 = WINDOW_ICON;
    MemoryOutputStream mo;
    auto result = Base64::convertFromBase64(mo, imageBase64);
    if (result)
    {
        img = ImageFileFormat::loadFrom(mo.getData(), mo.getDataSize());
    }
    return img;
}