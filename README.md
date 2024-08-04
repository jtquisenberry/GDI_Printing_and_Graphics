# Windows Graphics and Printing with GDI and GDI+

This repository contains projects demonstrating the use of Windows GDI+ and GDI to draw bitmaps and write to a printer.


# Gdiplus_MemBitmapToPrinter

This MFC project demonstrates drawing graphics to a memory device context and then sending the associated bitmap to a printer.

* Create a printer device context. 
* Creates a memory device context compatible with the printer device context.
* Creates a bitmap object and inserts it into the memory device context. 
* Draws a a rectangle with `CDC::Rectangle` into the memory device context in the center of the image, 100 pixels from each edge.
* Draws a 500x500 rectangle with `CDC::Rectangle` into the memory device context.
* Draws four green rectangles with `Gdiplus::Graphics` into the memory device context.
* Copies the contents of the memory device context into the printer device context using `CDC::BitBlt`.
* Saves the bitmap associated with the memory device context to a PNG file.

![Multiple Rectangles on Memory DC](images/Gdiplus_MemBitmapToPrinter_001.png?raw=true "Multiple Rectangles on Memory DC")

* Sends the printer device context to print with `EndPage`. 

The following image is a screen capture of the PDF generated by the printer "Bullzip PDF Printer".

![Multiple Rectangles Printed](images/Gdiplus_MemBitmapToPrinter_002.png?raw=true "Multiple Rectangles Printed")


# Gdiplus_PrinterToBitmap

This MFC project demonstrates the impossibility of extracting graphics from a printer device context. The project includes drawing of graphics to bitmaps and to a printer.

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

![Printer DC Overlaid on Memory DC](images/Gdiplus_PrinterToBitmap_004.png?raw=true "Printer DC Overlaid on Memory DC")


* Sends the printer device context to the printer using `EndPage`. The code specifies printer "Bullzip PDF Printer", which writes the output to a PDF file.


![Screenshot of Printed PDF](images/Gdiplus_PrinterToBitmap_007.png?raw=true "Screenshot of Printed PDF")



# GdiPrint_OpenPrinter

This non-MFC project demonstrates drawing text with a printer when the printer is specified with `OpenPrinter`. It draws text with `ExtTextOut` and `TextOut` API calls.

Following is a partial screenshot of a PDF generated by the "Bullzip PDF Printer". 

![OpenPrinter Text Out](images/GdiPrint_OpenPrinter_001.png?raw=true "OpenPrinter Text Out")


# GdiPrint_PrintDlg

This non-MFC project demonstrates drawing text with a printer when the printer is specified with `PrintDlg`. It draws text with `ExtTextOut` and `TextOut` API calls. There are two calls to `StartPage` to allow printing two pages.

Following are partial screenshots of a two-page PDF generated by the "Bullzip PDF Printer".


![PrintDlg Text Out Page 1](images/GdiPrint_PrintDlg_001.png?raw=true "PrintDlg Text Out Page 1")


![PrintDlg Text Out Page 2](images/GdiPrint_PrintDlg_002.png?raw=true "PrintDlg Text Out Page 2")


# Notes 

Projects specify hard-coded paths for bitmap files. Be sure to specify paths on the local machine.

