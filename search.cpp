// Do NOT add any other includes
#include "search.h"

SearchEngine::SearchEngine(){
    baseSize = 0;
}

SearchEngine::~SearchEngine(){
    for(int i = 0;i<info.size();i++){
        delete info[i];
    }
}

void tolower(string &a){
    
    for(int i= 0;i<a.size();i++){
        a[i] = tolower(a[i]);
    }
    
}

void SearchEngine::insert_sentence(int book_code, int page, int paragraph, int sentence_no, string sentence){
    Node* in = new Node(book_code,page,paragraph,sentence_no,0);
    tolower(sentence);
    base.push_back(sentence);
    info.push_back(in);
    baseSize++;
}

void insert(Node* &head,Node* &tail, Node* in){
    if(head == nullptr){
        head = in;
        tail = in;
    }
    else{
        
        tail -> right = in;
        in -> left = tail;
        tail = in;
    }
}

int kaha(string &pat,int &m,int &abhi,int &x){
    if(abhi<m ){
        if(pat[abhi] == x)
        return abhi+1;
    }
    int i;
    for(int agla = abhi;agla > 0;agla--){
        bool flag = false;
        if(pat[agla - 1] == x){
            for(i = 0;i<agla - 1;i++)
                if(pat[i] != pat[abhi-agla + 1 + i]){
                    flag = true;
                    break;
                }
                    
            if(!flag)
                return agla;
        }
    }
    return 0;
}

void transition(string &pat,int m,int table[][128]){

    int abhi,x;
    for(abhi= 0;abhi<=m;abhi++){
        for(x = 0;x<128;x++){
            table[abhi][x] = kaha(pat,m,abhi,x);
        }
    }

}



Node* SearchEngine::search(string pattern, int& n_matches){
    Node* head = nullptr;
    Node* tail = nullptr;
    tolower(pattern);
    int kitna = pattern.size();

    int table[kitna+1][128];
    
    transition(pattern,kitna,table);
    
    for(int i = 0;i<base.size();i++){
        vector<int> offset;
        string a = base[i];

        int j, abhi= 0;
        int n = a.size();
        Node* an = info[i];
        for (j = 0; j < n; j++)
        {
            abhi= table[abhi][a[j]];
            if (abhi== kitna)
            {
                offset.push_back(j-kitna+1);
                
            }
        }
        for(int i = 0;i<offset.size();i++){
            Node* temp = new Node(an->book_code,an->page,an->paragraph,an->sentence_no,offset[i]);
            temp -> left = NULL;
            temp -> right = NULL;
            insert(head,tail,temp);
            n_matches++;
        }

    }
    return head;
}

// int main(){
//     string a = "Cute";    
//     string b = "Namste My cute iabhigreat";
    
//     SearchEngine* abhi= new SearchEngine();
//     abhi-> insert_sentence(0,0,0,1,a);

//     int c = 0;
//     cout<<"inserted"<<endl;
//     Node* an = abhi-> search("cute",c);
    
//     // cout<<"hi"<<" "<<c<<endl;
//     // c = 0;
//     // abhi-> insert_sentence(0,0,0,2,b);
    

    
    
//     // Node* bn = abhi-> search("cute",c);
//     // cout<<"hki"<<" "<<c<<endl;

//     if(an == NULL){
//         cout<<"nhi mila"<<endl;
//     }
//     // while(an != NULL){
//     //     cout<<an -> offset<<endl;
//     //     an = an -> right;
//     // }
//     // while(bn != NULL){
//     //     cout<<bn -> offset<<endl;
//     //     bn = bn -> right;
//     // }

//     // cout<<c<<endl;
// }