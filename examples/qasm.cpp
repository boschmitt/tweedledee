/*-------------------------------------------------------------------------------------------------
| This file is distributed under the MIT License.
| See accompanying file /LICENSE for details.
| Author(s): Bruno Schmitt
*------------------------------------------------------------------------------------------------*/
#include "tweedledee/qasm/qasm.hpp"
#include "tweedledee/qasm/ast/visitor.hpp"

#include <fmt/color.h>
#include <fmt/format.h>
#include <iostream>

using namespace tweedledee::qasm;

void node_printer(ast_node const& node)
{
	switch (node.kind()) {
	case ast_node_kinds::decl_gate:
		fmt::print(fg(fmt::color::green) | fmt::emphasis::bold, "decl_gate ");
		fmt::print(fg(fmt::color::cyan), "{}",
		           static_cast<decl_gate const&>(node).identifier());
		break;

	case ast_node_kinds::decl_param:
		fmt::print(fg(fmt::color::green) | fmt::emphasis::bold, "decl_param ");
		fmt::print(fg(fmt::color::cyan), "{}",
		           static_cast<decl_param const&>(node).identifier());
		break;

	case ast_node_kinds::decl_register:
		fmt::print(fg(fmt::color::green) | fmt::emphasis::bold, "decl_register ");
		fmt::print(fg(fmt::color::cyan), "{}",
		           static_cast<decl_register const&>(node).identifier());
		fmt::print(fg(fmt::color::green), " '{}:{}'",
		           static_cast<decl_register const&>(node).type() == register_type::quantum ?
		               "Quantum" :
		               "Classical",
		           static_cast<decl_register const&>(node).size());
		break;

	case ast_node_kinds::expr_binary_op:
		fmt::print(fg(fmt::terminal_color::bright_magenta) | fmt::emphasis::bold,
		           "expr_binary_op ");
		fmt::print("{}", static_cast<expr_binary_op const&>(node).op());
		break;

	case ast_node_kinds::expr_decl_ref:
		fmt::print(fg(fmt::terminal_color::bright_magenta) | fmt::emphasis::bold,
		           "expr_decl_ref ");
		node_printer(*static_cast<expr_decl_ref const&>(node).declaration());
		break;

	case ast_node_kinds::expr_integer:
		fmt::print(fg(fmt::terminal_color::bright_magenta) | fmt::emphasis::bold,
		           "expr_integer ");
		fmt::print(fg(fmt::color::cyan), "{}",
		           static_cast<expr_integer const&>(node).evaluate());
		break;

	case ast_node_kinds::expr_real:
		fmt::print(fg(fmt::terminal_color::bright_magenta) | fmt::emphasis::bold,
		           "expr_real ");
		fmt::print(fg(fmt::color::cyan), "{}", static_cast<expr_real const&>(node).value());
		break;

	case ast_node_kinds::expr_reg_idx_ref:
		fmt::print(fg(fmt::terminal_color::bright_magenta) | fmt::emphasis::bold,
		           "expr_reg_idx_ref ");
		break;

	case ast_node_kinds::expr_unary_op:
		fmt::print(fg(fmt::terminal_color::bright_magenta) | fmt::emphasis::bold,
		           "expr_unary_op ");
		fmt::print(fg(fmt::color::cyan), "{}",
		           static_cast<expr_unary_op const&>(node).name());
		break;

	case ast_node_kinds::stmt_cnot:
		fmt::print(fg(fmt::terminal_color::bright_magenta) | fmt::emphasis::bold,
		           "stmt_cnot");
		break;

	case ast_node_kinds::stmt_gate:
		fmt::print(fg(fmt::terminal_color::bright_magenta) | fmt::emphasis::bold,
		           "stmt_gate");
		break;

	case ast_node_kinds::stmt_unitary:
		fmt::print(fg(fmt::terminal_color::bright_magenta) | fmt::emphasis::bold,
		           "stmt_unitary");
		break;

	case ast_node_kinds::program:
	default:
		break;
	}
}

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
			node_printer(node);
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
	auto program = qasm_read_from_file(argv[1]);
	if (program) {
		print_ast(std::cout, *program);
	}
}
