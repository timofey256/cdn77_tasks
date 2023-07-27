#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <bits/stdc++.h>

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
		
		root->is_word_end = false;
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
	
	dns_record resolve_ip(std::string hex_ip) {
		dns_record best_fit;

		std::string ip = ip_to_binary_str(hex_ip);

		Node* cur = root;
		int bit_idx = 0;
		while (cur != NULL) {
			if (cur->is_word_end == true) {
				best_fit.first = cur->address;
				best_fit.second = cur->pop_id;
			}
			
			int bit = (int)(ip[bit_idx] - '0');
			bit_idx += 1;
			cur = cur->children[bit];
		}

		return best_fit;
	}

private:
	Node* root;
	
	std::string ip_to_binary_str(std::string ip) {
		std::string binary = "";

		for (int i=0; i < ip.length(); i++) {
			if (ip[i] == ':') {
				continue;
			}
			else if (ip[i] == '/') {
				break;
			}
			else {
				binary += hex_char_to_bin(ip[i]);
			}
		}
		
		return binary;
	}

	Node* get_node(bool bit) {
		Node* node = new Node;
		node->bit = bit;
		node->children[0] = NULL;
		node->children[1] = NULL;
		
		return node;
	}
	
	// i tried to use some libs to make it in a less uglier way but it seems like the most simple way to convert :-/
	std::string hex_char_to_bin(char c) {
	    switch(c) {
		case '0': return "0000";
		case '1': return "0001";
		case '2': return "0010";
		case '3': return "0011";
		case '4': return "0100";
		case '5': return "0101";
		case '6': return "0110";
		case '7': return "0111";
		case '8': return "1000";
		case '9': return "1001";
		case 'a': return "1010";
		case 'b': return "1011";
		case 'c': return "1100";
		case 'd': return "1101";
		case 'e': return "1110";
		case 'f': return "1111";
	    }
	}
};

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
	DNSRecordsTrie trie;	
	for (dns_record rec : records) {
		trie.insert(rec);
	}
	
	std::string ip = "2001:49f0:d0b8:8a00::/56";
	dns_record rec = trie.resolve_ip(ip);
	std::cout << rec.first << std::endl;
	
	return 0;
}
