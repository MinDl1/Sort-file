//Made by MinDl
//
//8.2.2022
//

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main(){
	ifstream file_in("file.txt");
	if (!file_in.is_open()) {
		cout << "Error: File can't open";
		return 0;
	}
	vector<string> text;
	vector<string> lastname_firstname;
	string buff;

	cout << "Unsorted table: \n";
	while (getline(file_in, buff)) {
		text.push_back(buff);
	}
	file_in.close();

	for (int i = 0; i < text.size(); i++) {
		cout << text[i] << endl;
		text[i].replace(0, 1, " ");
	}
	//sort(text.begin(),text.end()); // u can use this
	//text.erase(unique(text.begin(),text.end()),text.end()); //and don't use loop further
	for (int i = 0; i < text.size(); i++) {
		for (int j = i+1; j < text.size(); j++) {
			if (text[i]==text[j]) {
				text.erase(text.begin()+i);
			}
		}
	}

	for (int j = 0; j < text.size(); j++){
		string str = text[j];

		string firstname = str;
		for (int i = 0, begin_ = 0, end_ = 0, spaces = 0; i < firstname.size(); i++) {
			if (firstname[i] == ' ' && spaces == 0) {
				begin_ = i + 1;
				spaces++;
			}
			else if (firstname[i] == ' ' && spaces == 1) {
				end_ = i;
				firstname = firstname.substr(begin_, end_ - begin_);
				break;
			}
		}

		string lastname = str;
		for (int i = 0, begin_ = 0, end_ = 0, spaces = 0; i < lastname.size(); i++) {
			if (lastname[i] == ' ') {
				spaces++;
			}
			if (spaces == 2 && begin_ == 0) {
				begin_ = i + 1;
			}
			else if (spaces == 3 && end_ == 0) {
				end_ = i;
				lastname = lastname.substr(begin_, end_ - begin_);
				break;
			}
		}

		lastname_firstname.push_back(lastname + ' ' + firstname);
		text[j] = lastname_firstname[j] + " " + text[j];
	}
	lastname_firstname.clear();
	sort(text.begin(), text.end());

	for (int i = 0; i < text.size(); i++) {
		for (int j = 0, spaces = 0; j < text[i].size(); j++) {
			if (text[i][j] == ' ') {
				spaces++;
			}
			if (spaces == 2) {
				text[i].replace(0,j+2,to_string(i+1));
				break;
			}
		}
	}
	cout << "\nSorted table: \n";

	ofstream file_out("file.txt", ios_base::out | ios_base::trunc);

	for (string it : text) {
		cout << it << endl;
		file_out << it << endl;
	}
	file_out.close();
	text.clear();
}
