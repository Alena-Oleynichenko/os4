#include <iostream>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <random>

void draw_painting(Display* display, Window window, GC gc)
{
    // Colors
    unsigned long soft_red =      0xBA362F;
    unsigned long tan =        0xD2B48C;
    unsigned long light_green =   0x92BA8A;
    unsigned long green =         0x33522D;
    unsigned long dark_green =    0x141C13;
    unsigned long dark_wood =     0x453028;
    unsigned long sky =      0xADD8E6;
    unsigned long light_wood =    0x363331;
    unsigned long dirt =          0x261C19;

    // *******************************
    // *     Painting background     *
    // *******************************
    XSetForeground(display, gc, sky); //Sky
    XFillRectangle(display, window, gc, 0, 0, 800, 600);
    XSetForeground(display, gc, light_green); //Trees
    XFillArc(display, window, gc, 230, 275, 50, 200, 0, 360*64);
    XFillArc(display, window, gc, 250, 250, 50, 200, 0, 360*64);


    XFillArc(display, window, gc, 600, 350, 25, 100, 0, 360*64);
    XFillArc(display, window, gc, 850, 100, 50, 400, 0, 360*64);
    XSetForeground(display, gc, light_wood);
    XFillRectangle(display, window, gc, 265, 350, 15, 100);
    XFillRectangle(display, window, gc, 607, 400, 7, 50);
    XSetForeground(display, gc, dark_green); //Ground
    XFillRectangle(display, window, gc, 0, 425, 800, 175);


    XSetForeground(display, gc, green); // Trees and bushes on foreground
    XFillArc(display, window, gc, -150, 200, 100, 650, 0, 360*64);
    XFillArc(display, window, gc, 850, 225, 600, 600, 0, 360*64);

    XFillArc(display, window, gc,900, 350, 700, 650, 0, 360*64);

XSetForeground(display, gc, light_wood);
    XFillRectangle(display, window, gc, -83, 450, 25, 350);



    XSetForeground(display, gc, soft_red); //grib
    XFillArc(display, window, gc, 100, 400, 50, 20, 0, 360*64);
    XFillArc(display, window, gc, 200, 400, 50, 20, 0, 360*64);
    XFillArc(display, window, gc, 150, 420, 50, 20, 0, 360*64);
    XFillArc(display, window, gc, 250, 420, 50, 20, 0, 360*64);

    XSetForeground(display, gc, tan);
    XFillRectangle(display, window, gc, 120, 410, 10, 40);
XFillRectangle(display, window, gc, 220, 410,10, 40);
XFillRectangle(display, window, gc, 170, 430, 10, 40);
XFillRectangle(display, window, gc, 270, 430, 10, 40);


}
int main()
{
    Display *main_display;
    GC gc;
    XEvent event;

    if ((main_display = XOpenDisplay(NULL)) == NULL)
        exit(1);

    int main_screen_number = DefaultScreen(main_display);

    Window main_window = XCreateSimpleWindow(main_display, RootWindow(main_display, main_screen_number), 10, 10, 800, 600, 1, 0xFFFFFF, 0);
    XSelectInput(main_display, main_window, ExposureMask | KeyPressMask| ButtonPressMask);
    XMapWindow(main_display, main_window);

    gc = XCreateGC(main_display, DefaultRootWindow(main_display), 0, 0);
    while(true)
    {
        XNextEvent(main_display, &event);

        if (event.type == Expose) draw_painting(main_display, main_window, gc);
        if ((event.type == KeyPress) && (XLookupKeysym(&event.xkey, 0) == XK_Escape)) break;
        if ((event.type == ButtonPress) && (event.xbutton.x < 10) && (event.xbutton.y < 10)) break;
    }
    XCloseDisplay(main_display);

    return 0;
}