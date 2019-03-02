#pragma once
#include <vector>
#include <iostream>
#include <cctype>
#include <string>
#include <numeric>
#include <algorithm>
#include <sstream>
class Splitter {
public:
	Splitter() = default;
	explicit Splitter(std::string prompt)
		: m_prompt(std::move(prompt))
		, m_delimiter(' ')
	{}

	void prompt(std::string prompt);
	friend std::ostream& operator<<(std::ostream& os, const Splitter& splitter);
	std::vector<std::string> split (char delimiter);
	Splitter& to_lower();

private:
	std::string m_prompt;
	char m_delimiter;
	std::vector<std::string> m_result;

};

std::vector<std::string> Splitter::split(char delimiter) {
	m_result.clear();
	std::stringstream ss(m_prompt);
	std::string item;
	while (std::getline(ss, item, delimiter)) {
		m_result.push_back(item);
	}
	
	m_prompt.clear();
	for (const auto& substr : m_result) { m_prompt += substr; }
	return m_result;
}

void Splitter::prompt(std::string prompt) {
	m_prompt = std::move(prompt);
}

Splitter& Splitter::to_lower() {
	for (auto& letter : m_prompt) { letter = tolower(letter); }
	return *this;
}

std::ostream& operator<<(std::ostream& os, const Splitter& splitter)
{
	for (auto& item : splitter.m_result) {
		os << item << " ";
	}
	return os;
}