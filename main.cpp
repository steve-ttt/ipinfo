#include <boost/asio.hpp>
#include <iostream>
#include "ipinfo.hpp"
#include "rapidjson/document.h"

using namespace std;

int main() {

    std::string result = pullData();
    std::string json; 

    size_t start = result.find('{'); // Find the start of JSON
    size_t end = result.rfind('}');   // Find the end of JSON

    if (start != std::string::npos && end != std::string::npos) {
        json = result.substr(start, end - start + 1); // Extract JSON
        //printf("json data: %s\n", json.c_str());
    } else {
        printf("Failed to find valid JSON\n");
        return 1;
    }

    //printf("json data: %s\n", json.c_str());
    rapidjson::Document document;
    document.Parse(json.c_str());

    if (document.HasParseError()) {
        printf("Failed to parse JSON\n");
        return 1; 
    }

    printOutput(document);



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
        boost::asio::read_until(socket, response, "}");

        // Extract the data from the streambuf,and store it in a string
        std::istream response_stream(&response);
        std::string response_string((std::istreambuf_iterator<char>(response_stream)), std::istreambuf_iterator<char>());

        // Print the response
        // cout << &response;
        return response_string;

    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return response_string;
}


void printOutput(rapidjson::Document &document){

    cout << "_____________________________________" << endl; 
    if (document.HasMember("ip") && document["ip"].IsString()) {
        cout << "IP = " << document["ip"].GetString() << endl;
    }
    if (document.HasMember("city") && document["city"].IsString()) {
        cout << "City = " << document["city"].GetString() << endl;
    }
    if (document.HasMember("region") && document["region"].IsString()) {
        cout << "Region = " << document["region"].GetString() << endl;
    }
    if (document.HasMember("country") && document["country"].IsString()) {
        cout << "Country = " << document["country"].GetString() << endl;    
    }
    if (document.HasMember("org") && document["org"].IsString()) {
        cout << "Org = " << document["org"].GetString() << endl;
    }
    if (document.HasMember("loc") && document["loc"].IsString()) {
        cout << "Location = " << document["loc"].GetString() << endl;   
    }
    if (document.HasMember("timezone") && document["timezone"].IsString()) {
        cout << "Timezone = " << document["timezone"].GetString() << endl;
    }
    cout << "_____________________________________" << endl;


}
