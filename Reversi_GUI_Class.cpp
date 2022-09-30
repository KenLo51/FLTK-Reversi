#include "Reversi_GUI_Class.h"

ReversiGUI::ReversiGUI(int argc, char** argv) {
	ReversiGUI::WindowInit();

	ReversiGUI::ControllerInit();

	ReversiGUI::window->end();
	ReversiGUI::window->show(argc, argv);
}

void ReversiGUI::WindowInit() {
	ReversiGUI::window = new Fl_Window(500, 500);

	//Fl_Output* turnLabel = new Fl_Output(0, 0, 300, 50);
	//turnLabel->value("Turn");

	ReversiGUI::statusLabel = new Fl_Output(150, 0, 300, 50, "Dark  turn");
	ReversiGUI::statusLabel->value((ReversiGUI::reversi.turn == REVERSI_TURN_DARK) ? "Dark  turn" : "Light turn");
	ReversiGUI::startBtn = new Fl_Button(50, 0, 100, 50, "START");

	// create 2d button array
	const int buttonSize = 50;
	const int buttonOffsetX = 50;
	const int buttonOffsetY = 50;
	Fl_Color buttonBackgroundColor = fl_rgb_color(124, 203, 124);
	for (unsigned int rowIdx = 0; rowIdx < ReversiGUI::colSize; rowIdx++) {
		std::vector<Fl_Button*> newRow;
		for (unsigned int colIdx = 0; colIdx < ReversiGUI::rowSize; colIdx++) {
			Fl_Button* newButton = new Fl_Button(colIdx * buttonSize + buttonOffsetX, rowIdx * buttonSize + buttonOffsetY, buttonSize, buttonSize);
			newButton->color(buttonBackgroundColor);
			newRow.push_back(newButton);
		}
		ReversiGUI::buttonArray.push_back(newRow);
	}


}
void ReversiGUI::buttonArray_cb(Fl_Widget* w, void* data) {
	ReversiGUI::buttonArrayCbData cbData = *(ReversiGUI::buttonArrayCbData*)data;
	unsigned int colIdx = cbData.x;
	unsigned int rowIdx = cbData.y;
	ReversiGUI* self = cbData.obj;

	int returnCode = self->reversi.Put(rowIdx, colIdx);
	if (returnCode == REVERSI_RESULT_DARK)
		self->statusLabel->value("Dark Win");
	else if (returnCode == REVERSI_RESULT_LIGHT)
		self->statusLabel->value("Light Win");
	else if (returnCode == REVERSI_RESULT_DRAW)
		self->statusLabel->value("Draw");
	else
		self->statusLabel->value((self->reversi.turn == REVERSI_TURN_DARK)? "Dark  turn" : "Light turn");
#if REVERSI_DEBUG
	if (returnCode == 0)
		std::cout << "success" << std::endl;
	else
		std::cout << "fail" << std::endl;

	for (unsigned int i = 0; i < 8; i++) {
		for (unsigned int j = 0; j < 8; j++) {
			std::cout << self->reversi.board[i][j] << "\t";
		}
		std::cout << std::endl;
	}
#endif
	self->boardUpdate();
#if REVERSI_DEBUG
	std::cout << rowIdx << " , " << colIdx << std::endl;
#endif
}

void ReversiGUI::startBtn_cb(Fl_Widget* w, void* data) {
	ReversiGUI* self = (ReversiGUI*)data;
	self->reversi.NewGame();
	self->boardUpdate();
}
void ReversiGUI::boardUpdate() {
	for (unsigned int rowIdx = 0; rowIdx < ReversiGUI::colSize; rowIdx++) {
		for (unsigned int colIdx = 0; colIdx < ReversiGUI::rowSize; colIdx++) {
			short data = ReversiGUI::reversi.board[rowIdx][colIdx];
			if (data == REVERSI_BOARD_ELEMENT_DARK)
				ReversiGUI::buttonArray[rowIdx][colIdx]->image(darkDiskImg);
			else if (data == REVERSI_BOARD_ELEMENT_LIGHT)
				ReversiGUI::buttonArray[rowIdx][colIdx]->image(lightDiskImg);
#if REVERSI_HELP
			else if (data == REVERSI_BOARD_ELEMENT_VAILD_DARK)
				ReversiGUI::buttonArray[rowIdx][colIdx]->image(validDarkDiskImg);
			else if (data == REVERSI_BOARD_ELEMENT_VAILD_LIGHT)
				ReversiGUI::buttonArray[rowIdx][colIdx]->image(validLightDiskImg);
#endif
			else
				ReversiGUI::buttonArray[rowIdx][colIdx]->image(NULL);
			ReversiGUI::buttonArray[rowIdx][colIdx]->redraw();
		}
	}

}
void ReversiGUI::ControllerInit() {
	// buttonArray controller
	for (unsigned int rowIdx = 0; rowIdx < ReversiGUI::colSize; rowIdx++) {
		for (unsigned int colIdx = 0; colIdx < ReversiGUI::rowSize; colIdx++) {
			ReversiGUI::buttonArrayCbData* cbData = new ReversiGUI::buttonArrayCbData;
			cbData->x = colIdx;	cbData->y = rowIdx;
			cbData->obj = this;
			buttonArray_cb_parameter.push_back(cbData);
			ReversiGUI::buttonArray[rowIdx][colIdx]->callback((Fl_Callback*)(ReversiGUI::buttonArray_cb), cbData);
		}
	}

	ReversiGUI::startBtn->callback((Fl_Callback*)(ReversiGUI::startBtn_cb), this);

	ReversiGUI::reversi.NewGame();
	ReversiGUI::boardUpdate();
}
void ReversiGUI::Delete(){
	ReversiGUI::reversi.Delete();
	for (unsigned int i = 0; i < buttonArray_cb_parameter.size(); i++)
		delete buttonArray_cb_parameter[i];
}
int ReversiGUI::Run() {
	int returnCode = Fl::run();
	return Fl::run();
}