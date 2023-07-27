#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using dns_record = std::pair<std::string, int>;
const std::string file_name = "./routing-data-short.txt";

struct Node {
	bool bit;
	bool is_word_end;

	// if is_word_end == false, then these properties will be empty
	std::string address;
	int pop_id;

	Node* children[2];
};

class DNSRecordsTrie {
public:
	DNSRecordsTrie() {
		root = new Node;

		root->children[0] = NULL;
		root->children[1] = NULL;
	}

	void insert(dns_record rec) {
		std::string binary_ip = ip_to_binary_str(rec.first);	
		
		Node* cur = root;
		for (int i=0; i < binary_ip.length(); i++) {
			int bit = (int)(binary_ip[i] - '0');
			if (cur->children[bit] == NULL) {
				cur->children[bit] = get_node(bit);
			}

			cur = cur->children[bit];	
		}

		cur->is_word_end = true;
		cur->address = rec.first;
		cur->pop_id = rec.second;
	}	
	
	dns_record resolve_ip(std::string ip) {
		// ...	
	}

private:
	Node* root;
	
	std::string ip_to_binary_str(std::string) {
		// ...
	}

	Node* get_node(bool bit) {
		Node* node = new Node;
		node->bit = bit;
		node->children[0] = NULL;
		node->children[1] = NULL;
		
		return node;
	}
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
	std::vector<dns_record> records = parse_addresses(file_name);

	for (dns_record rec : records) {
		std::cout << rec.first << " " << rec.second << std::endl;
	}

	return 0;
}
