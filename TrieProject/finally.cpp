#include <iostream>
#include<vector>
#include <string.h>
#include<fstream>
using namespace std;

#define ALPHABET_SIZE 26
#define false 0
#define true 1
#define MAX_WORD_SIZE   50
#define MAX_MEANING_SIZE 1000
#define underlineOn "\033[31m"
#define underlineOff "\033[0m"

int letterToInt(char letter)
{
    if (letter >= 'A' && letter <= 'Z')
    {
        return letter - 'A';
    }

    else if (letter >= 'a' && letter <= 'z')
    {
        return letter - 'a';
    }

    return -1;
}

struct trieNode
{
    struct trieNode* children[ALPHABET_SIZE];
    bool isEndOfWord;
    string value;
};

struct trieNode* getNode(void)
{
    struct trieNode *pNode =  new trieNode;

    pNode->isEndOfWord = false;

    for (int i = 0; i < ALPHABET_SIZE; i++)
        pNode->children[i] = NULL;

    return pNode;
}

int insert(struct trieNode *root, string word, string meaning)
{
    struct trieNode *curr = root;

    for (int i = 0; i < word.length(); i++)
    {
        int index = letterToInt(word[i]);

        if (!curr->children[index])
            curr->children[index] = getNode();

        curr = curr->children[index];
    }

    curr->isEndOfWord = true;
    curr->value = meaning;

    return true;
}

void deleteWordsFromFile(const char* filename, string word)
{
    string line;
    ifstream myfile;
    myfile.open(filename);
    ofstream temp;
    temp.open("/Users/saarthak/Desktop/TrieProject/TrieProject/TrieProject/temp.txt");
    while (getline(myfile, line))
    {
    if (line.substr(0, word.size()) != word)
    temp << line << endl;
    }
    myfile.close();
    temp.close();
    remove(filename);
    rename("/Users/saarthak/Desktop/TrieProject/TrieProject/TrieProject/temp.txt", "/Users/saarthak/Desktop/TrieProject/TrieProject/TrieProject/text.txt");
}

void WriteWordsToFile(const char* filename,string x,string y){
    char word[50]; char meaning[100];
    strcpy(word, x.c_str());
    strcpy(meaning, y.c_str());

    FILE *filepointer;
    filepointer = fopen(filename,"a");

    fprintf(filepointer,"\n%s  %s",word,meaning);


    fclose(filepointer);
    return;

}

int readWordsFromFile(struct trieNode *root,const char* filename)
{
    FILE *file = fopen(filename, "r");

    if (!file)
    {
        printf("could not find/open file \"%s\"\n", filename);
        return false;
    }

    char word[MAX_WORD_SIZE];
    char meaning[MAX_MEANING_SIZE];

    int count = 0;

    while (fscanf(file, "%s %[^\n]", word, meaning) > 1)
    {
        if (!insert(root, word, meaning))
        {
            fclose(file);
            return false;
        }

        else
        {
            count++;
        }
    }

    fclose(file);
    cout << "Welcome to our Dictionary. Our Dictionary right now contains " << count << " words.\n";

    return true;
}

bool search(struct trieNode *root, string word)
{
    struct trieNode *curr = root;

    for (int i = 0; i < word.length(); i++)
    {
        int index = letterToInt(word[i]);

        if (!curr->children[index])
            return false;

        curr = curr->children[index];
    }

    if (curr->isEndOfWord)  {
        cout << "The meaning of the word is: \n";
        cout << curr->value;
        return true;
    }
    return false;
}

bool searchNotes(struct trieNode *root, string word)
{
    struct trieNode *curr = root;

    for (int i = 0; i < word.length(); i++)
    {
        int index = letterToInt(word[i]);

        if (!curr->children[index])
            return false;

        curr = curr->children[index];
    }

    if (curr->isEndOfWord) return true;
    return false;
}
string deletedWord = "";
bool deleteWord(struct trieNode *root, string word)
{
    struct trieNode *curr = root;

    for (int i = 0; i < word.length(); i++)
    {
        int index = letterToInt(word[i]);

        if (!curr->children[index])
            return false;

        curr = curr->children[index];
    }
    if (curr->isEndOfWord)  {
        curr->isEndOfWord = false;
        deletedWord = curr->value;
        return true;
    }
    return false;
}

void alphabeticalOrder(struct trieNode* root, char allWords[], int index)
{
    struct trieNode* curr = root;

    if(curr->isEndOfWord == true) {
        for(int j = 0; j < index; j++)  {
            cout << allWords[j];
            }

        cout << ": ";
        cout << curr->value << "\n";
    }

    for(int i = 0; i < ALPHABET_SIZE; i++)  {
        if(curr->children[i] != NULL) {
            allWords[index] = 'a' + i;
            alphabeticalOrder(curr->children[i], allWords, index + 1);
        }
    }
}

void print_prefix_search(struct trieNode* curr, string &word){
    if(curr->isEndOfWord) {
        cout<<word<<": "<<curr->value<<endl;
    }
    for(int i = 0; i < 26; i++){
        if(curr->children[i]){
            word += ('a' + i);
            print_prefix_search(curr->children[i],word);
        }
    }
    word.pop_back();
}

void prefix_search(struct trieNode* root, string prefix)
{
    struct trieNode* curr = root;

    for(int i = 0; i < prefix.length(); i++)    {
        int index = letterToInt(prefix[i]);
        if(curr->children[index]==NULL){
            cout<<"No word present that has "<<prefix<<" as a prefix"<<endl;
            return;
        }
        curr = curr->children[index];
    }
    print_prefix_search(curr,prefix);
}

void print_prefix_search_of_wrong_spelling(struct trieNode* curr, string &word){
    if(curr->isEndOfWord) {
        cout<<word<<endl;
    }
    for(int i = 0; i < 26; i++){
        if(curr->children[i]){
            word += ('a' + i);
            print_prefix_search_of_wrong_spelling(curr->children[i],word);
        }
    }
    word.pop_back();
}

void prefix_search_of_wrong_spelling(struct trieNode* root, string prefix)
{
    struct trieNode* curr = root;

    for(int i = 0; i < prefix.length(); i++){
        int index = letterToInt(prefix[i]);
        if(curr->children[index]==NULL){
            cout<<"No word present that has "<<prefix<<" as a prefix"<<endl;
            return;
        }
        curr = curr->children[index];
    }
    print_prefix_search_of_wrong_spelling(curr,prefix);
}


string spelling_checker(struct trieNode* root, string prefix)
{
    struct trieNode* curr = root;
    string correct_prefix;

    for(int i = 0; i < prefix.length(); i++){
        int index = letterToInt(prefix[i]);
        if(curr->children[index]==NULL){
            cout<<"--------------------- your spelling is incorrect --------------------------"<<endl;
            return correct_prefix;
        }
        correct_prefix += prefix[i];
        curr = curr->children[index];
    }

    if(curr->isEndOfWord == true){
        cout<<"--------------- Congrats !! Your spelling is CORRECT ----------------------------"<<endl;
    }else{
        cout<<"your spelling is incorrect"<<endl;
    }

    return correct_prefix;
}



int main()  {
    struct trieNode *root = getNode();

    readWordsFromFile(root, "/Users/saarthak/Desktop/TrieProject/TrieProject/TrieProject/text.txt");

    string command;
    do  {
        cout << "\nWhat would you like to do?\n";
        cout << "1. Insert a word.\n";
        cout << "2. Search a word.\n";
        cout << "3. Delete a word.\n";
        cout << "4. Print dictionary in alphabetical order.\n";
        cout << "5. Prefix search.\n";
        cout << "6. Use dictonary as a Spelling Checker.\n";
        cout << "\n";
        fflush(stdin);

        int call;
        cin >> call;
        cout << "\n";

        string word;
        string meaning;
        string s = "";
        switch(call)    {

            case 1: cout << "Enter the word you would like to insert: ";
                    cin >> word;
                    cout << "Enter its meaning: ";
                    cin.ignore();
                    getline(cin,meaning);
                    if(insert(root, word, meaning)) {
                        cout << word << " has been added to the Dictionary.\n";
                    }
                    WriteWordsToFile("/Users/saarthak/Desktop/TrieProject/TrieProject/TrieProject/text.txt",word,meaning);

                    break;

            case 2: cout << "Enter the word you would like to search: ";
                    cin >> word;

                    if(!search(root, word))  {
                        cout << "Sorry, the word you searched for doesn't exist. Would you like to add it to the Dictionary.(Yes/No) ";

                        string add;
                        cin >> add;

                        if(add == "yes" || add == "Yes" || command == "YES")  {
                            cout << "Enter its meaning: ";
                            cin.ignore();
                            getline(cin,meaning);
                            if(insert(root, word, meaning)) {
                            cout << word << " has been added to the Dictionary.\n";
                            WriteWordsToFile("/Users/saarthak/Desktop/TrieProject/TrieProject/TrieProject/text.txt",word,meaning);
                            }
                        }
                    }

                    break;

            case 3: cout << "Which word would you like to delete? ";
                    cin >> word;

                    if(deleteWord(root, word))  {
                        cout << word << " has been successfully deleted from the Dictionary.\n";
                        deleteWordsFromFile("/Users/saarthak/Desktop/TrieProject/TrieProject/TrieProject/text.txt",deletedWord);
                        deleteWordsFromFile("/Users/saarthak/Desktop/TrieProject/TrieProject/TrieProject/text.txt",word);
                    }

                    else    {
                        cout << "No such word exists in the Dictionary.\n";
                    }

                    break;

            case 4: char allWords[50];
                    alphabeticalOrder(root, allWords, 0);
                    cout << "\n";

                    break;

            case 5: cout << "Enter the word you would like to use as a prefix: ";
                    cin >> word;
                    cout << "\n";

                    prefix_search(root, word);

                    break;

            case 6:{
                    cout<<"Enter the word whose spelling you would like to check : ";
                    cin >> word;
                    string prefix_of_wrong_spelling = spelling_checker(root,word);
                    cout<<"Enter '1' if you want to find the words which are similar your entered word , otherwise Enter '2' : ";
                    int x; cin>>x;

                    if(x==1) prefix_search_of_wrong_spelling(root,prefix_of_wrong_spelling);
                   }
                   break;

            default: cout << "Enter a valid entry.";
                //You need to clear the input state and then ignore the junk that was invalid.
                     cin.clear();
                     cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    fflush(stdin);
        cout << "\n\nWould you like to continue?(Yes/No) ";
        cin >> command;
    }
    while(command == "yes" || command == "Yes" || command == "YES");

    cout << "Thanks for using our Dictionary.\n";
    return 0;
}
