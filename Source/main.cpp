#include "common.hpp"
#include "Media.hpp"
#include "Post.hpp"
#include "render.hpp"

#include <restclient-cpp/restclient.h>

#include <rapidjson/document.h>

#include <iostream>
#include <string>
#include <vector>

std::string readConfig()
{
	rapidjson::Document config;
	config.Parse(readFile("config.json").c_str());
	
	std::string server = config["server"].GetString();
	std::string query = config["query"].GetString();
	return "http://" + server + "/api/query/?search=" + query;	
}

int main()
{
	std::string url = readConfig();

	RestClient::response queryReq = RestClient::get(url);
	
	rapidjson::Document doc;
	doc.Parse(queryReq.body.c_str());
	
	std::vector<Post> posts;
	
	iterateJSONArray(doc, 
		[&](const rapidjson::Value::ConstValueIterator& iter)
		{
			posts.push_back(Post(iter));
		}
	);
	
	for (auto& post : posts) {
		std::cout << post.getTitle() << std::endl;
		post.iterateMedia(
			[&](Media& medium)
			{
				std::cout << '\t' << medium.getPath() << std::endl;
				medium.load();
				render(
					post.getTitle(), 
					medium.getWidth(),
					medium.getHeight(),
					medium.getPath()
				);
			}
		);
	}
	
	return 0;
}
