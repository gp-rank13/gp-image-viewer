# Image Viewer Extension for Gig Performer

## Overview

An extension for [Gig Performer](https://gigperformer.com) that provides an additional resizable window for displaying images. The loading of image files is performed using Gig Performer's scripting language ([GPScript](https://gigperformer.com/support.html)). This provides a great deal of flexibility in how you how you integrate the extension into your gig file. The two examples below demonstrate how you can load/display images using: (1) radio buttons; (2) the streaming audio file player, timeline actions, and OSC.

> _Disclaimer: This is a user-created extension and is not supported by Deskew Technologies. Extensions can cause unexpected behaviour in Gig Performer, and in extreme situations could cause it to crash. Please test it thoroughly before using it in any live performances!_

## Installation

Download the extension (library) files for either MacOS or Windows from the [Releases](https://github.com/gp-rank13/gp-image-viewer/releases) page.  

Mac users will need to move the _libGPImageViewer.dylib_ file into this folder and then restart Gig Performer:
```
/Users/Shared/Gig Performer/Extensions
```
Mac users will also need to authorize the extension via _System Preferences_ > 
_Privacy & Security_. Scroll down until you locate an entry that references the extension. Allow it to be loaded and then restart Gig Performer.

Windows users will need to move the _GPImageViewer.dll_ file into this folder and then restart Gig Performer:
```
C:\Users\Public\Documents\Gig Performer\Extensions
```

When opening Gig Performer, a prompt will appear asking to confirm whether to install the extension.

## Usage
### GP Script Functions
After installing the extension, custom GPScript functions will be available to use, and are listed in the _Code Helper_ autocomplete list. They are all prefixed with _GPImageViewer_.

> **DisplayImage** : _Display the image with the specified file path_  
> - GPImageViewer_DisplayImage (path : String)

<br />

If the *path* is an empty string (e.g. ""), then the default image is displayed (the GP logo).



> **Show** : _Show the Image Viewer window_
> - GPImageViewer_Show ()

<br />

> **Hide** : _Hide the Image Viewer window_
> - GPImageViewer_Hide ()

<br />

> **ShowFullScreen** : _Show the Image Viewer window in full screen or normal mode_
> - GPImageViewer_ShowFullScreen (isFullScreen : Boolean)


### Example 1: Radio Buttons

![gp-image-viewer-radiobuttons](https://github.com/gp-rank13/gp-image-viewer/assets/107261652/b3661f8a-3d4c-4762-983f-afd940e2c087)

1. Add switch widgets to the local or globl rackspace.
2. In the Widget Properties _General_ tab, map each widget to the same _Radio Group_.
3. In the Widget Properties _Advanced_ tab, give each widget a unique name. In this script example, 5 widgets have been named _ImageButton1_ to _ImageButton5_.
4. Copy and paste the below code into either the relevant local/global Script Editor (accessible via the Gig Performmer _Window_ menu).
5. Update the file paths to match images on your system. There is a _Tip_ at the end of this documentation about using relative file paths if you store the images in the Gig Performer folder.
6. Click _Compile_ at the bottom of the script editor.
```
Var
   ImageButton1,ImageButton2,ImageButton3,ImageButton4,ImageButton5 : Widget
   ImageFilePaths : String Array = [
   "", // A blank file path will display the default image - the GP logo.
   "~/Pictures/gp-image-1.png", // Update this to your image location
   "~/Pictures/gp-image-2.png", // Update this to your image location
   "~/Pictures/gp-image-3.png", // Update this to your image location
   "~/Pictures/gp-image-4.png" // Update this to your image location
   ]

On WidgetValueChanged(w : Widget, index: integer, newValue : double) from ImageButton1,ImageButton2,ImageButton3,ImageButton4,ImageButton5
    if newValue == 1.0 then
        GPImageViewer_Show()
        GPImageViewer_DisplayImage(ImageFilePaths[index])
    end
End
```
### Example 2: Streaming Audio File Player

![gp-image-viewer-safp-v2](https://github.com/gp-rank13/gp-image-viewer/assets/107261652/0ffa8a23-b8c7-4114-ae9d-1a5cc9f98c52)

1. Activate OSC in the Gig Performer _Options_ window.
2. Add the _Streaming Audio File Player_ to the local/global rackspace.
3. Add an audio file and Markers at the point where the image should change.
4. Add a Marker Action for _Send OSC Message_.
5. Enter the OSC message in the format:
> /ImageViewer "path-to-file"

e.g. MacOS
> /ImageViewer "~/Pictures/gp-image-1.png"

e.g. Windows
> /ImageViewer "C:\Users\rank13\Pictures\gp-image-1.png"

6. Copy and paste the below code into either the relevant local/global Script Editor (accessible via the Gig Performmer _Window_ menu).
7. Click _Compile_ at the bottom of the script editor.
8. Note: There is a _Tip_ at the end of this documentation about using relative file paths if you store the images in the Gig Performer folder.
```
On OSCMessageReceived(m : OSCMessage) Matching "/ImageViewer"
    GPImageViewer_DisplayImage(OSC_GetArgAsString(m, 0))
    GPImageViewer_Show()
End
```
### Tip: File Paths

By default, your image file paths should be an absolute path.

MacOS Example:
> /Users/rank13/Pictures/gp-image-1.png

> ~/Pictures/gp-image-1.png

Windows Example
> C:\Users\rank13\Pictures\gp-image-1.png

However, you can simplify the file paths to only require the file name itself, by using a variable within the script to store the parent folder path, or by placing all the images in the main Gig Performer folder on your system.

For the latter option, this GPScript function generates the file path to your main Gig Performer folder:
> GigPerformerDocumentsFolder()

It can be combined with a child folder (e.g. _Images_), and allows you to simplify your list of files in the script to only require the filename itself, or the OSC message to only include the filename itself.
e.g.

> GPImageViewer_DisplayImage(GigPerformerDocumentsFolder()+"Images/"+ImageFilePaths[index])
```
// Modified version of the Radio Button script that allows you to list the file names only. It requires all images to be stored in your main Gig Performer folder and an 'Images' subfolder. Windows users will need to change the forward slash to backslash: "Images\".

Var
   ImageButton1,ImageButton2,ImageButton3,ImageButton4,ImageButton5 : Widget
   ImageFilePaths : String Array = [
   "", // A blank file path will display the default image - the GP logo.
   "gp-image-1.png",
   "gp-image-2.png",
   "gp-image-3.png",
   "gp-image-4.png"
   ]

On WidgetValueChanged(w : Widget, index: integer, newValue : double) from ImageButton1,ImageButton2,ImageButton3,ImageButton4,ImageButton5
    if newValue == 1.0 then
        GPImageViewer_Show()
        GPImageViewer_DisplayImage(GigPerformerDocumentsFolder()+"Images/"+ImageFilePaths[index])
    end
End
```

```
// Modified version of the Timeline Action/OSC script that allows you to specify the file names only in the OSC message. It requires all images to be stored in your main Gig Performer folder and an 'Images' subfolder. Windows users will need to change the forward slash to backslash: "Images\".

On OSCMessageReceived(m : OSCMessage) Matching "/ImageViewer"
    GPImageViewer_DisplayImage(GigPerformerDocumentsFolder()+"Images/"+OSC_GetArgAsString(m, 0))
    GPImageViewer_Show()
End
```

## Building the Extension

To customize/build the extension, refer to the [Gig Performer SDK](https://github.com/gigperformer/gp-sdk) GitHub page.