#include "MinesweeperWindow.h"
#include "Tile.h"
#include <iostream>
#include <random>
#include <set>

MinesweeperWindow::MinesweeperWindow(int x, int y, int width, int height, int mines, const string &title) : 
	// Initialiser medlemsvariabler, bruker konstruktoren til AnimationWindow-klassen
	AnimationWindow{x, y, width * cellSize, (height + 1) * cellSize, title},
	width{width}, height{height}, mines{mines}
{
	// Legg til alle tiles i vinduet
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			tiles.emplace_back(new Tile{ Point{j * cellSize, i * cellSize}, cellSize});
			tiles.back()->setCallback(std::bind(&MinesweeperWindow::cb_click, this));
			auto temp = tiles.back().get();
			add(*temp); 
		}
	}

	// Generer tilfeldige posisjoner for minene
	std::random_device rd;
	std::default_random_engine gen(rd());
	std::uniform_int_distribution<> distrib(0, width * height - 1);

	// Sorger for at posisjonene er unike
    std::set<int> minePositions;
    while (minePositions.size() < mines) {
        int pos = distrib(gen);
        minePositions.insert(pos);
    }

	// Legg til miner på tilfeldige posisjoner
	for (const int& i : minePositions) {
		tiles.at(i)->setIsMine(true);
	}
}

vector<Point> MinesweeperWindow::adjacentPoints(Point xy) const {
	vector<Point> points;
	for (int di = -1; di <= 1; ++di) {
		for (int dj = -1; dj <= 1; ++dj) {
			if (di == 0 && dj == 0) {
				continue;
			}

			Point neighbour{ xy.x + di * cellSize,xy.y + dj * cellSize };
			if (inRange(neighbour)) {
				points.push_back(neighbour);
			}
		}
	}
	return points;
}


void MinesweeperWindow::openTile(Point xy) {
	auto& tile = at(xy);
	if (tile->getState() == Cell::closed) {
		tile->open();
		if (tile->getIsMine() == false) {
			vector<Point> closeBy = adjacentPoints(xy);
			int amount = countMines(closeBy);
			if (amount > 0) {
				tile->setAdjMines(amount);
			} else {
				for (const Point& point : closeBy) {
					openTile(point);
				}
			}
		}
	}
}

void MinesweeperWindow::flagTile(Point xy) {
	auto& tile = at(xy);
	if (tile->getState() != Cell::open) {
		tile->flag();
	}
}

// Kaller openTile ved venstreklikk og flagTile ved hoyreklikk
void MinesweeperWindow::cb_click() {
	
	Point xy{this->get_mouse_coordinates()};

	if (!inRange(xy)) {
		return;
	}
	if (this->is_left_mouse_button_down()) {
		openTile(xy);
	}
	else if(this->is_right_mouse_button_down()){
		flagTile(xy);
	}
}

int MinesweeperWindow::countMines(const vector<Point>& coords) const {

	int counter = 0;
	for (const Point& point : coords) {
		auto& tile = at(point);
		if (tile->getIsMine()) {
			counter += 1;
		}
	}

	return counter;
}