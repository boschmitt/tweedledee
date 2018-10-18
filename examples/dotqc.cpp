/*-------------------------------------------------------------------------------------------------
| This file is distributed under the MIT License.
| See accompanying file /LICENSE for details.
| Author(s): Bruno Schmitt
*------------------------------------------------------------------------------------------------*/

#include "tweedledee/dotqc/dotqc.hpp"
#include "tweedledee/gate_kinds.hpp"

#include <cstdlib>
#include <iostream>

using namespace tweedledee;

class reader final : public dotqc_reader<gate_kinds> {
public:
	reader() = default;

	void on_qubit(std::string label)
	{
		std::cout << "Found qubit: " << label << '\n';
	}

	void on_input(std::string label)
	{
		std::cout << "Found input: " << label << '\n';
	}

	void on_output(std::string label)
	{
		std::cout << "Found output: " << label << '\n';
	}

	void on_gate(gate_kinds kind, std::string qubit_label)
	{
		std::cout << "Found single qubit gate: " << gate_name(kind) << " gate\n";
		(void) qubit_label;
	}

	void on_gate(gate_kinds kind, std::vector<std::string> const& controls,
	             std::vector<std::string> const& targets)
	{
		std::cout << "Found multiple qubit gate: " << gate_name(kind) << " gate\n";
		(void) controls;
		(void) targets;
	}

	void on_end()
	{}
};

int main(int argc, char** argv)
{
	if (argc < 2) {
		std::cerr << "[e] Input file not specified.\n";
		return EXIT_FAILURE;
	}
	reader dotqc_reader;
	dotqc_read(argv[1], dotqc_reader);
	return EXIT_SUCCESS;
}
