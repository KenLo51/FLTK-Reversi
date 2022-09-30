#include "Reversi_GUI_Class.h"

int main(int argc, char** argv)
{
	ReversiGUI reversiGame = ReversiGUI(argc, argv);
	return Fl::run();
}