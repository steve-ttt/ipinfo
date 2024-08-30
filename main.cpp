#include <boost/asio.hpp>
#include <iostream>
#include "ipinfo.hpp"
#include "rapidjson/document.h"

int main() {

    std::string result = pullData();
    std::string json; 

    size_t start = result.find('{'); // Find the start of JSON
    size_t end = result.rfind('}');   // Find the end of JSON

    if(start != std::string::npos && end != std::string::npos) {
        json = result.substr(start, end - start + 1); // Extract JSON
        //printf("json data: %s\n", json.c_str());
    } else {
        printf("Failed to find valid JSON\n");
    }

    //printf("json data: %s\n", json.c_str());
    rapidjson::Document document;
    document.Parse(json.c_str());

    printf("_____________________________________\n\n");
    assert(document.HasMember("ip"));
    assert(document["ip"].IsString());
    printf("ip = %s\n", document["ip"].GetString());
    assert(document.HasMember("city"));
    assert(document["city"].IsString());
    printf("City = %s\n", document["city"].GetString());
    assert(document.HasMember("region"));
    assert(document["region"].IsString());
    printf("Region = %s\n", document["region"].GetString());
    assert(document.HasMember("country"));
    assert(document["country"].IsString());
    printf("Country = %s\n", document["country"].GetString());
    assert(document.HasMember("org"));
    assert(document["org"].IsString());
    printf("Org = %s\n", document["org"].GetString());
    assert(document.HasMember("loc"));
    assert(document["loc"].IsString());
    printf("Location = %s\n", document["loc"].GetString());
    assert(document.HasMember("timezone"));
    assert(document["timezone"].IsString());
    printf("Timezone = %s\n", document["timezone"].GetString());
    printf("_____________________________________\n\n");  
    return 0;
}

std::string pullData(){
        std::string response_string = "";
        
        try {
        boost::asio::io_context io_context;
        boost::asio::ip::tcp::resolver resolver(io_context);
        boost::asio::ip::tcp::socket socket(io_context);

        // Resolve the host and port
        auto endpoints = resolver.resolve("ipinfo.io", "80");

        // Connect to the server
        boost::asio::connect(socket, endpoints);

        // Send an HTTP GET request
        std::string request = "GET /json HTTP/1.1\r\nHost: ipinfo.io\r\n\r\n";
        boost::asio::write(socket, boost::asio::buffer(request));

        // Read the response
        boost::asio::streambuf response;
        //boost::asio::read_until(socket, response, "\r\n\r\n");
        boost::asio::read_until(socket, response, "}");

        // Extract the data from the streambuf,and store it in a string
        std::istream response_stream(&response);
        std::string response_string((std::istreambuf_iterator<char>(response_stream)), std::istreambuf_iterator<char>());

        // Print the response using printf
        //printf("Response\n%s\n\n", response_string.c_str());

        // Print the response
        //std::cout << &response;
        return response_string;

    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return response_string;
}


