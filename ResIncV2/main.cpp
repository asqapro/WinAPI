#include <iostream>
#include <fstream>
#include <windows.h>

using namespace std;

template<typename T, size_t size>
size_t char_size(T (&buffer)[ size ])
{
    std::cout << "Size: " << size << "\n";
    return size;
}

unsigned char* get_bitmap(HWND wind, int size_x, int size_y){
    HDC dc = GetDC(wind); //get the device context of the window
    HDC dc_cap = CreateCompatibleDC(dc); //create a compatible dc out of that
    HBITMAP hCaptureBitmap = CreateCompatibleBitmap(dc, size_x, size_y); //make a bitmap
    SelectObject(dc_cap, hCaptureBitmap); //select it in memory
    BitBlt(dc_cap, 0, 0, size_x+1, size_y+1, dc, 0, 0, SRCCOPY); //and bitblt it

    //getting the size of the picture
    BITMAP bm;
    GetObject(hCaptureBitmap, sizeof(bm), &bm);
    int width(bm.bmWidth), height(bm.bmHeight);

    //creating a bitmapheader for getting the dibits
    BITMAPINFOHEADER bminfoheader;
    ::ZeroMemory(&bminfoheader, sizeof(BITMAPINFOHEADER));
    bminfoheader.biSize        = sizeof(BITMAPINFOHEADER);
    bminfoheader.biWidth       = width;
    bminfoheader.biHeight      = -height;
    bminfoheader.biPlanes      = 1;
    bminfoheader.biBitCount    = 32;
    bminfoheader.biCompression = BI_RGB;

    bminfoheader.biSizeImage = (width*2) * 4 * (height*2);
    bminfoheader.biClrUsed = 0;
    bminfoheader.biClrImportant = 0;

    //create a buffer and let the GetDIBits fill in the buffer
    unsigned char* pPixels = new unsigned char[(((width*2) * (height*2))*4)];
    if( !GetDIBits(CreateCompatibleDC(0), hCaptureBitmap, 0, height, pPixels, (BITMAPINFO*) &bminfoheader, DIB_RGB_COLORS)){ // load pixel info
        //return if fails but first delete the resources
        DeleteObject(hCaptureBitmap);
        delete [] pPixels; // delete the array of objects
        return NULL;
    }
    ReleaseDC(wind, dc); //release the device context to the wind
    DeleteDC(dc_cap); //delete the device context that was captured
    DeleteObject(hCaptureBitmap); //delete the bitmap
    return pPixels;
}

void save_bmp(HWND wind, int w, int h){
    unsigned char* pixels = get_bitmap(wind, w, h);
    cout << "Sizeof pixels: " << sizeof(pixels) << endl;
    unsigned char* pix_copy = new unsigned char[((w * h)*4)*4];
    //memcpy(pix_copy, pixels, ((w * h)*4)*4);
    memset(pix_copy,0,((w * h)*4)*4);
    //
    //
    //ISSUE: SIZEOF(PIXELS)/SIZEOF(PIXELS[0]) DOES NOT RETURN CORRECT SIZE, AS IT IS A POINTER
    //
    //
    //w*=2;
    //h*=2;
    for(int y=0; y<h*2; y++){
        for(int x=0; x<w*2; x++){
            if(y-1 > 0){
                if(x-1 > 0){
                    unsigned int r = pixels[(w*y+x) * 4 + 2]; //get the pixel's Red shade
                    unsigned int g = pixels[(w*y+x) * 4 + 1]; //get the pixel's Green shade
                    unsigned int b = pixels[(w*y+x) * 4 + 0]; //get the pixel's Blue shade
                    pix_copy[(w*(y-1)+(x-1)) * 4 + 2] = r;
                    pix_copy[(w*(y-1)+(x-1)) * 4 + 1] = g;
                    pix_copy[(w*(y-1)+(x-1)) * 4 + 0] = b;
                }
                unsigned int r = pixels[(w*y+x) * 4 + 2]; //get the pixel's Red shade
                unsigned int g = pixels[(w*y+x) * 4 + 1]; //get the pixel's Green shade
                unsigned int b = pixels[(w*y+x) * 4 + 0]; //get the pixel's Blue shade
                pix_copy[(w*(y-1)+x) * 4 + 2] = r;
                pix_copy[(w*(y-1)+x) * 4 + 1] = g;
                pix_copy[(w*(y-1)+x) * 4 + 0] = b;
                if(x+1 < w){
                    unsigned int r = pixels[(w*y+x) * 4 + 2]; //get the pixel's Red shade
                    unsigned int g = pixels[(w*y+x) * 4 + 1]; //get the pixel's Green shade
                    unsigned int b = pixels[(w*y+x) * 4 + 0]; //get the pixel's Blue shade
                    pix_copy[(w*(y-1)+(x+1)) * 4 + 2] = r;
                    pix_copy[(w*(y-1)+(x+1)) * 4 + 1] = g;
                    pix_copy[(w*(y-1)+(x+1)) * 4 + 0] = b;
                }
            }
            if(y+0 >= 0){
                if(x-1 > 0){
                    unsigned int r = pixels[(w*y+x) * 4 + 2]; //get the pixel's Red shade
                    unsigned int g = pixels[(w*y+x) * 4 + 1]; //get the pixel's Green shade
                    unsigned int b = pixels[(w*y+x) * 4 + 0]; //get the pixel's Blue shade
                    pix_copy[(w*y+(x-1)) * 4 + 2] = r;
                    pix_copy[(w*y+(x-1)) * 4 + 1] = g;
                    pix_copy[(w*y+(x-1)) * 4 + 0] = b;
                }
                unsigned int r = pixels[(w*y+x) * 4 + 2]; //get the pixel's Red shade
                unsigned int g = pixels[(w*y+x) * 4 + 1]; //get the pixel's Green shade
                unsigned int b = pixels[(w*y+x) * 4 + 0]; //get the pixel's Blue shade
                pix_copy[(w*y+x) * 4 + 2] = r;
                pix_copy[(w*y+x) * 4 + 1] = g;
                pix_copy[(w*y+x) * 4 + 0] = b;
                if(x+1 < w){
                    unsigned int r = pixels[(w*y+x) * 4 + 2]; //get the pixel's Red shade
                    unsigned int g = pixels[(w*y+x) * 4 + 1]; //get the pixel's Green shade
                    unsigned int b = pixels[(w*y+x) * 4 + 0]; //get the pixel's Blue shade
                    pix_copy[(w*y+(x+1)) * 4 + 2] = r;
                    pix_copy[(w*y+(x+1)) * 4 + 1] = g;
                    pix_copy[(w*y+(x+1)) * 4 + 0] = b;
                }
            }
            if(y+1 < h){
                if(x-1 > 0){
                    unsigned int r = pixels[(w*y+x) * 4 + 2]; //get the pixel's Red shade
                    unsigned int g = pixels[(w*y+x) * 4 + 1]; //get the pixel's Green shade
                    unsigned int b = pixels[(w*y+x) * 4 + 0]; //get the pixel's Blue shade
                    pix_copy[(w*(y+1)+(x-1)) * 4 + 2] = r;
                    pix_copy[(w*(y+1)+(x-1)) * 4 + 1] = g;
                    pix_copy[(w*(y+1)+(x-1)) * 4 + 0] = b;
                }
                unsigned int r = pixels[(w*y+x) * 4 + 2]; //get the pixel's Red shade
                unsigned int g = pixels[(w*y+x) * 4 + 1]; //get the pixel's Green shade
                unsigned int b = pixels[(w*y+x) * 4 + 0]; //get the pixel's Blue shade
                pix_copy[(w*(y+1)+x) * 4 + 2] = r;
                pix_copy[(w*(y+1)+x) * 4 + 1] = g;
                pix_copy[(w*(y+1)+x) * 4 + 0] = b;
                if(x+1 < w){
                    unsigned int r = pixels[(w*y+x) * 4 + 2]; //get the pixel's Red shade
                    unsigned int g = pixels[(w*y+x) * 4 + 1]; //get the pixel's Green shade
                    unsigned int b = pixels[(w*y+x) * 4 + 0]; //get the pixel's Blue shade
                    pix_copy[(w*(y+1)+(x+1)) * 4 + 2] = r;
                    pix_copy[(w*(y+1)+(x+1)) * 4 + 1] = g;
                    pix_copy[(w*(y+1)+(x+1)) * 4 + 0] = b;
                }
            }
        }
    }
    FILE *f;
    unsigned char *img = NULL;
    int filesize = 54 + 3*(w*2)*(h*2);  //w is your image width, h is image height, both int
    img = (unsigned char *)malloc(3*(w*2)*(h*2));
    memset(img,0,sizeof(img));
    for(int y=0; y<h*2; y++){
        for(int x=0; x<w*2; x++){
            unsigned int r = pix_copy[(w*y+x) * 4 + 2]; //get the pixel's Red shade
            unsigned int g = pix_copy[(w*y+x) * 4 + 1]; //get the pixel's Green shade
            unsigned int b = pix_copy[(w*y+x) * 4 + 0]; //get the pixel's Blue shade
            img[(x+y*w)*3+2] = (unsigned char)(r);
            img[(x+y*w)*3+1] = (unsigned char)(g);
            img[(x+y*w)*3+0] = (unsigned char)(b);
        }
    }
    unsigned char bmpfileheader[14] = {'B','M', 0,0,0,0, 0,0, 0,0, 54,0,0,0};
    unsigned char bmpinfoheader[40] = {40,0,0,0, 0,0,0,0, 0,0,0,0, 1,0, 24,0};
    unsigned char bmppad[3] = {0,0,0};

    bmpfileheader[2] = (unsigned char)(filesize);
    bmpfileheader[3] = (unsigned char)(filesize>> 8);
    bmpfileheader[4] = (unsigned char)(filesize>>16);
    bmpfileheader[5] = (unsigned char)(filesize>>24);

    bmpinfoheader[4] = (unsigned char)(w);
    bmpinfoheader[5] = (unsigned char)(w>> 8);
    bmpinfoheader[6] = (unsigned char)(w>>16);
    bmpinfoheader[7] = (unsigned char)(w>>24);
    bmpinfoheader[8] = (unsigned char)(h);
    bmpinfoheader[9] = (unsigned char)(h>> 8);
    bmpinfoheader[10] = (unsigned char)(h>>16);
    bmpinfoheader[11] = (unsigned char)(h>>24);

    f = fopen("img.bmp","wb");
    fwrite(bmpfileheader,1,14,f);
    fwrite(bmpinfoheader,1,40,f);
    for(int i=0; i<h; i++)
    {
        fwrite(img+(w*(h-i-1)*3),3,w,f);
        fwrite(bmppad,1,(4-(w*3)%4)%4,f);
    }
    fclose(f);
}

int main()
{
    RECT desktop;
    // Get a handle to the desktop window
    const HWND hDesktop = GetDesktopWindow();
    // Get the size of screen to the variable desktop
    GetWindowRect(hDesktop, &desktop);
    save_bmp(hDesktop, desktop.right, desktop.bottom);
    return 0;
}
