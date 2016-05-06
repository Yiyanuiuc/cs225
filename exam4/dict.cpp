#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

bool isomorphicStrings(string s1, string s2)
{
    // Your Code Here
	if (s1.size()!=s2.size()) return false;
	map<char, char> map;
	for (size_t i=0; i<s1.size(); i++) {
		auto lookup = map.find(s1[i]);
		if (lookup==map.end()) map[s1[i]] = s2[i];
		else {
			if (map[s1[i]]!=s2[i]) return false;	
		}
	}
	return true;
}
