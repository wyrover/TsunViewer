#pragma once

#include <rapidjson/document.h>

#include <string>

class Media {
public:
	Media() {}
	Media(const rapidjson::Value::ConstValueIterator&);

	const std::string& getPath() const { return path; }
	int getWidth() const { return width; }
	int getHeight() const { return height; }
	
	void load();

private:
	bool loaded = false;

	std::string url;
	std::string path;
	
	int width = 0;
	int height = 0;
};
