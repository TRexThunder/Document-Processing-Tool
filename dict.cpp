// Do NOT add any other includes
#include "dict.h"

Dict::Dict(){
    // Implement your function here
    store=new Trie();
}

Dict::~Dict(){
    // Implement your function here
    delete store;
}

void Dict::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence){
    // Implement your function here
    word.clear();
    int sz=sentence.size();
    for (int i=0; i<sz; i++){
        char c=sentence[i];
        if (store->mp[(int)c].first==-1){
            if (word.size()!=0) {
                store->insert(word);
                word.clear();
            }
        }
        else if (i==sz-1){
            word.push_back(c);
            store->insert(word);
            word.clear();
        }
        else word.push_back(c);
    }  
    return;
}

int Dict::get_word_count(string word){
    // Implement your function here  
    return store->search(word);
}

void Dict::dump(TrieNode* node, string w, ofstream &outputFile){
    if (node==NULL) return;
    if (node->count>0) outputFile<<w<<", "<<node->count<<endl;
    for (int i=0; i<54; i++){
        dump(node->children[i], w+store->mp[i].second, outputFile);
    }
}

void Dict::dump_dictionary(string filename){
    // Implement your function here
    string file=filename;
    ofstream outputFile;
    string s="";
    outputFile.open(file);
    dump(store->root, s, outputFile);
    outputFile.close();  
    return;
}