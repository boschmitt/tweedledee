/*------------------------------------------------------------------------------
| This file is distributed under the MIT License.
| See accompanying file /LICENSE for details.
| Author(s): Bruno Schmitt
*-----------------------------------------------------------------------------*/
#include "tweedledee/base/source_manager.hpp"
#include "tweedledee/quil/ast/ast.hpp"
#include "tweedledee/quil/ast/visitor.hpp"
#include "tweedledee/quil/parser.hpp"
#include "tweedledee/quil/preprocessor.hpp"
#include "tweedledee/quil/semantic.hpp"
#include "tweedledee/quil/token.hpp"
#include "tweedledee/quil/token_kinds.hpp"

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

	tweedledee::source_manager source_manager;
	preprocessor pp_lexer(source_manager);
	semantic semantic;
	parser parser(pp_lexer, semantic, source_manager);

	pp_lexer.add_target_file(argv[1]);
	auto success = parser.parse();
	if (success) {
		std::cout << "Valid Quil =)\n";
	} else {
		std::cout << "Invalid Quil =(\n";
	}
	auto program = semantic.finish();
	print_ast(std::cout, *program);
}
