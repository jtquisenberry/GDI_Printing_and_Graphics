// Gdiplus_PrinterToBitmap.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "stdafx.h"
#include "afxwin.h"
#include "atlimage.h"
#include <windows.h>
#include <stdio.h>
#include <gdiplus.h>
#include <conio.h>
using namespace Gdiplus;

int main()
{
	/* Demonstrates the inability to capture the contents of a Printer device context
	   to a bitmap. This is true even if a bitmap is attached to the device context
	   before printing.
	*/

	// Initialize GDI+.
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	// Initialize DOCINFO structure
	DOCINFO docInfo;
	ZeroMemory(&docInfo, sizeof(docInfo));
	docInfo.cbSize = sizeof(docInfo);
	docInfo.lpszDocName = L"GdiplusPrint";

	// Get printer HDC, CDC
	LPCTSTR printerName = L"Bullzip PDF Printer";
	HDC hPrinterDC = CreateDC(L"WINSPOOL", printerName, NULL, NULL);

	// Setup graphics objects
	Gdiplus::Graphics* graphics;
	Gdiplus::Graphics* graphics2;
	Pen* pen = new Pen(Color(255, 0, 255, 0));

	// Start printing
	StartDoc(hPrinterDC, &docInfo);
	StartPage(hPrinterDC);

	// Get printer CDC*, memory CDC
	CDC* PrinterDC = CDC::FromHandle(hPrinterDC);
	CDC memDC;
	memDC.CreateCompatibleDC(PrinterDC);

	// Create a new bitmap and size it based on the printer device capabilities.
	CBitmap bitmap;
	bitmap.CreateCompatibleBitmap(PrinterDC, PrinterDC->GetDeviceCaps(HORZRES), PrinterDC->GetDeviceCaps(VERTRES));

	// Insert the CBitmap into the memory device context
	CBitmap* pOldBitmap = memDC.SelectObject(&bitmap);

	// Create a new bitmap and size it based on the printer device capabilities.
	CBitmap bitmap2;
	bitmap2.CreateCompatibleBitmap(PrinterDC, PrinterDC->GetDeviceCaps(HORZRES), PrinterDC->GetDeviceCaps(VERTRES));

	// Insert the CBitmap into the printer device context
	// WARNING: Omitting this step may produce a Page Fault and blue screen of death at BitBlt below
	CBitmap* pOldBitmap2 = PrinterDC->SelectObject(&bitmap2);

	/* Draw without Gdiplus::Graphics*/
	// Draw a rectangle almost the size of the bitmap
	memDC.Rectangle(100, 100, PrinterDC->GetDeviceCaps(HORZRES) - 100, PrinterDC->GetDeviceCaps(VERTRES) - 100);
	// Draw a smaller rectangle
	memDC.Rectangle(0, 0, 500, 500);

	// Draw with Gdiplus::Graphics
	// Draw green rectangles
	graphics = new Gdiplus::Graphics(memDC);
	graphics->DrawRectangle(pen, 50, 50, 200, 300);
	graphics->DrawRectangle(pen, 150, 150, 301, 400);
	graphics->DrawRectangle(pen, 150, 150, 401, 500);
	graphics->DrawRectangle(pen, 50, 50, 501, 600);

	// Print green rectangles
	graphics2 = new Gdiplus::Graphics(PrinterDC->GetSafeHdc());
	graphics2->DrawRectangle(pen, 50, 50, 200, 300);
	graphics2->DrawRectangle(pen, 150, 150, 301, 400);
	graphics2->DrawRectangle(pen, 150, 150, 401, 500);
	graphics2->DrawRectangle(pen, 50, 50, 501, 600);

	// Overlay the contents of PrinterDC to memDC
	// Notice the first two arguments are 300, 300. This is to show where the printer bitmap overlaps the memory bitmap.
	// The memDC contains green rectangles. The PrintDC is an empty rectangle. 
	// The empty rectangle is overlaid onto the memDC.
	memDC.BitBlt(300, 300, PrinterDC->GetDeviceCaps(HORZRES), PrinterDC->GetDeviceCaps(VERTRES), PrinterDC, 0, 0, SRCCOPY);
	
	// Write bitmap to PNG
	CImage Image;
	Image.Attach(bitmap);
	Image.Save(L"D:/file.png", Gdiplus::ImageFormatPNG);

	// Write bitmap2 to PNG
	CImage Image2;
	Image2.Attach(bitmap2);
	Image2.Save(L"D:/file2.png", Gdiplus::ImageFormatPNG);

	// End printing
	EndPage(hPrinterDC);
	EndDoc(hPrinterDC);

	memDC.SelectObject(pOldBitmap);
	PrinterDC->SelectObject(pOldBitmap2);
	
	// Free device contexts
	memDC.DeleteDC();
	PrinterDC->DeleteDC();

	return 0;
}

