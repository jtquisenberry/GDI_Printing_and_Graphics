# Windows GDI Graphics and Printing with MFC

This repository contains projects demonstrating the use of Windows GDI+ and GDI to draw bitmaps and write to a printer.


# Gdiplus_PrinterToBitmap

This MFC project demonstrates drawing rectangles to bitmap and printer.

* Create a printer device context. 
* Creates a memory device context compatible with the printer device context.
* Creates a bitmap object (bitmap 1) and inserts it into the memory device context. 
* Creates a bitmap object (bitmap 2) and inserts it into the printer device context. 
* Draws a a rectangle with `CDC::Rectangle` into the memory device context in the center of the image, 100 pixels from each edge.
* Draws a 500x500 rectangle with `CDC::Rectangle`, also into the memory device context.

![White Rectangles on Memory DC](images/Gdiplus_PrinterToBitmap_001.png?raw=true "White Rectangles on Memory DC")


* Draws four green rectangles with `Gdiplus::Graphics`, also into the memory device context.

![Added Green-bordered rectangles on Memory DC](images/Gdiplus_PrinterToBitmap_002.png?raw=true "Added Green-bordered rectangles on Memory DC")


* Draws four green rectangles with `Gdiplus::Graphics`, this time into the print device context. 

![Empty, Black Canvas from Printer DC](images/Gdiplus_PrinterToBitmap_003.png?raw=true "Empty, Black Canvas from Printer DC")


* Overlays the contents of the printer device context onto the memory device context at position 300, 300 in the memory device context. This is done with `CDC::BitBlt`.

Notice that the empty rectangle from the printer device context covers a portion of the green-bordered rectanges in the memory device context. This demonstrates that a printer device context is write-only.

![Alt text](images/Gdiplus_PrinterToBitmap_004.png?raw=true "Title")


* Sends the printer device context to the printer using `EndPage`. The code specifies printer "Bullzip PDF Printer", which writes the output to a PDF file.


![Alt text](images/Gdiplus_PrinterToBitmap_007.png?raw=true "Title")