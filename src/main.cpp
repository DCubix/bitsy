#include <iostream>
#include <string>

#include "gorbitsa.hpp"
#include "engine.h"

int main(int argc, char** argv) {

	std::string code = "";

	Gorbitsa gb{};
	gb.load(code);

	Engine eng{};
	eng.start(&gb);

	return 0;
}
