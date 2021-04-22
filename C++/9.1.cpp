#include <iostream>
#include <vector> 
#include <string>

using std::cout; 
using std::cin; 
using std::string; 
using std::vector; 

bool delimiter_check(const char symbol) {
	if (symbol == ' ' || symbol == '.' || symbol == ',' || symbol == ':' || symbol == ';' 
   || symbol == '!' || symbol == '?' || symbol == '\"' || symbol == '(' || symbol == ')' || symbol == '\0') return 1;
	return 0;
}

vector<string> only_words (const string& sentence) {
	vector<string> only_word;  
	for (int i = 0; i < sentence.size(); i++) { 
		if (delimiter_check(sentence[i])) continue;
		else {
			string help;
			while (!delimiter_check(sentence[i])) {
				help += sentence[i];
				i++;
			}
			only_word.push_back(help); 
		}
	}
	return only_word;
}

vector<string> common_words(const string& sentence) {
	vector<string> only_word = only_words(sentence); 
	vector<string> result; 
	string help_1;
	string help_2; 
	int high_reps = 0; 
	for(int i = 0; i < only_word.size(); i ++) {
		help_2 = only_word[i]; 
		int repeat_word = 0; 
		for(int j = 0; j < only_word.size(); j ++) {
			help_1 = only_word[j];
			if(help_1 == help_2) repeat_word++; 
		}
		if(repeat_word > high_reps) {
			result.clear(); 
			result.push_back(help_2); 
			high_reps = repeat_word; 
		}
		else {
			if(repeat_word == high_reps) {
				bool repeat_result = true;
				for(int k = 0; k < result.size(); k++) {
					help_1 = result[k]; 
					if(help_1 == help_2) {
						repeat_result = false; 
						break;
					}
				}
				if(repeat_result) {
					result.push_back(help_2);  
				}
			}
		}
	}
	result.pop_back();
	return result;
}

int main() {
   string sentence = "Hello, my friend. my friend love chokolate. I stydy in BSU with my friend."; 
	vector<string> result = common_words(sentence); 
	for(int i = 0; i < result.size(); i++){
		cout << result[i]; 
	} 

}