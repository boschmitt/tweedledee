/*------------------------------------------------------------------------------
| This file is distributed under the MIT License.
| See accompanying file /LICENSE for details.
| Author(s): Bruno Schmitt
*-----------------------------------------------------------------------------*/
#pragma once

#include "ast/ast.hpp"

#include <memory>
#include <string_view>
#include <unordered_map>

namespace tweedledee {
namespace quil {

// This implements semantic analysis and AST building.
class semantic {
	program::builder program_;

public:
	semantic() = default;
	semantic(const semantic&) = delete;
	void operator=(const semantic&) = delete;

	void on_gate_statement(std::unique_ptr<stmt_gate> stmt_gate)
	{
		if (stmt_gate == nullptr) {
			return;
		}
		program_.add_child(std::move(stmt_gate));
	}

	std::unique_ptr<program> finish()
	{
		return program_.finish();
	}
};

} // namespace quil
} // namespace tweedledee
