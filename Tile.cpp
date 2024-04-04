#include "Tile.h"
#include <iostream>


// For aa sette Tilelabel i henhold til state
const std::map<Cell, std::string> cellToSymbol{{Cell::closed, ""},
									 			{Cell::open, ""},
									 	  		{Cell::flagged, "|>"}};

Tile::Tile(TDT4102::Point pos, int size) : 
	Button({pos.x, pos.y}, 1.5*size, size, "") {
		setButtonColor(TDT4102::Color::silver);
	}

void Tile::open() {
	if (state == Cell::closed) {
		setButtonColor(TDT4102::Color::white);
		state = Cell::open;
		if (isMine) {
			set_label("X");
			set_label_color(TDT4102::Color::red);
		}
	}
}

void Tile::flag() {
	if (state == Cell::flagged) {
		state = Cell::closed;
		set_label(cellToSymbol.at(state));
	} else {
		state = Cell::flagged;
		set_label(cellToSymbol.at(state));
		set_label_color(TDT4102::Color::black);
	}
}

TDT4102::Color numMinesToColor(int n) {
	// Will be the same object at every call! Gets constructed once for the first call, doesn't get deallocated when the function ends.
	static std::vector<TDT4102::Color> minesToColorVec;

	if (minesToColorVec.empty()) {  // If the vector is empty, initialize it
		std::cout << "Initializing minesToColorVec\n";
		minesToColorVec = {TDT4102::Color::blue,
							TDT4102::Color::red,
							TDT4102::Color::dark_green,
							TDT4102::Color::dark_magenta,
							TDT4102::Color::dark_blue,
							TDT4102::Color::dark_cyan,
							TDT4102::Color::dark_red,
							TDT4102::Color::gold};
	}
	// Usually the vector is already initialized, so we just return the color at index n - 1
	return minesToColorVec[n - 1];
}

void Tile::setAdjMines(int n) {
    if (n < 1 || n > 8) {
        throw std::out_of_range("Invalid number of adjacent mines: Must be between 1 and 8.");
    }
	set_label(std::to_string(n));
	set_label_color(numMinesToColor(n));
	// set_label_color(TDT4102::Color::green);
}
