/*------------------------------------------------------------------------------
| This file is distributed under the MIT License.
| See accompanying file /LICENSE for details.
| Author(s): Bruno Schmitt < bruno [at] oschmitt [dot] com >
*-----------------------------------------------------------------------------*/
#pragma once

#include "../gate_kinds.hpp"

#include <experimental/filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace fs = std::experimental::filesystem;

namespace tweedledee {

namespace utils {
inline void left_trim(std::string& str, const char* chars = " \t\n\v\f\r")
{
	if (!str.empty()) {
		std::size_t str_idx = str.find_first_not_of(chars);

		if (str_idx == std::string::npos)
			str.clear();
		else if (str_idx > 0)
			str = str.substr(str_idx, std::string::npos);
	}
}

inline std::vector<std::string> split(std::string const& str)
{
	std::vector<std::string> slipt_string;
	std::istringstream iss(str);
	std::copy(std::istream_iterator<std::string>(iss),
	          std::istream_iterator<std::string>(),
	          std::back_inserter(slipt_string));
	return slipt_string;
}
}; // namespace utils

class dotqc_reader {
public:
	virtual void on_qubit(std::string label) const
	{
		(void) label;
	}

	virtual void on_input(std::string label) const
	{
		(void) label;
	}

	virtual void on_output(std::string label) const
	{
		(void) label;
	}

	virtual void on_gate(gate_kinds kind, std::string qubit_label) const
	{
		(void) kind;
		(void) qubit_label;
	}

	virtual void on_two_qubit_gate(gate_kinds kind,
	                               std::string qubit0_label,
	                               std::string qubit1_label) const
	{
		(void) kind;
		(void) qubit0_label;
		(void) qubit1_label;
	}

	virtual void on_multiple_qubit_gate(
	    gate_kinds kind, std::vector<std::string> const& qubit_labels) const
	{
		(void) kind;
		(void) qubit_labels;
	}

	virtual void on_end() const
	{}
};

inline void dotqc_read(std::string const& path)
{
	fs::path fpath(path);
	if (fpath.extension() != ".qc") {
		std::cerr << "[e] Unreconized file type: " << fpath.extension()
		          << '\n';
	}
	// Load the whole file into a buffer
	std::ifstream input_file(fpath);
	if (!input_file.is_open()) {
		std::cerr << "[e] Couldn't open file: " << fpath.filename()
		          << '\n';
		return;
	}
	std::stringstream buffer;
	std::string line;
	buffer << input_file.rdbuf();
	input_file.close();

	while (buffer.peek() == '.' || buffer.peek() == '#') {
		if (buffer.peek() == '#') {
			std::getline(buffer, line);
			continue;
		}
		std::getline(buffer, line, ' ');
		if (line[1] == 'v') {
			std::getline(buffer, line);
			auto qubits = utils::split(line);
			for (auto& label : qubits) {
				std::cout << "Found qubit: " << label << '\n';
			}
		} else if (line[1] == 'i') {
			std::getline(buffer, line);
			auto inputs = utils::split(line);
			for (auto& label : inputs) {
				std::cout << "Found input: " << label << '\n';
			}
		} else if (line[1] == 'o') {
			std::getline(buffer, line);
			auto outputs = utils::split(line);
			for (auto& label : outputs) {
				std::cout << "Found output: " << label << '\n';
			}
		}
	}

	while (std::getline(buffer, line)) {
		utils::left_trim(line);
		if (line.empty()) {
			continue;
		}
		auto entries = utils::split(line);
		auto gate = entries[0];
		entries.erase(entries.begin());
		switch (entries.size()) {
		case 0:
			/* Hopefully was either BEGIN or END */
			break;

		case 1:
			std::cout << "Found single qubit gate: " << gate << '\n';
			break;

		case 2:
			std::cout << "Found two qubit gate: " << gate << '\n';
			break;

		default:
			std::cout << "Found multiple qubit gate: " << gate << '\n';
			break;
		}
	}
}

} // namespace tweedledee
