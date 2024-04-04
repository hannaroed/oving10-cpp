#include "Tile.h"


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

void Tile::setAdjMines(int n) {
    if (n < 1 || n > 8) {
        throw std::out_of_range("Invalid number of adjacent mines: Must be between 1 and 8.");
    }
	set_label(std::to_string(n));
	set_label_color(minesToColor.at(n));
}
