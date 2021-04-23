#ifndef H_WIKI_ENTRY_SPIKE
#define H_WIKI_ENTRY_SPIKE
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <locale>

using namespace std;
class wikiEntry {
   private:
    /* data */
   public:
    wikiEntry(string title, string ns, string id);
    wikiEntry(string rawData);
    ~wikiEntry();

    string parseTitle(string rawData);  // Used for returning the title from a raw .dat entry string
    void insertEntry(map<string, wikiEntry> &entries, string rawData);
    string toLower(string str); // Convert string to lowercase
    string title;
    pair<string, string> pairType;

    inline bool operator < (const wikiEntry& rhs) const;
};


string wikiEntry::parseTitle(string rawData) {
    string delimiter = ":";
    stringstream data(rawData);
    string line;
    for(int x = 0; x < 3; x++)  // Traverse to third segment of string (the title)
        getline(data, line, ':');
    return line;                // Return the line from above loop
}

string wikiEntry::toLower(string str)
{
    string temp = str;
    for(auto& c : temp)
    {
    c = tolower(c);
    }

    return temp;

}

void wikiEntry::insertEntry(map<string, wikiEntry> &entries, string rawData) {
    entries.insert(pair<string, wikiEntry>(toLower(parseTitle(rawData)), wikiEntry(rawData)));
}

wikiEntry::wikiEntry(string rawData) {
    string delimiter = ":";
    stringstream data(rawData);
    string line;
    getline(data, line, ':');
    pairType.first = line;
    getline(data, line, ':');
    pairType.second = line;
    getline(data, line, ':');
    this->title = line;
}

wikiEntry::wikiEntry(string title, string ns, string id) {
    pairType.first = ns;
    pairType.second = id;
    this->title = title;
}

wikiEntry::~wikiEntry() {
}

bool wikiEntry::operator<(const wikiEntry &rhs) const {
    return (
            make_pair(stoi(this->pairType.first), stoi(this->pairType.second))
            <
            make_pair(stoi(rhs.pairType.first), stoi(rhs.pairType.second))
    );
}

#endif