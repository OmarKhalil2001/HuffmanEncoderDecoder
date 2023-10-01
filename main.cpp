#include <bits/stdc++.h>
using namespace std;

class bin_node{
    public:
        int asci = 0;
        bin_node *left, *right;
    
        bin_node(int asc){
            asci = asc;
            left = nullptr;
            right = nullptr;
        }
};

vector<char> holder;
map<char, int> freq;

void open_read(){
    freopen("Input.txt", "r", stdin);
    char temp;
    while(cin.get(temp)){
        holder.push_back(temp);
        freq[temp]++;
    }
    cin.clear();
}


bin_node* tree_builder(){
    set<pair<int, bin_node*>> p_q;
    for(auto i : freq){
        p_q.insert({i.second, new bin_node((int)i.first)});
    }
    
    if(p_q.size() == 1){
         p_q.insert({0, new bin_node(0)});
    }

    while(p_q.size() > 1){
        bin_node* temp = new bin_node(0);
        auto x = p_q.begin();
        
        int freq = x->first;
        temp->left = x->second;
        
        x++;
        
        freq += x->first;
        temp ->right = x->second;
        
        p_q.erase(p_q.begin());
        p_q.erase(p_q.begin());

        p_q.insert({freq, temp});
    }
    return p_q.begin()->second;
}

bool huff_encode(int ch, bin_node *root, string &temp){
    if(root == nullptr) return false;
    if(root->asci == ch){
        return true;
    }else if(huff_encode(ch, root->left, temp)){
        temp.push_back('0');
        return true;
    }else if(huff_encode(ch, root->right, temp)){
        temp.push_back('1');
        return true;
    }

    return false;
}

void huffman_decode(bin_node* root, string &s){
		
		bin_node* node = root;
		for (int i = 0; i < s.length(); i++){
			if (s[i] == '0'){
				node = node->left;	
            }else{
				node = node->right;	
            }
            if(node->asci != 0){
				cout << (char)node->asci;
			    node = root;
            }
		}
	}

int main(){
    open_read();
    bin_node *root = tree_builder();
    freopen("ENCODED.txt", "w", stdout);
    for(auto i : holder){
        string temp = "";
        huff_encode((int) i, root, temp);
        reverse(temp.begin(), temp.end());
        cout << temp;
    }
    cout.clear();

    freopen("ENCODED.txt", "r", stdin);
	string s = "";
	
	cin >> s;
    cin.clear();

    freopen("DECODED.txt", "w", stdout);
    huffman_decode(root, s);
    cout.clear();


    return 0;
}