
#pragma once

//[Headers]     -- You can add your own extra header files here --
#include <juce_core/juce_core.h>
#include <juce_graphics/juce_graphics.h>
#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_gui_extra/juce_gui_extra.h>

// AnimationAppDemo.h does not qualify uses of the juce namespace.
// To avoid changing that file, we just import the namespace as a whole.
// This is super hacky, please do not try this at home ;-)
using namespace juce;
//[/Headers]


//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class ImageViewer : public juce::Component
{
  public:
    //==============================================================================
    ImageViewer();
    ~ImageViewer() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void static initialize(); // Call this to initialize the component
    void static finalize();   // Call this when library is about to be unloaded to
                              // free resources
    void static showWindow();
    void static hideWindow();
    void static displayImage(String path);
    //[/UserMethods]

    void paint(juce::Graphics &g) override;
    void resized() override;

  private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    static ImageViewer *sfInstance;

    std::unique_ptr<juce::DocumentWindow> fWindow;
    //[/UserVariables]

    //==============================================================================

    std::unique_ptr<ImageComponent> image;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ImageViewer)
};

//[EndFile] You can add extra defines here...
//[/EndFile]
