#include <iostream>
#include <stdlib.h>
#include <vector>
#include <stdio.h>
#include <fstream>
using namespace std;

vector < vector <int> > eagleLocations;
vector < vector <int> > rabbitLocations;
vector < vector <int> > grassLocations;
vector < vector <int> > grasshopperLocations;
vector < vector <int> > mouseLocations;
vector < vector <int> > snakeLocations;
vector < vector <int> > kookaburraLocations;
vector <int> temp;
vector <int> currentGen;

vector < vector <int> > chart;

int maxEagle, avgEagle, maxRabbit, avgRabbit, maxGrass, avgGrass, maxGrasshopper, avgGrasshopper, maxMouse, avgMouse, maxSnake, avgSnake, maxKookaburra, avgKookaburra;

//38 is the best of both worlds, imo
int width = 40;
int grid[40][40] = {0};

class animal {
	public:	
		int radius;
		int spawn;
};
//land can't handle a range over 30, tbh
animal eagle; //7
animal rabbit; //3
animal grass; //1
animal grasshopper; //2
animal mouse; //4
animal snake; //5
animal kookaburra; //6

int print () {
	for (int x = 0; x < width; x++) {
		for (int i = 0; i < width; i++) {
			cout << grid[x][i] << " ";
		} cout << endl;
	}
}

int genEagle() {
	int amount = rand() % 10 + 10;
	if (amount == 15) {
		amount = 20;
	}
	int randX, randY;
	
	for (int z = 0; z < amount; z++) {
		randX = rand() % width;
		randY = rand() % width;
		grid[randY][randX] = 7;
	}
}

int genKookaburra() {
	int amount = rand() % 10 + 10;
	int randX, randY;
	
	for (int z = 0; z < amount; z++) {
		randX = rand() % width;
		randY = rand() % width;
		grid[randY][randX] = 6;
	}
}

int genSnake() {
	int amount = rand() % 20 + 5;
	int randX, randY;
	
	for (int z = 0; z < amount; z++) {
		randX = rand() % width;
		randY = rand() % width;
		grid[randY][randX] = 5;
	}
}

int genMouse() {
	int amount = rand() % 35 + 6;
	int randX, randY;
	
	for (int z = 0; z < amount; z++) {
		randX = rand() % width;
		randY = rand() % width;
		grid[randY][randX] = 4;
	}
}

int genRabbit() {
	int amount = rand() % 25 + 6;
	int randX, randY;
	
	for (int z = 0; z < amount; z++) {
		randX = rand() % width;
		randY = rand() % width;
		grid[randY][randX] = 3;
	}
}

int genGrasshopper() {
	int amount = rand() % 25 + 6;
	int randX, randY;
	
	for (int z = 0; z < amount; z++) {
		randX = rand() % width;
		randY = rand() % width;
		grid[randY][randX] = 2;
	}
}

int genGrass () {
	int randomX, randomY, randStartX, randStartY;
	srand(time(NULL));
	int patches = rand() % 30 + 15;
	
	for (int z = 0; z < patches; z++) {
		
		//start generating grass at random places;
		randStartX = rand() % width;
		randStartY = rand() % width;
		//generate random lengths/widths for the grass;
		randomX = randStartX + ( rand() % width ) + 1;
		randomY = randStartY + ( rand() % width ) + 1;
		//make sure not to return 0 error;
		if (randomX > width) {
			randomX = width;
		}
		if (randomY > width) {
			randomY = width;
		}
		
		for (int y = randStartY; y < randomY; y++) {
			for (int x = randStartX; x < randomX; x++) {
				grid[y][x] = 1;
			}
		}
		
	}
}

//ik grasses is not grammaticaly correct, but I really needed another var name :)
int eagles, rabbits, grasses, grasshoppers, mice, snakes, kookaburras;

int whichAnimal (int y, int x) {
	temp.clear();
	temp.push_back(x);
	temp.push_back(y);
	bool food = false;
	bool mate = false;
	if (grid[y][x] == 1) {
		grasses++;
		if (grid[y - 1][x] == 1 || grid[y + 1][x] == 1 || grid[y][x + 1] == 1 || grid[y][x - 1] == 1 || grid[y - 1][x - 1] == 1 || grid[y - 1][x + 1] == 1 || grid[y + 1][x - 1] == 1 || grid[y + 1][x + 1] == 1) {
			grassLocations.push_back(temp);
		}
		
		//grassLocations.push_back(temp);
	} else if (grid[y][x] == 2) {
		grasshoppers++;
		for (int i = y - grasshopper.radius; i < y + grasshopper.radius; i++) {
			for (int z = x - grasshopper.radius; z < x + grasshopper.radius; z++) {
				if (grid[i][z] == 1 && food == false) {
					food = true;
					grid[i][z] = 0;
				} else if (grid[i][z] == 2) {
					mate = true;
				} 
				if (mate && food) {
					grasshopperLocations.push_back(temp);
					i = 100000;
					z = 100000;
				} else if ( (i == y + grasshopper.radius - 1 && z == x + grasshopper.radius - 1) || (i == width - 1 || z == width - 1)) {
					grid[y][x] = 0;
				}
			}
		}
	} else if (grid[y][x] == 3) {
		rabbits++;
		for (int i = y - rabbit.radius; i < y + rabbit.radius && i < width; i++) {
			for (int z = x - rabbit.radius; z < x + rabbit.radius && z < width; z++) {
				if (i < 0) {
					i = 0;
				}
				if (z < 0) {
					z = 0;
				}
				
				if (grid[i][z] == 1 && food == false) {
					food = true;
					grid[i][z] = 0;
				} else if (grid[i][z] == 3) {
					mate = true;
				} 
				if (mate && food) {
					rabbitLocations.push_back(temp);
					i = 100000;
					z = 100000;
				} else if ((i == y + rabbit.radius - 1 && z == x + rabbit.radius - 1) || (i == width - 1 || z == width - 1)) {
					grid[y][x] = 0;
				}
			}
		}
	} else if (grid[y][x] == 4) {
		mice++;
		for (int i = y - mouse.radius; i < y + mouse.radius && i < width; i++) {
			for (int z = x - mouse.radius; z < x + mouse.radius && z < width; z++) {
				if (i < 0) {
					i = 0;
				}
				if (z < 0) {
					z = 0;
				}
				
				if (grid[i][z] == 1 && food == false) {
					food = true;
					grid[i][z] = 0;
				} else if (grid[i][z] == 4) {
					mate = true;
				} 
				if (mate && food) {
					mouseLocations.push_back(temp);
					i = 100000;
					z = 100000;
				} else if ((i == y + mouse.radius - 1 && z == x + mouse.radius - 1) || (i == width - 1 || z == width - 1)) {
					grid[y][x] = 0;
				}
			}
		}
		//mouseLocations.push_back(temp);
	} else if (grid[y][x] == 5) {
		snakes++;
		for (int i = y - snake.radius; i < y + snake.radius && i < width; i++) {
			for (int z = x - snake.radius; z < x + snake.radius && z < width; z++) {
				if (i < 0) {
					i = 0;
				}
				if (z < 0) {
					z = 0;
				}
				
				if ( (grid[i][z] == 4 || grid[i][z] == 3) && food == false) {
					food = true;
					grid[i][z] = 0;
				} else if (grid[i][z] == 5) {
					mate = true;
				} 
				if (mate && food) {
					snakeLocations.push_back(temp);
					i = 100000;
					z = 100000;
				} else if ((i == y + snake.radius - 1 && z == x + snake.radius - 1) || (i == width - 1 || z == width - 1)) {
					grid[y][x] = 0;
				}
			}
		}
		//snakeLocations.push_back(temp);
	} else if (grid[y][x] == 6) {
		kookaburras++;
		//kookaburras are capable of eating much more than 1 animal per gen, so we will set it to eat a max of 3. But, they must eat at least 2 to stay alive
		int kookaDigested = 0;
		for (int i = y - kookaburra.radius; i < y + kookaburra.radius && i < width; i++) {
			for (int z = x - kookaburra.radius; z < x + kookaburra.radius && z < width; z++) {
				if (i < 0) {
					i = 0;
				}
				if (z < 0) {
					z = 0;
				}
				
				if ( (grid[i][z] == 4 || grid[i][z] == 5 || grid[i][z] == 2) && kookaDigested < 3) {
					grid[i][z] = 0;
					kookaDigested++;
					if (kookaDigested >= 2) {
						food = true;
					}
					
				} else if (grid[i][z] == 6) {
					mate = true;
				} 
				if (mate && food) {
					kookaburraLocations.push_back(temp);
					i = 100000;
					z = 100000;
				} else if ((i == y + kookaburra.radius - 1 && z == x + kookaburra.radius - 1) || (i == width - 1 || z == width - 1)) {
					grid[y][x] = 0;
				}
			}
		}
		//kookaburraLocations.push_back(temp);
	} else if (grid[y][x] == 7) {
		eagles++;
		//eagle are capable of eating much more than 1 animal per gen, so we will set it to eat a max of 2. But, they must eat at least 1 to stay alive
		int eagleDigested = 0;
		for (int i = y - eagle.radius; i < y + eagle.radius && i < width; i++) {
			for (int z = x - eagle.radius; z < x + eagle.radius && z < width; z++) {
				if (i < 0) {
					i = 0;
				}
				if (z < 0) {
					z = 0;
				}
				
				if ( (grid[i][z] == 6 || grid[i][z] == 5 /*|| grid[i][z] == 3*/) && eagleDigested < 1) {
					grid[i][z] = 0;
					eagleDigested++;
					if (eagleDigested >= 1) {
						food = true;
					}
					
				} else if (grid[i][z] == 7) {
					mate = true;
				} 
				if (mate && food) {
					eagleLocations.push_back(temp);
					i = 100000;
					z = 100000;
				} else if ((i == y + eagle.radius - 1 && z == x + eagle.radius - 1) || (i == width - 1 || z == width - 1)) {
					grid[y][x] = 0;
				}
			}
		}
		//eagleLocations.push_back(temp);
	}
}

int whichAnimal2 (int x, int y) {
	if (grid[y][x] == 1) {
		grasses++;
	} else if (grid[y][x] == 2) {
		grasshoppers++;
	} else if (grid[y][x] == 3) {
		rabbits++;
	} else if (grid[y][x] == 4) {
		mice++;
	} else if (grid[y][x] == 5) {
		snakes++;
	} else if (grid[y][x] == 6) {
		kookaburras++;
	} else if (grid[y][x] == 7) {
		eagles++;
	}
}

int howManyOfEach () {
	cout << endl << "Amount of grass: " << grasses;
	cout << endl << "Number of grasshoppers: " << grasshoppers;
	cout << endl << "Number of rabbits: " << rabbits;
	cout << endl << "Number of mice: " << mice;
	cout << endl << "Number of snakes: " << snakes;
	cout << endl << "Number of kookaburras: " << kookaburras;
	cout << endl << "Number of eagles: " << eagles << endl;
	currentGen.clear();
	currentGen.push_back(grasses);
	currentGen.push_back(grasshoppers);
	currentGen.push_back(rabbits);
	currentGen.push_back(mice);
	currentGen.push_back(snakes);
	currentGen.push_back(kookaburras);
	currentGen.push_back(eagles);
	chart.push_back(currentGen);
	
	if (grasses > maxGrass) {
		maxGrass = grasses;
	}
	if (grasshoppers > maxGrasshopper) {
		maxGrasshopper = grasshoppers;
	}
	if (rabbits > maxRabbit) {
		maxRabbit = rabbits;
	}
	if (mice > maxMouse) {
		maxMouse = mice;
	}
	if (snakes > maxSnake) {
		maxSnake = snakes;
	}
	if (kookaburras > maxKookaburra) {
		maxKookaburra = kookaburras;
	}
	if (eagles > maxEagle) {
		maxEagle = eagles;
	}
	avgGrass += grasses;
	avgGrasshopper += grasshoppers;
	avgMouse += mice;
	avgSnake += snakes;
	avgRabbit += rabbits;
	avgKookaburra += kookaburras;
	avgEagle += eagles;
}

int newGrasshoppers () {
	for (int i = 0; i < grasshopperLocations.size(); i++) {
		if (grasshopperLocations[i][0] + 1 < width) {
			if (grid[grasshopperLocations[i][1]][grasshopperLocations[i][0] + 1] == 0 || grid[grasshopperLocations[i][1]][grasshopperLocations[i][0] + 1] == 1) {
				grid[grasshopperLocations[i][1]][grasshopperLocations[i][0] + 1] = 2;
			}
		}
		if (grasshopperLocations[i][0] - 1 >= 0) {
			if (grid[grasshopperLocations[i][1]][grasshopperLocations[i][0] - 1] == 0 || grid[grasshopperLocations[i][1]][grasshopperLocations[i][0] - 1] == 1) {
				grid[grasshopperLocations[i][1]][grasshopperLocations[i][0] - 1] = 2;
			}
		}
		if (grasshopperLocations[i][1] + 1 < width) {
			if (grid[grasshopperLocations[i][1] + 1][grasshopperLocations[i][0]] == 0 || grid[grasshopperLocations[i][1] + 1][grasshopperLocations[i][0]] == 1) {
				grid[grasshopperLocations[i][1] + 1][grasshopperLocations[i][0]] = 2;
			}
		}
		if (grasshopperLocations[i][1] - 1 >= 0) {
			if (grid[grasshopperLocations[i][1] - 1][grasshopperLocations[i][0]] == 0 || grid[grasshopperLocations[i][1] - 1][grasshopperLocations[i][0]] == 1) {
				grid[grasshopperLocations[i][1] - 1][grasshopperLocations[i][0]] = 2;
			}
		}
	}
}

int newRabbits () {
	int range = rand() % 2 + 1;
	for (int i = 0; i < rabbitLocations.size(); i++) {
		if (rabbitLocations[i][0] + range < width) {
			if (grid[rabbitLocations[i][1]][rabbitLocations[i][0] + range] == 0 || grid[rabbitLocations[i][1]][rabbitLocations[i][0] + range] == 1) {
				grid[rabbitLocations[i][1]][rabbitLocations[i][0] + range] = 3;
			}
		}
		if (rabbitLocations[i][0] - range >= 0) {
			if (grid[rabbitLocations[i][1]][rabbitLocations[i][0] - range] == 0 || grid[rabbitLocations[i][1]][rabbitLocations[i][0] - range] == 1) {
				grid[rabbitLocations[i][1]][rabbitLocations[i][0] - range] = 3;
			}
		}
		if (rabbitLocations[i][1] + range < width) {
			if (grid[rabbitLocations[i][1] + range][rabbitLocations[i][0]] == 0 || grid[rabbitLocations[i][1] + range][rabbitLocations[i][0]] == 1) {
				grid[rabbitLocations[i][1] + range][rabbitLocations[i][0]] = 3;
			}
		}
		if (rabbitLocations[i][1] - range >= 0) {
			if (grid[rabbitLocations[i][1] - range][rabbitLocations[i][0]] == 0 || grid[rabbitLocations[i][1] - range][rabbitLocations[i][0]] == 1) {
				grid[rabbitLocations[i][1] - range][rabbitLocations[i][0]] = 3;
			}
		}
	}
}

int newMice () {
	int range = rand() % 2 + 1;
	for (int i = 0; i < mouseLocations.size(); i++) {
		if (mouseLocations[i][0] + range < width) {
			if (grid[mouseLocations[i][1]][mouseLocations[i][0] + range] == 0 || grid[mouseLocations[i][1]][mouseLocations[i][0] + range] == 1) {
				grid[mouseLocations[i][1]][mouseLocations[i][0] + range] = 4;
			}
		}
		if (mouseLocations[i][0] - range >= 0) {
			if (grid[mouseLocations[i][1]][mouseLocations[i][0] - range] == 0 || grid[mouseLocations[i][1]][mouseLocations[i][0] - range] == 1) {
				grid[mouseLocations[i][1]][mouseLocations[i][0] - range] = 4;
			}
		}
		if (mouseLocations[i][1] + range < width) {
			if (grid[mouseLocations[i][1] + range][mouseLocations[i][0]] == 0 || grid[mouseLocations[i][1] + range][mouseLocations[i][0]] == 1) {
				grid[mouseLocations[i][1] + range][mouseLocations[i][0]] = 4;
			}
		}
		if (mouseLocations[i][1] - range >= 0) {
			if (grid[mouseLocations[i][1] - range][mouseLocations[i][0]] == 0 || grid[mouseLocations[i][1] - range][mouseLocations[i][0]] == 1) {
				grid[mouseLocations[i][1] - range][mouseLocations[i][0]] = 4;
			}
		}
	}
}

int newSnakes () {
	int range = rand() % 2 + 1;
	for (int i = 0; i < snakeLocations.size(); i++) {
		if (snakeLocations[i][0] + range < width) {
			if (grid[snakeLocations[i][1]][snakeLocations[i][0] + range] == 0 || grid[snakeLocations[i][1]][snakeLocations[i][0] + range] == 1) {
				grid[snakeLocations[i][1]][snakeLocations[i][0] + range] = 5;
			}
		}
		if (snakeLocations[i][0] - range >= 0) {
			if (grid[snakeLocations[i][1]][snakeLocations[i][0] - range] == 0 || grid[snakeLocations[i][1]][snakeLocations[i][0] - range] == 1) {
				grid[snakeLocations[i][1]][snakeLocations[i][0] - range] = 5;
			}
		}
		if (snakeLocations[i][1] + range < width) {
			if (grid[snakeLocations[i][1] + range][snakeLocations[i][0]] == 0 || grid[snakeLocations[i][1] + range][snakeLocations[i][0]] == 1) {
				grid[snakeLocations[i][1] + range][snakeLocations[i][0]] = 5;
			}
		}
		if (snakeLocations[i][1] - range >= 0) {
			if (grid[snakeLocations[i][1] - range][snakeLocations[i][0]] == 0 || grid[snakeLocations[i][1] - range][snakeLocations[i][0]] == 1) {
				grid[snakeLocations[i][1] - range][snakeLocations[i][0]] = 5;
			}
		}
	}
}

int newKookaburras () {
	int range = rand() % 3 + 1;
	for (int i = 0; i < kookaburraLocations.size(); i++) {
		//int upOrDown = rand() % 2;
		//if (upOrDown == 0) {
			if (kookaburraLocations[i][0] + range < width) {
				if (grid[kookaburraLocations[i][1]][kookaburraLocations[i][0] + range] == 0 || grid[kookaburraLocations[i][1]][kookaburraLocations[i][0] + range] == 1) {
					grid[kookaburraLocations[i][1]][kookaburraLocations[i][0] + range] = 6;
				}
			}
			if (kookaburraLocations[i][0] - range >= 0) {
				if (grid[kookaburraLocations[i][1]][kookaburraLocations[i][0] - range] == 0 || grid[kookaburraLocations[i][1]][kookaburraLocations[i][0] - range] == 1) {
					grid[kookaburraLocations[i][1]][kookaburraLocations[i][0] - range] = 6;
				}
			}
		//} else {
			if (kookaburraLocations[i][1] + range < width) {
				if (grid[kookaburraLocations[i][1] + range][kookaburraLocations[i][0]] == 0 || grid[kookaburraLocations[i][1] + range][kookaburraLocations[i][0]] == 1) {
					grid[kookaburraLocations[i][1] + range][kookaburraLocations[i][0]] = 6;
				}
			}
			if (kookaburraLocations[i][1] - range >= 0) {
				if (grid[kookaburraLocations[i][1] - range][kookaburraLocations[i][0]] == 0 || grid[kookaburraLocations[i][1] - range][kookaburraLocations[i][0]] == 1) {
					grid[kookaburraLocations[i][1] - range][kookaburraLocations[i][0]] = 6;
				}
			}
		//}
	}
}

int newEagles () {
	int range = rand() % 5 + 1;
	for (int i = 0; i < eagleLocations.size(); i++) {
		//int upOrDown = rand() % 2;
		//if (upOrDown == 0) {
			if (eagleLocations[i][0] + range < width) {
				if (grid[eagleLocations[i][1]][eagleLocations[i][0] + range] == 0 || grid[eagleLocations[i][1]][eagleLocations[i][0] + range] == 1) {
					grid[eagleLocations[i][1]][eagleLocations[i][0] + range] = 7;
				}
			}
			if (eagleLocations[i][0] - range >= 0) {
				if (grid[eagleLocations[i][1]][eagleLocations[i][0] - range] == 0 || grid[eagleLocations[i][1]][eagleLocations[i][0] - range] == 1) {
					grid[eagleLocations[i][1]][eagleLocations[i][0] - range] = 7;
				}
			}
		//} else {
			if (eagleLocations[i][1] + range < width) {
				if (grid[eagleLocations[i][1] + range][eagleLocations[i][0]] == 0 || grid[eagleLocations[i][1] + 5][eagleLocations[i][0]] == range) {
					grid[eagleLocations[i][1] + range][eagleLocations[i][0]] = 7;
				}
			}
			if (eagleLocations[i][1] - range >= 0) {
				if (grid[eagleLocations[i][1] - range][eagleLocations[i][0]] == 0 || grid[eagleLocations[i][1] - range][eagleLocations[i][0]] == 1) {
					grid[eagleLocations[i][1] - range][eagleLocations[i][0]] = 7;
				}
			}
		//}
	}
}


int newGrass () {
	for (int i = 0; i < grassLocations.size(); i++) {
		if (grassLocations[i][0] + 1 < width) {
			if (grid[grassLocations[i][1]][grassLocations[i][0] + 1] == 0) {
				grid[grassLocations[i][1]][grassLocations[i][0] + 1] = 1;
			}
		}
		if (grassLocations[i][0] - 1 >= 0) {
			if (grid[grassLocations[i][1]][grassLocations[i][0] - 1] == 0) {
				grid[grassLocations[i][1]][grassLocations[i][0] - 1] = 1;
			}
		}
		if (grassLocations[i][1] + 1 < width) {
			if (grid[grassLocations[i][1] + 1][grassLocations[i][0]] == 0) {
				grid[grassLocations[i][1] + 1][grassLocations[i][0]] = 1;
			}
		}
		if (grassLocations[i][1] - 1 >= 0) {
			if (grid[grassLocations[i][1] - 1][grassLocations[i][0]] == 0) {
				grid[grassLocations[i][1] - 1][grassLocations[i][0]] = 1;
			}
		}
		if (grassLocations[i][0] + 2 < width) {
			if (grid[grassLocations[i][1]][grassLocations[i][0] + 2] == 0) {
				grid[grassLocations[i][1]][grassLocations[i][0] + 2] = 1;
			}
		}
		if (grassLocations[i][0] - 2 >= 0) {
			if (grid[grassLocations[i][1]][grassLocations[i][0] - 2] == 0) {
				grid[grassLocations[i][1]][grassLocations[i][0] - 2] = 1;
			}
		}
		if (grassLocations[i][1] + 2 < width) {
			if (grid[grassLocations[i][1] + 2][grassLocations[i][0]] == 0) {
				grid[grassLocations[i][1] + 2][grassLocations[i][0]] = 1;
			}
		}
		if (grassLocations[i][1] - 2 >= 0) {
			if (grid[grassLocations[i][1] - 2][grassLocations[i][0]] == 0) {
				grid[grassLocations[i][1] - 2][grassLocations[i][0]] = 1;
			}
		}
		if (grassLocations[i][0] + 3 < width) {
			if (grid[grassLocations[i][1]][grassLocations[i][0] + 3] == 0) {
				grid[grassLocations[i][1]][grassLocations[i][0] + 3] = 1;
			}
		}
		if (grassLocations[i][0] - 3 >= 0) {
			if (grid[grassLocations[i][1]][grassLocations[i][0] - 3] == 0) {
				grid[grassLocations[i][1]][grassLocations[i][0] - 3] = 1;
			}
		}
		if (grassLocations[i][1] + 3 < width) {
			if (grid[grassLocations[i][1] + 3][grassLocations[i][0]] == 0) {
				grid[grassLocations[i][1] + 3][grassLocations[i][0]] = 1;
			}
		}
		if (grassLocations[i][1] - 3 >= 0) {
			if (grid[grassLocations[i][1] - 3][grassLocations[i][0]] == 0) {
				grid[grassLocations[i][1] - 3][grassLocations[i][0]] = 1;
			}
		}
	}
}

int generations = 0;

int generation () {
	eagles = rabbits = grasses = grasshoppers = mice = snakes = kookaburras = 0;
	
	generations++;
	eagleLocations.clear();
	kookaburraLocations.clear();
	snakeLocations.clear();
	mouseLocations.clear();
	rabbitLocations.clear();
	grasshopperLocations.clear();
	grassLocations.clear();
	
	//first time is a check before generating
	for (int y = 0; y < width; y++) {
		for (int x = 0; x < width; x++) {
			
			if (grid[y][x] != 0) {
				whichAnimal (y, x);
			}
			
		}
	}
	
	//srand(time(NULL));
	int randX1 = (rand() % width) - 1;
	int randY1 = (rand() % width) - 1;
	if (randX1 < 0) {randX1 = 0;}
	if (randY1 < 0) {randY1 = 0;}
	int randX2 = randX1 + 1;
	int randY2 = randY1 + 1;

	if (eagles == 0) {
		grid[randY1][randX1] = 7; grid[randY2][randX2] = 7;
	}
	if (kookaburras == 0) {
		grid[randY1][randX1] = 6; grid[randY2][randX2] = 6;
	}
	if (snakes == 0) {
		grid[randY1][randX2] = 5; grid[randY2][randX2] = 5;
	}
	if (mice == 0) {
		grid[randY1][randX1] = 4; grid[randY2][randX2] = 4;
	}
	if (rabbits == 0) {
		grid[randY1][randX1] = 3; grid[randY2][randX2] = 3;
	}
	if (grasshoppers == 0) {
		grid[randY1][randX1] = 2; grid[randY2][randX2] = 2;
	}
	if (grasses == 0) {
		grid[randY1][randX1] = 1; grid[randY2][randX2] = 1;
	}
	
	newGrass();
	newMice();
	newRabbits();
	newGrasshoppers();
	newSnakes();
	newKookaburras();
	newEagles();
	
	
	eagles = rabbits = grasses = grasshoppers = mice = snakes = kookaburras = 0;
	
	for (int y = 0; y < width; y++) {
		for (int x = 0; x < width; x++) {
			
			if (grid[y][x] != 0) {
				whichAnimal2 (x, y);
			}
			
		}
	}
	
	howManyOfEach();
	cout << "Generation: " << generations << endl;
}

int printChartFile() {
	for (int x = 0; x < chart.size(); x++) {
		for (int i = 0; i < chart[x].size(); i++) {
			cout << chart[x][i] << "\t";
		} cout << endl; 
	}
}

int printChart() {
	for (int x = 0; x < chart.size(); x++) {
		if (x == 0) {
			cout << "[ ";
		}
		cout << "[";
		for (int i = 0; i < chart[x].size(); i++) {
			if (i != chart[x].size() - 1) {
			    cout << chart[x][i] << ", ";
			} else {
			    cout << chart[x][i];
			}
		} cout << "]";
		if (x == chart.size() - 1) {
			cout << " ]" << endl;
		} else {
			cout << endl;
		} 
	}
}

int main() {
	
	maxEagle = avgEagle = maxRabbit = avgRabbit = maxGrass = avgGrass = maxGrasshopper = avgGrasshopper = maxMouse = avgMouse = maxSnake = avgSnake = maxKookaburra = avgKookaburra = 0;
	
	eagle.radius = 6;
	kookaburra.radius = 6;
	snake.radius = 5;
	mouse.radius = 5;
	rabbit.radius = 4;
	grasshopper.radius = 1;
	
	int next = 1;
	srand(time(NULL));
	
	genGrass();
	genGrasshopper();
	genRabbit();
	genMouse();
	genSnake();
	genKookaburra();
	genEagle();
	
	generation();
	print();
	
	while (next != 0) {
		cout << "Enter number of generations to skip (1..n), -1 to view additional stats, or 0 to end: ";
		cin >> next;
		if (next == -1) {
		    int a;
		    while (a != 0) {
			char code;
			cout << "Would you like to view max (M), averages (A), or generations (G)?: " << endl;
			cin >> code;
			if (code == 'M') {
				printf(" max grass: %d\n max grasshoppers: %d\n max rabbits: %d\n max mice: %d\n max snakes: %d\n max kookaburras: %d\n max eagles:%d\n", maxGrass, maxGrasshopper, maxRabbit, maxMouse, maxSnake, maxKookaburra, maxEagle);
			} else if (code == 'A') {
				printf(" avg grass: %d\n avg grasshoppers: %d\n avg rabbits: %d\n avg mice: %d\n avg snakes: %d\n avg kookaburras: %d\n avg eagles:%d\n", avgGrass/generations, avgGrasshopper/generations, avgRabbit/generations, avgMouse/generations, avgSnake/generations, avgKookaburra/generations, avgEagle/generations);
			} else if (code == 'G') {
				int spreadSheetOrPython;
				cin >> spreadSheetOrPython;
				if (spreadSheetOrPython == 1) {
				    printChart();
				} else if (spreadSheetOrPython == 2) {
				    printChartFile();
				}
			}
		        cout << "If you would like to continue inquiring enter any integer other than 0. Else enter 0: " << endl;
		        cin >> a;
		        
		    }
			cout << "Enter number of generations to skip (1..n) or 0 to end: ";
			cin >> next;
		}
		//desperately needed to optimize for gens > 1, so we will only print for the last gen for specified skip
		for (int z = 0; z < next; z++) {
			if (z == next - 1) {
				generation();
				print();
			} else {
				generation();
			}
		}
		
	}
	//1	2	3	4	5
}
