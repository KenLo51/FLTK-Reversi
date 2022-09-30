#ifndef REVERSI_GUI_CLASS_H
#define REVERSI_GUI_CLASS_H

#include <vector>
#include <iostream>

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/Fl_Output.H>

#include "Reversi.h"

#define REVERSI_DEBUG 0
#define REVERSI_HELP 1

class ReversiGUI {
private:
	typedef struct MyStruct
	{
		int x, y;
		ReversiGUI* obj;
	}buttonArrayCbData;
	//
	const unsigned int colSize = 8;
	const unsigned int rowSize = 8;

	Reversi reversi = Reversi(ReversiGUI::colSize, ReversiGUI::rowSize);

	std::vector < std::vector<Fl_Button*> > buttonArray;

	// GUI variables
	Fl_Window* window;
	Fl_Output* statusLabel;
	Fl_Button* startBtn;
	Fl_PNG_Image* lightDiskImg = new Fl_PNG_Image("light_disk.png");
	Fl_PNG_Image* darkDiskImg = new Fl_PNG_Image("dark_disk.png");
	Fl_PNG_Image* validLightDiskImg = new Fl_PNG_Image("valid_light_disk.png");
	Fl_PNG_Image* validDarkDiskImg = new Fl_PNG_Image("valid_dark_disk.png");




	//

	std::vector <buttonArrayCbData*> buttonArray_cb_parameter;

	// GUI functions
	static void buttonArray_cb(Fl_Widget* w, void* data);
	static void startBtn_cb(Fl_Widget* w, void* data);

	void boardUpdate();
public:
	ReversiGUI(int argc, char** argv);

	void WindowInit();
	void ControllerInit();

	void Delete();

	int Run();

};

#endif