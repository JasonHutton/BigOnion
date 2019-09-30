#include<iostream>
#include<SDL.h>
using namespace std;
int main(int argc, char* argv[])
{

	if (SDL_Init(SDL_INIT_EVERYTHING) > 0) {
		cout << "SDL Error:" << SDL_GetError() << endl;
	}
	
	return EXIT_SUCCESS;
}