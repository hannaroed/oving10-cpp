#pragma once
#include "AnimationWindow.h"
#include "widgets/Button.h"
#include <map>
#include <string>
#include <stdexcept> // For std::out_of_range

// const std::vector<TDT4102::Color> minesToColorVec{TDT4102::Color::blue,
// 											TDT4102::Color::red,
// 											TDT4102::Color::dark_green,
// 											TDT4102::Color::dark_magenta,
// 											TDT4102::Color::dark_blue,
// 											TDT4102::Color::dark_cyan,
// 											TDT4102::Color::dark_red,
// 											TDT4102::Color::gold};

// const TDT4102::Color minesToColorArr[8] = {TDT4102::Color::blue,
// 											TDT4102::Color::red,
// 											TDT4102::Color::dark_green,
// 											TDT4102::Color::dark_magenta,
// 											TDT4102::Color::dark_blue,
// 											TDT4102::Color::dark_cyan,
// 											TDT4102::Color::dark_red,
// 											TDT4102::Color::gold};


// De forskjellige tilstandene en Tile kan være i
enum class Cell {
	closed,
	open,
	flagged }; 

class Tile : public TDT4102::Button
{
private:
	bool isMine = false;

	Cell state = Cell::closed;
	void set_label(std::string s) { this->setLabel(s);}
	void set_label_color(TDT4102::Color c) {this->setLabelColor(c);}

	// For å sette labelfarge i henhold til hvor mange miner som er rundt
	// Fails to initialize when compiled with clang++ on MacOS, all Colors become black transparent
	const std::map<int, TDT4102::Color> minesToColor{{1, TDT4102::Color::blue},
											{2, TDT4102::Color::red},
											{3, TDT4102::Color::dark_green},
											{4, TDT4102::Color::dark_magenta},
											{5, TDT4102::Color::dark_blue},
											{6, TDT4102::Color::dark_cyan},
											{7, TDT4102::Color::dark_red},
											{8, TDT4102::Color::gold}};

public:
	Tile(TDT4102::Point pos, int size);

	void open();
	void flag();
	void close();

	Cell getState() const { return state; }

    void setIsMine(bool mineStatus) { isMine = mineStatus; }
    bool getIsMine() const { return isMine; }

	void setAdjMines(int n);
};
