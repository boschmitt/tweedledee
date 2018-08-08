/*------------------------------------------------------------------------------
| This file is distributed under the MIT License.
| See accompanying file /LICENSE for details.
| Author(s): Bruno Schmitt
*-----------------------------------------------------------------------------*/
#pragma once

#include <cstdint>
#include <memory>
#include <ostream>

#include "../ast_node.hpp"
#include "../ast_node_kinds.hpp"

namespace tweedledee {
namespace quil { 

/*! \brief Qubit AST node

  A qubit is referred to by its integer index.
  For example, Q5 is referred to by 5.

*/
class qubit final : public ast_node {
public:
	static std::unique_ptr<qubit> build(uint32_t location,
	                                    uint32_t index)
	{
		auto result = std::unique_ptr<qubit>(
			new qubit(location, index));
		return result;
	}

private:
	qubit(uint32_t location, uint32_t index)
		: ast_node(location)
		, index_(index)
	{ }

	ast_node_kinds do_get_kind() const override
	{ return ast_node_kinds::qubit; }

	void do_print(std::ostream& out) const override
	{
		out << "qubit " << index_;
	}

private:
	uint32_t index_;
};

} // namespace quil
} // namespace tweedledee
