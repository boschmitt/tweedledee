/*-------------------------------------------------------------------------------------------------
| This file is distributed under the MIT License.
| See accompanying file /LICENSE for details.
| Author(s): Bruno Schmitt
*------------------------------------------------------------------------------------------------*/
#include "tweedledee/base/source_manager.hpp"
#include "tweedledee/qasm/ast/ast.hpp"
#include "tweedledee/qasm/ast/visitor.hpp"
#include "tweedledee/qasm/parser.hpp"
#include "tweedledee/qasm/preprocessor.hpp"
#include "tweedledee/qasm/semantic.hpp"
#include "tweedledee/qasm/token.hpp"
#include "tweedledee/qasm/token_kinds.hpp"

#include <iostream>

using namespace tweedledee::qasm;

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
	// while (1) {
	// 	auto token = pp_lexer.next_token();
	// 	if (token.is(TokenKind::eof))
	// 		break;
	// 	std::cout << "[debug] found " << token.name()
	// 	          << " length: " << token.length << "\n";
	// }

	auto success = parser.parse();
	if (success) {
		std::cout << "Valid QASM 2.0 =)\n";
	} else {
		std::cout << "Invalid QASM 2.0 =(\n";
	}
	auto program = semantic.finish();
	print_ast(std::cout, *program);
}
