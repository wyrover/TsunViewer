#include "common.hpp"
#include "render.hpp"

#include <restclient-cpp/restclient.h>

#include <rapidjson/document.h>

#include <iostream>
#include <string>

std::string readConfig()
{
	rapidjson::Document config;
	config.Parse(readFile("config.json").c_str());
	
	std::string server = config["server"].GetString();
	std::string query = config["query"].GetString();
	return "http://" + server + "/api/query/?search=" + query;	
}

std::string saveImage(rapidjson::Document& doc)
{
	RestClient::response imageReq = RestClient::get(
		doc[0u]["media"][0u]["image"]["image"].GetString()
	);
	std::string path = doc[0u]["media"][0u]["image"]["url"].GetString();
	path.erase(0, 11);
	path = "Images/" + path;
	if (!fileExists(path)) {
		writeFile(path, imageReq.body);
	}
	
	return path;
}

int main()
{
	std::string url = readConfig();

	RestClient::response queryReq = RestClient::get(url);
	
	rapidjson::Document doc;
	doc.Parse(queryReq.body.c_str());
	
	std::string path = saveImage(doc);
		
	render(
		doc[0u]["title"].GetString(), 
		doc[0u]["media"][0u]["width"].GetInt(),
		doc[0u]["media"][0u]["height"].GetInt(),
		path
	);
	
	return 0;
}
