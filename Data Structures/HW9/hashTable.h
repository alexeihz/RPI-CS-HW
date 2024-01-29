#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;


class hashtable{
	public:
	HashTable();
	HashTable(string genome, int table_size, float occupancy, int kmer);
	void query(string query_string, int mismatch);
	
	
	
	
	private:
	vector <pair<string,int> > hashes;
	string genome;
	int table_size, kmer;
	float occupancy;
}