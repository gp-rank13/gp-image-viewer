
#pragma once

#include <juce_core/juce_core.h>
#include <juce_graphics/juce_graphics.h>
#include <juce_gui_basics/juce_gui_basics.h>

using namespace juce;

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

class ImageViewer : public juce::Component
{
  public:
    ImageViewer();
    ~ImageViewer() override;

    void static initialize(); // Call this to initialize the component
    void static finalize();   // Call this when library is about to be unloaded to free resources
    void static showWindow();
    void static hideWindow();
    void static toggleFullScreenWindow();
    void static showWindowFullScreen(bool isFullScreen);
    void static displayImage(String path); 
    void paint(juce::Graphics &g) override;
    void resized() override;

  private:
    Image getWindowIcon();
    static ImageViewer *viewer;
    Image defaultImage;
    std::unique_ptr<MyDocumentWindow> window;
    std::unique_ptr<ImageComponent> image;
    const juce::String WINDOW_ICON = "iVBORw0KGgoAAAANSUhEUgAAABAAAAAQCAYAAAAf8/9hAAAAAXNSR0IArs4c6QAAAIRlWElmTU0AKgAAAAgABQESAAMAAAABAAEAAAEaAAUAAAABAAAASgEbAAUAAAABAAAAUgEoAAMAAAABAAIAAIdpAAQAAAABAAAAWgAAAAAAAAGQAAAAAQAAAZAAAAABAAOgAQADAAAAAQABAACgAgAEAAAAAQAAABCgAwAEAAAAAQAAABAAAAAABklvbAAAAAlwSFlzAAA9hAAAPYQB1ayvdAAAAVlpVFh0WE1MOmNvbS5hZG9iZS54bXAAAAAAADx4OnhtcG1ldGEgeG1sbnM6eD0iYWRvYmU6bnM6bWV0YS8iIHg6eG1wdGs9IlhNUCBDb3JlIDYuMC4wIj4KICAgPHJkZjpSREYgeG1sbnM6cmRmPSJodHRwOi8vd3d3LnczLm9yZy8xOTk5LzAyLzIyLXJkZi1zeW50YXgtbnMjIj4KICAgICAgPHJkZjpEZXNjcmlwdGlvbiByZGY6YWJvdXQ9IiIKICAgICAgICAgICAgeG1sbnM6dGlmZj0iaHR0cDovL25zLmFkb2JlLmNvbS90aWZmLzEuMC8iPgogICAgICAgICA8dGlmZjpPcmllbnRhdGlvbj4xPC90aWZmOk9yaWVudGF0aW9uPgogICAgICA8L3JkZjpEZXNjcmlwdGlvbj4KICAgPC9yZGY6UkRGPgo8L3g6eG1wbWV0YT4KGV7hBwAAAttJREFUOBF1U0tLW2EQPTc+bnzHiEExvtKgaFAJJU0IuAjEhUvBjYJxI5ju4qZpcW/jD3AtuFERQRF1U+xWoa2CigYDvlEkGF+YXB/5OjOL0E0H7s13M3Nm5sycTwOZUsp/dnYWu7q6+khnnR5omsauf03Rh2YymTI1NTW/GxoavlDMFoN9m5ubanBwUJFTlZWVqYqKCmWxWBggT1VVlaqurlYEVARUQ0NDijFkn7C7u/uzv79fNTY2pnt7e7MOh0MxgIODwaDyer1K1/VcMpvNxuf0wMCA2t/f/6Gtrq6mwuGwpb6+XhUXF2t9fX2gDrgzrK2toaWlBS6XC0VFRSgoKMDt7S1WVlbU0tKStri4mMzPZDL6+fk5qBrGx8cFeH19DWoVe3t76OnpQXt7Oy4vL1FSUoLm5ma8vLxgdnaWf3XT6+urDGp0dBTEG0QD3d3diEQioCooLy/HwcEBOjo6sLCwgIeHB2xsbAiGiqtcAhoSjo+PkUgk4Ha74fF4MD09LQkKCwsFMDIyguXlZczMzKC1tRWUQDPRS5xEQ7NarXK+ubnB29sb6urq5DuVSmF9fR2np6cIhUIIBAJgmkwll4ADaIUYi4wJ39LSUpjNZglk7rW1tZicnERTUxMMw5DEXFwS2O12dqqdnR2EP4fFmUwmwZU5mPSBubk5zM/Pg9abSyAd8Ovx8RFdXV1gjgyIx+NwOD7g/f0dpAFZXSwWg9/vx9PTE7LZrGyLsEo6eH5+lh3z7lkHd3d3GB4OgXQBHiDvn43nwmBOzCZDpD8N5sp8KisrxUnqw9TUFA4PD3F/fy8gBvDKGcyF8vLyOKGRTwrbJqEESDQGiUfn4fEaWQdsrELuoK2tDel0WoBHR0cGxVBd83Y+iecrcdui1swnJye59pxOp1S6uLiQ1nkWfEN5oJ2dnWafz8eS/yZ3dmJiwkutfqdhuimRLqX/8+LrTMA/XDgajf76C4CBivkurfrLAAAAAElFTkSuQmCC";

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(ImageViewer)
};
