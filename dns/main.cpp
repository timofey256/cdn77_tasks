#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using dns_record = std::pair<std::string, int>;

// returns a root of the trie
void construct_trie(std::vector<std::string> addresses) {

}

std::vector<dns_record> parse_addresses(std::string path) {
	std::vector<dns_record> addresses;

	std::ifstream file(path);
	std::string str;
	
    	std::string delimiter = " ";	
	while (std::getline(file, str)) {
		
		int delimiter_pos = str.find(delimiter);
		std::string ip = str.substr(0, delimiter_pos);	
	   	int pop_id = std::stoi(str.substr(delimiter_pos, str.length()-delimiter_pos));
		
		dns_record rec;
		rec.first = ip;
		rec.second = pop_id;

		addresses.push_back(rec);
	}

	return addresses;
}

int main() {
	const std::string file_name = "./routing-data-short.txt";
	std::vector<dns_record> records = parse_addresses(file_name);

	for (dns_record rec : records) {
		std::cout << rec.first << " " << rec.second << std::endl;
	}

	return 0;
}
