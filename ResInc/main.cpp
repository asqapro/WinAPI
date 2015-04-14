#include <windows.h>
#include <iostream>
#define Winver 0x500
#include <fstream>
#include <istream>
#include <sstream>
#include <gdiplus.h>
using namespace std;

void read_pixels(wstring fileName){
    // Start Gdiplus
    Gdiplus::GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;
    Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

    // Load the image
    Gdiplus::Image* image = Gdiplus::Image::FromFile(fileName.c_str(), false);
    Gdiplus::Bitmap* bitmap = dynamic_cast<Gdiplus::Bitmap*>(image);

    int x_max = image->GetWidth();
    int y_max = image->GetHeight();
    int x_current = 0;
    int y_current = 0;
    Gdiplus::Color pixel;
    for(;x_current < x_max;x_current++){
        for(;y_current < y_max;y_current++){
            bitmap->GetPixel(x_current, y_current, &pixel);
            cout << "here" << endl;
            cout << pixel.GetGreen() << endl;
        }
    }

    // delete the image when done
    delete image; image = 0;

    // Shutdown Gdiplus
    Gdiplus::GdiplusShutdown(gdiplusToken);
}
int main()
{
    string fileName = "";
    cout << "Enter filename with complete path (escape \'\\' characters with \\\'s): ";
    cin >> fileName;
    read_pixels(wstring(fileName.begin(), fileName.end()));
    return 0;
}
