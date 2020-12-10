// (c) aidswidjaja 2020-2021
// https://github.com/aidswidjaja/c2i
// See LICENSE for license information
#include "fltk/include/FL/Fl.H"
#include "fltk/include/FL/Fl_Window.H"
#include "fltk/include/FL/Fl_Box.H"
#include "fltk/include/FL/fl_ask.H"
#include "fltk/include/FL/Fl_Progress.H"


#ifdef _WIN32
// WINDOWS
#include <windows.h>
#define usleep(v) Sleep(v/1000)
#else
// UNIX
#include <unistd.h>                            // usleep
#endif

int main(int argc, char **argv) {

    Fl_Window *window = new Fl_Window(300,100);
    window->begin();

    Fl_Box *box = new Fl_Box(100,0,50,50,"Currently importing beatmap/skin"); 
    box->box(FL_NO_BOX);

    Fl_Progress *progress = new Fl_Progress(20,50,200,30);

    progress->minimum(0);                      // set progress range to be 0.0 ~ 1.0
    progress->maximum(1);
    progress->color(0x88888800);               // background color
    progress->selection_color(0xff66aa00);     // progress bar color
    progress->labelcolor(FL_WHITE);            // percent text color
    window->end();                                  // end adding to window
    // Computation loop..
    for ( int t=1; t<=500; t++ ) {
        progress->value(t/500.0);              // update progress bar with 0.0 ~ 1.0 value
        char percent[10];
        sprintf(percent, "%d%%", int((t/500.0)*100.0));
        progress->label(percent);              // update progress bar's label
        Fl::check();                           // give fltk some cpu to update the screen
        usleep(1000);                          // 'your stuff' that's compute intensive
    }

    window->end();

    window->show(argc, argv);

    return (Fl::run());
}

/* to-do:

- pass arguments to darwin
- then, pass those arguments to the win32 batch script under wine
    - message box is hopefully easier with this
- kill darwin after win32 dies