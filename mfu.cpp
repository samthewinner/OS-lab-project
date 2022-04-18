#include <bits/stdc++.h>

using namespace std;

class mfuCache{
    public:

    class node{
        public:
        node * next;
        node * prev;
        int val;
        int freq;
        node(int v,int f){
            val=v;
            freq=f;
            next=prev=NULL;
        }
    };

    node * head = new node(-1,-1);
    node * tail = new node(-1,-1);
    
    int capacity;    
    vector <int> ref_string;
    int n,curr_size=0;
    int page_hit,page_miss;

    mfuCache(vector<int> v,int cap){ 
        page_hit = page_miss=0;                 
        head->next = tail;
        tail->prev = head;
        ref_string= v;      
        capacity = cap;
        n=ref_string.size();
    }

    
    unordered_map<int, node*> m;

    void createAtEnd(int val){
        node * temp = new node(val,1);
        m.emplace(val, temp);
        temp->next = tail;        
        tail->prev->next =temp;
        temp->prev = tail->prev;
        tail->prev = temp;
        
    }

    void createAtBegining(int val){
        node * temp = new node(val,1);
        m.emplace(val, temp);
        head->next->prev = temp;
        temp->next = head->next;
        temp->prev=head;
        head->next = temp;
        
    }

   
    void implementation(){        
        for(int i=0;i<n;i++){            
            
            if(curr_size < capacity){
                
                if(!m.empty() && m.count(ref_string[i]) == 1){ // element is present and cache is not empty
                    page_hit++;                  
                    cout<<"page hit"<<endl;  
                     node * temp = m[ref_string[i]];                                                          
                    int curr_freq = temp->freq ;
                    curr_freq++;                    
                    int curr_val = temp->val;

                    m.erase(curr_val);
                    temp->prev ->next = temp->next;
                    temp->next ->prev = temp->prev;
                    delete temp;

                    
                    node * curr = head->next;
                    while(1){
                        if(curr->freq < curr_freq){
                            node * n = new node(curr_val,curr_freq);
                            m.emplace(curr_val,n);
                            curr->prev->next = n;
                            n->prev = curr->prev;
                            n->next=curr;
                            curr->prev = n;
                            break;
                        }
                        curr = curr ->next;
                    }                    
                    
                }

                
                else{                               //element is not present
                   createAtEnd (ref_string[i]);
                   page_miss++;
                   cout<<"Page miss: "<<endl;
                    curr_size++;
                }
            }
            else{
                
                if(m.count(ref_string[i]) == 1){ //cache is full and element is presenet 
                    page_hit++;
                    cout<<"Page hit"<<endl;
                     node * temp = m[ref_string[i]]; 
                                                       
                    int curr_freq = temp->freq ;
                    
                    curr_freq++;
                    
                    int curr_val = temp->val;
                    
                    m.erase(curr_val);
                    temp->prev ->next = temp->next;
                    temp->next ->prev = temp->prev;
                    delete temp;
                    
                    
                    node * curr = head->next;
                    while(1){
                        if(curr->freq < curr_freq){
                            node * n = new node(curr_val,curr_freq);
                            m.emplace(curr_val,n);
                            curr->prev->next = n;
                            n->prev = curr->prev;
                            n->next=curr;
                            curr->prev = n;
                            break;
                        }
                        curr = curr ->next;
                    }    
                }

                
                else{       //cache is full and element is not present

                    page_miss++;
                    cout<<"page miss: "<<endl;
                    
                    head->next->next->prev = head;
                    head->next = head->next->next;

                    createAtEnd(ref_string[i]); 

                }
            }
            cout<<"Cache after "<<i+1<<" th operation"<<endl;
        cout<<"[";
        node * temp = head->next;
        while(temp->freq!=-1){
            cout<<" { "<<temp->val<<"  "<<temp->freq<<" } ";            
            temp=temp->next;
        }
        cout<<"]"<<endl<<endl;
        }
    }   

};

int main(){
    int s,n;
    
    cout<<"Enter cache size: ";cin>>s;
    cout<<"Enter string size: ";cin>>n;
    vector <int> v(n);
    cout<<"Enter reference string:(space seperated)"<<endl;
    for(int i=0;i<n;i++){        
        cin>>v[i];                
    }    
    
    mfuCache * o = new mfuCache(v,s);
    o->implementation();
}
