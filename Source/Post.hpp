#pragma once

#include "Media.hpp"

#include <rapidjson/document.h>

#include <string>
#include <vector>

class Post {
public:
	Post() {}
	Post(const rapidjson::Value::ConstValueIterator&);
	
	const std::string& getTitle() const { return title; }
	
	template<typename F>
	void iterateMedia(F&& lambda)
	{	
		for (auto& medium : media) {
			lambda(medium);
		}
	}

private:
	std::string title;
	std::vector<Media> media;
};
