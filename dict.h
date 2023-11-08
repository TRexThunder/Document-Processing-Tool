// Do NOT add any other includes
#include <string> 
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

class Dict {
private:
    // You can add attributes/helper functions here
    string word;
    class TrieNode{
        public:
        TrieNode** children=new TrieNode*[54];
        int count;
        TrieNode() {
            for (int i=0; i<54; i++){
                children[i]=NULL;
            }
            count=0;
        }

        ~TrieNode(){
            count=0;
            delete[] children;
        }
    };

    class Trie{
        public:
        TrieNode* root;
        int cnt;       
        pair<int, char> mp[127];
        Trie(){
            cnt=26;
            for (int i=0; i<=25; i++) mp[i]=make_pair(-1, i+97);
            for (int i=26; i<=29; i++) mp[i]=make_pair(-1, i+9);
            for (int i=30; i<=31; i++) mp[i]=make_pair(-1, i+12);
            for (int i=32; i<=34; i++) mp[i]=make_pair(-1, i+15);
            for (int i=35; i<=38; i++) {
                mp[i]=make_pair(cnt, i+15);
                cnt++;
            }
            for (int i=39; i<=41; i++) mp[i]=make_pair(-1, i+15);
            mp[42]=make_pair(cnt, 57);
            cnt++;
            mp[43]=make_pair(cnt, 60);
            cnt++;
            for (int i=44; i<=45; i++) mp[i]=make_pair(-1, i+17);
            mp[46]=make_pair(-1, 92);
            for (int i=47; i<=49; i++) {
                mp[i]=make_pair(cnt, i+47);
                cnt++;
            }
            for (int i=50; i<=53; i++) {
                mp[i]=make_pair(cnt, i+73);
                cnt++;
            }
            for (int i=54; i<=57; i++) {
                mp[i]=make_pair(cnt, '0');
                cnt++;
            }
            for (int i=58; i<=59; i++) mp[i]=make_pair(-1, '0');
            for (int i=60; i<=62; i++) {
                mp[i]=make_pair(cnt, '0');
                cnt++;
            }
            for (int i=63; i<=64; i++) mp[i]=make_pair(-1, '0');
            for (int i=65; i<=90; i++) mp[i]=make_pair(i-65, '0');
            mp[91]=make_pair(-1, '0');
            mp[92]=make_pair(cnt, '0');
            cnt++;
            mp[93]=make_pair(-1, '0');
            for (int i=94; i<=96; i++) {
                mp[i]=make_pair(cnt, '0');
                cnt++;
            }
            for (int i=97; i<=122; i++) mp[i]=make_pair(i-97, '0');
            for (int i=123; i<=126; i++) {
                mp[i]=make_pair(cnt, '0');
                cnt++;
            }
            root=new TrieNode();
        }

        void insert(string word){
            TrieNode* current=root;
            for (char ch : word){
                int i=mp[(int)(ch)].first;
                if (current->children[i]==NULL) current->children[i]=new TrieNode();
                current=current->children[i];
            }
            current->count++;
        }

        int search(string word){
            TrieNode* current=root;
            for (char ch : word){
                int i=mp[(int)(ch)].first;
                if (current->children[i]==NULL) return 0;
                current=current->children[i];
            }
            return current->count;
        }

        void Destroy(TrieNode* node){
            if (node==NULL) return;
            else {
                for (int i=0; i<54; i++){
                    Destroy(node->children[i]);
                }
                delete node;
            }
        }

        ~Trie(){
           Destroy(root); 
        }
    };

    Trie* store;
    void dump(TrieNode* node, string w, ofstream &outputFile);

public: 
    /* Please do not touch the attributes and 
    functions within the guard lines placed below  */
    /* ------------------------------------------- */
    Dict();

    ~Dict();

    void insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence);

    int get_word_count(string word);

    void dump_dictionary(string filename);

    /* -----------------------------------------*/
};