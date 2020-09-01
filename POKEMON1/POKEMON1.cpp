#include <iostream>
#include"Pokemon.h"
int main()
{
	Race<0> Charmander;
	Race<1> Bulbasaur;
	Race<2> Squirtle;
	Race<3> Pikachu;

	Pokemon A(Charmander, "小刚");
	Pokemon B(Pikachu, "小智");
	Battle war(A, B);
	war.start();
	return 0;
}

