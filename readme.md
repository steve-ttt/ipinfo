# ipinfo

A simple C++ program that retrieves and parses IP information from ipinfo.io using Boost.Asio and RapidJSON.

## Dependencies

- Boost.Asio (for networking)
- RapidJSON (for JSON parsing) included in this package
   (https://github.com/Tencent/rapidjson?tab=License-1-ov-file#readme)

## Building

1. Make sure you have Boost installed on your system.
   1. Debian based systems can install with: sudo apt-get install libboost-all-dev
   2. Red Hat / Fedora systems: dnf install boost.x86_64 
2. Compile the code using the provided Makefile:
   ```bash
   make 
   ```
3. Install with:
    ```bash
    make install
    ```
## Running
Simply run the compiled executable:
```
./ipinfo
```
## Output
The program will print the following IP information retrieved from ipinfo.io:

_____________________________________

ip = [your_ip_address]
city = [your_city]
region = [your_region]
country = [your_country]
Org = [your_serviceProvider]
loc = [your_latitude],[your_longitude]
timezone = [your_timezone]
_____________________________________

## Explanation
Networking (Boost.Asio):

The pullData() function uses Boost.Asio to establish a TCP connection to ipinfo.io on port 80.
It sends an HTTP GET request to retrieve the IP information in JSON format.
The response from the server is read into a boost::asio::streambuf.
JSON Parsing (RapidJSON):

The JSON data is extracted from the streambuf and stored in a std::string.
RapidJSON is used to parse the JSON string into a rapidjson::Document object.
The program then accesses and prints specific fields from the JSON document, such as "ip", "city", "region", etc.
Notes
You might need to adjust the compiler flags and library linking options based on your system configuration.
The program assumes that ipinfo.io is accessible and returns a valid JSON response.
Error handling is minimal in this example. You can add more robust error checking and handling if needed.
