#pragma once

#include <rapidjson/document.h>

#include <iterator>
#include <random>
#include <string>

std::string readFile(const std::string&);
void writeFile(const std::string&, const std::string&);
bool fileExists(const std::string&);

template<typename F>
void iterateJsonArray(const rapidjson::Value& arr, F&& lambda)
{	
	for (
		rapidjson::Value::ConstValueIterator iter = arr.Begin(); 
		iter != arr.End(); 
		iter++
	) {
		if (lambda(iter)) {
			break;
		}
	}
}

// via https://gist.github.com/cbsmith/5538174
template <typename RandomGenerator = std::default_random_engine>
struct random_selector
{
	// On most platforms, you probably want to use std::random_device("/dev/urandom")()
	random_selector(RandomGenerator g = RandomGenerator(std::random_device()())) : gen(g) {}
 
	template <typename Iter>
	Iter select(Iter start, Iter end) 
	{
		std::uniform_int_distribution<> dis(0, std::distance(start, end) - 1);
		std::advance(start, dis(gen));
		return start;
	}
 
	// Convenience function
	template <typename Iter>
	Iter operator()(Iter start, Iter end) 
	{
		return select(start, end);
	}
 
	// Convenience function that works on anything with a sensible begin() and end(), 
	//	and returns with a ref to the value type
	template <typename Container>
	auto operator()(const Container& c) -> decltype(*begin(c))& 
	{
		return *select(begin(c), end(c));
	}
 
private:
	RandomGenerator gen;
};
