
#include <juce_events/juce_events.h>
#include "ImageViewer.h"
#include "BinaryData.h"

ImageViewer *ImageViewer::sfInstance = nullptr;

class MyDocumentWindow : public juce::DocumentWindow
{
  public:
    MyDocumentWindow() : DocumentWindow("GP Image Viewer", juce::Colours::black, DocumentWindow::allButtons, true)
    {
    }
    virtual ~MyDocumentWindow()
    {
    }
    virtual void closeButtonPressed() override
    {
        setVisible(false);
    };
};

ImageViewer::ImageViewer()
{
    image.reset(new ImageComponent());
    addAndMakeVisible(image.get());
    setSize(720, 480);
    defaultImage = ImageFileFormat::loadFrom(BinaryData::DefaultImage_png, (size_t) BinaryData::DefaultImage_pngSize);
    image->setImage(defaultImage);

    fWindow.reset(new MyDocumentWindow());
    fWindow->setContentNonOwned(this, true);
    fWindow->setResizable(true, true);
    fWindow->setUsingNativeTitleBar(true);

    #if JUCE_WINDOWS
        extensionWindow->getPeer()->setIcon(getWindowIcon());
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
        if (sfInstance == nullptr)
        {
            sfInstance = new ImageViewer();
            sfInstance->fWindow->setTopLeftPosition(100, 100);
        }

        jassert(sfInstance != nullptr);
        sfInstance->fWindow->setVisible(false);
    });
}

void ImageViewer::finalize()
{
    if (sfInstance != nullptr)
    {
        delete sfInstance;
        sfInstance = nullptr;
    }
}

void ImageViewer::showWindow()
{
    sfInstance->fWindow->setVisible(true);
    sfInstance->fWindow->toFront(true);
}

void ImageViewer::hideWindow()
{
    sfInstance->fWindow->setVisible(false);
}

void ImageViewer::displayImage(String path)
{
    Image imageFile = ImageFileFormat::loadFrom(File(path));
    if (imageFile.isValid()) 
    {
        sfInstance->image->setImage(imageFile);
    } else
    {
        sfInstance->image->setImage(sfInstance->defaultImage);
    }
    
}

Image ImageViewer::getWindowIcon() 
{
    Image img;
    String imageBase64 = WINDOW_ICON;
    MemoryOutputStream mo;
    auto result = Base64::convertFromBase64(mo, imageBase64);
    if (result) {
        img = ImageFileFormat::loadFrom(mo.getData(), mo.getDataSize());
    }
    return img;
}