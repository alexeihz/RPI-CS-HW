#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

//hash function from lab
unsigned int myhash ( std::string const& key ) {
    //  This implementation comes from 
    //  http://www.partow.net/programming/hashfunctions/
    unsigned int hash = 1315423911;
    for(unsigned int i = 0; i < key.length(); i++)
      hash ^= ((hash << 5) + key[i] + (hash >> 2));
    return hash;
	
  } 


int main(){
	//initialize variables
	string str,file, gene,dna;
	int size =100, kmer, error;
	float occupy = 0.5;
	vector <pair<string,int> > query;
	//read in values
	while (cin >> str){
		if(str=="quit"){
			break;
		}
		if(str == "genome"){
			cin >> file;
			ifstream infile(file.c_str());
			string temp;
			while(infile >> temp){
				dna = dna + temp;
				
			}
		}
		if(str=="table_size"){
			cin >> size;
		}
		if(str == "occupancy"){
			cin >> occupy;
		}
		if(str == "kmer"){
			cin >> kmer;
		}
		if(str == "query"){

			cin >> error;
			cin >> gene;
			vector <pair<int,int> > query_temp;
			
			
			
			string kmer_gene;
			//doubles size if needed
			for(unsigned int i = 0; i<dna.length() - kmer; ++i){
				if(i/size > occupy){
					size = size * 2;
				}
			}
			vector<int> temp1;
			//creates hashtable and resizes it to proper size
			vector <pair<string, vector<int> > > hashtable(size,pair <string,vector<int> > ("-1",temp1));
			hashtable.resize(size);
			
			//populates hashed locations in the hashtable with the dna string and location
			for(unsigned int loc = 0; loc<dna.length() - kmer; ++loc){
				vector<int> temp; 
				string temp_str;
				for(int j = 0; j < kmer; ++j){
					temp_str += dna[loc + j];
					
				}
				
				long long int hashed_dna = myhash(temp_str);
				int hashloc = hashed_dna % size;
				hashtable[hashloc].first = temp_str;
				hashtable[hashloc].second.push_back(loc);
			}
			for(int i = 0; i<kmer; ++i){
				kmer_gene += gene[i];
			}
			long long hashed_kmer_gene = myhash(kmer_gene);
			int hashloc2 = hashed_kmer_gene % size;
			cout << "Query: " << gene << endl;
			//if a place holder value is found, no match
			if(hashtable[hashloc2].first == "-1"){
				cout<<"No Match"<<endl;
			}
			else{
				//goes through the vector of ints and checks each time a matching kmer dna string was found to make sure it doesn't go over the allowed number of errors
				vector <pair<int, pair<int,string> > > matchSuccess;
				for(unsigned int i = 0; i<hashtable[hashloc2].second.size(); ++i){
					bool matchfail = false;
					string gene_match = hashtable[hashloc2].first;
					string dna_match = hashtable[hashloc2].first;
					int mismatch = 0;
					
					for(unsigned int j = kmer; j<gene.length(); ++j){
						if(gene[j] == dna[hashtable[hashloc2].second[i] + j]){
							gene_match += gene[j];
							dna_match += dna[hashtable[hashloc2].second[i] + j];
						}
						else{
							mismatch++;
							if(mismatch > error){
								matchfail = true;
								break;
								
							}
							gene_match += gene[j];
							dna_match += dna[hashtable[hashloc2].second[i] + j];
						}
						
					}
					if(matchfail==false){
						pair<int, string> tempPair1 = pair<int, string>(mismatch,dna_match);
						pair<int, pair<int, string> > tempPair2 = pair<int, pair<int, string> >(hashtable[hashloc2].second[i],tempPair1);
						matchSuccess.push_back(tempPair2);
					}
				}
				if(matchSuccess.size()<=0){
					cout<<"No Match"<<endl;
				}
				else{
					for(unsigned int i = 0; i<matchSuccess.size(); ++i){
						cout << matchSuccess[i].first << " " << matchSuccess[i].second.first << " " << matchSuccess[i].second.second << endl;
					}
				}
			}
		}
	}
}













