/*------------------------------------------------------------------------------
| This file is distributed under the MIT License.
| See accompanying file /LICENSE for details.
| Author(s): Bruno Schmitt < bruno [at] oschmitt [dot] com >
*-----------------------------------------------------------------------------*/
#include "tweedledee/dotqc/dotqc.hpp"
#include <cstdlib>
#include <iostream>

using namespace tweedledee;

int main(int argc, char** argv)
{
	if (argc < 2) {
		std::cerr << "[e] Input file not specified.\n";
		return EXIT_FAILURE;
	}
	dotqc_read(argv[1]);
	return EXIT_SUCCESS;
}
