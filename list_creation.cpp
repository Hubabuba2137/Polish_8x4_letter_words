#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <map>

#define WORDLEN 4

using namespace std;

size_t count_utf8_chars(const std::string& str) {
    size_t count = 0;
    for (size_t i = 0; i < str.size(); ) {
        unsigned char c = static_cast<unsigned char>(str[i]);
        if ((c & 0x80) == 0) {
            i += 1; // 1 bajtowy znak
        } else if ((c & 0xE0) == 0xC0) {
            i += 2; // 2 bajtowy znak
        } else if ((c & 0xF0) == 0xE0) {
            i += 3; // 3 bajtowy znak
        } else if ((c & 0xF8) == 0xF0) {
            i += 4; // 4 bajtowy znak
        } else {
            // Nieprawidłowy znak UTF-8
            ++i;
        }
        ++count;
    }
    return count;
}

map<char, int> buildCharHistogram(const string& str) {
    map<char, int> histogram;
    for (char c : str) {
        ++histogram[c];
    }
    return histogram;
}

fstream open(string nazwa){
    fstream plik;
    plik.open(nazwa, ios::in);

    if( plik.good() == true ){
        //cout << "Uzyskano dostep do pliku!" << endl;
    } 
    
    else cout << "Dostep do pliku zostal zabroniony!" << endl;

    return plik;
}

int main(){

    fstream plik = open("slowa.txt");
    ofstream endlist("lista_slow.txt");

    if (!endlist) {
        std::cerr << "Nie można otworzyć pliku do zapisu!" << std::endl;
        return 1;
    }

    string line;
    auto begin = std::chrono::high_resolution_clock::now();

    vector <string> lista_slow;

    while(getline(plik, line)){
        if(count_utf8_chars(line) == WORDLEN){
            lista_slow.push_back(line);
        }
    }

    cout<<"Przepisano słowa o długości "<< WORDLEN << " znaków"<<endl;

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
    cout<<"Czas przepisywania "<< elapsed.count()<<"µs"<<endl;

    auto begin_2 = std::chrono::high_resolution_clock::now();

    auto it = lista_slow.begin();
    while (it != lista_slow.end()) {
        std::map<char, int> histogram = buildCharHistogram(*it);
        bool hasDuplicate = false;

        for (const auto& entry : histogram) {
            if (entry.second > 1) {
                hasDuplicate = true;
                break;
            }
        }
        
        if (hasDuplicate) {
            it = lista_slow.erase(it); 
        }
        
        else {
            ++it; 
        }
    }

    auto end_2 = std::chrono::high_resolution_clock::now();
    auto elapsed_2 = std::chrono::duration_cast<std::chrono::microseconds>(end_2 - begin_2);

    cout<<"Czas usuwania powtórzonych liter "<< elapsed_2.count()<<"µs"<<endl;

    auto begin_3 = std::chrono::high_resolution_clock::now();

    for(size_t i = 0; i < lista_slow.size();i++){
        endlist << lista_slow[i]<<endl;
    }

    endlist.close();

    auto end_3 = std::chrono::high_resolution_clock::now();
    auto elapsed_3 = std::chrono::duration_cast<std::chrono::microseconds>(end_3 - begin_3);

    cout<<"Czas zapisywania listy "<< elapsed_3.count()<<"µs"<<endl;
    cout<<"Czas całkowity "<< elapsed_3.count() + elapsed_2.count()+elapsed.count()<<"µs"<<endl;

    return 0;
}