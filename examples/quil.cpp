/*-------------------------------------------------------------------------------------------------
| This file is distributed under the MIT License.
| See accompanying file /LICENSE for details.
| Author(s): Bruno Schmitt
*------------------------------------------------------------------------------------------------*/

#include "tweedledee/quil/quil.hpp"
#include "tweedledee/quil/ast/visitor.hpp"

#include <iostream>

using namespace tweedledee::quil;

void print_ast(std::ostream& out, const program& program)
{
	out << "AST for :\n";
	std::string prefix;
	visit(program, [&](const ast_node& node, visitor_info info) {
		if (node.kind() == ast_node_kinds::program)
			return true;
		else if (info == visitor_info::container_end) {
			prefix.pop_back();
			prefix.pop_back();
		} else {
			out << prefix;
			if (info == visitor_info::container_begin)
				prefix += "| ";
			out << "|-";
			node.print(out);
			out << '\n';
		}
		return true;
	});
}

int main(int argc, char** argv)
{
	if (argc < 2) {
		std::cerr << "Input file not specified.\n";
	}
	auto program = quil_read_file(argv[1]);
	std::cout << "Num qubits: " << program->qubits.size() << '\n';
	print_ast(std::cout, *program);
}
