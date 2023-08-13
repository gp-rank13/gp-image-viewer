/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 7.0.6

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2020 - Raw Material Software Limited.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
#include <juce_events/juce_events.h>
//[/Headers]

#include "ImageViewer.h"

//[MiscUserDefs] You can add your own user definitions and misc code here...
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
//[/MiscUserDefs]

//==============================================================================
ImageViewer::ImageViewer()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    image.reset(new ImageComponent());
    addAndMakeVisible(image.get());

    //[UserPreSize]
    //[/UserPreSize]

    setSize(800, 600);

    //[Constructor] You can add your own custom stuff here..
    fWindow.reset(new MyDocumentWindow());
    fWindow->setContentNonOwned(this, true);
    fWindow->setResizable(true, true);
    fWindow->setUsingNativeTitleBar(true);
    //[/Constructor]
}

ImageViewer::~ImageViewer()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    image = nullptr;

    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void ImageViewer::paint(juce::Graphics &g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll(juce::Colours::black);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void ImageViewer::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]
   
    image->setBounds(0, 0, getWidth(), getHeight());

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
// other code here...
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
    Image imageFile;
    imageFile = ImageFileFormat::loadFrom(File(path));
    sfInstance->image->setImage(imageFile);
}



//[EndFile] You can add extra defines here...
//[/EndFile]
