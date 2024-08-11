#include <iostream> 
#include <string>
#include <vector>
#include <fstream>
#include <map>
#include <chrono>
#include <unordered_map>
#include <bitset>

#define WORDLEN 4 //ewentualnie do zmiany

std::fstream open(std::string nazwa){
    std::fstream plik;
    plik.open(nazwa, std::ios::in);

    if( plik.good() == true ){
        //cout << "Uzyskano dostep do pliku!" << endl;
    } 
    
    else std::cout << "Dostep do pliku zostal zabroniony!" << std::endl;

    return plik;
}

uint32_t binary_representation(const std::string& word) {
    uint32_t temp = 0b00000000000000000000000000000000;

    for (size_t i = 0; i < word.size(); ++i) {
        
        if ((word[i] & 0xC0) == 0xC0) {
            std::string letter = word.substr(i, 2);
            i++; // Przesuwamy indeks, aby pominąć drugi bajt
            if (letter == "ą") {
                temp |= 0b00000000000000000000000000000010;
            } else if (letter == "ć") {
                temp |= 0b00000000000000000000000000010000;
            } else if (letter == "ę") {
                temp |= 0b00000000000000000000000010000000;
            } else if (letter == "ł") {
                temp |= 0b00000000000000001000000000000000;
            } else if (letter == "ń") {
                temp |= 0b00000000000001000000000000000000;
            } else if (letter == "ó") {
                temp |= 0b00000000000100000000000000000000;
            } else if (letter == "ś") {
                temp |= 0b00000001000000000000000000000000;
            } else if (letter == "ź") {
                temp |= 0b01000000000000000000000000000000;
            } else if (letter == "ż") {
                temp |= 0b10000000000000000000000000000000;
            }
        } else {
            // Zwykłe litery alfabetu łacińskiego (pojedynczy bajt)
            switch (word[i]) {
                case 'a':
                    temp |= 0b00000000000000000000000000000001;
                    break;
                case 'b':
                    temp |= 0b00000000000000000000000000000100;
                    break;
                case 'c':
                    temp |= 0b00000000000000000000000000001000;
                    break;
                case 'd':
                    temp |= 0b00000000000000000000000000100000;
                    break;
                case 'e':
                    temp |= 0b00000000000000000000000001000000;
                    break;
                case 'f':
                    temp |= 0b00000000000000000000000100000000;
                    break;
                case 'g':
                    temp |= 0b00000000000000000000001000000000;
                    break;
                case 'h':
                    temp |= 0b00000000000000000000010000000000;
                    break;
                case 'i':
                    temp |= 0b00000000000000000000100000000000;
                    break;
                case 'j':
                    temp |= 0b00000000000000000001000000000000;
                    break;
                case 'k':
                    temp |= 0b00000000000000000010000000000000;
                    break;
                case 'l':
                    temp |= 0b00000000000000000100000000000000;
                    break;
                case 'm':
                    temp |= 0b00000000000000010000000000000000;
                    break;
                case 'n':
                    temp |= 0b00000000000000100000000000000000;
                    break;
                case 'o':
                    temp |= 0b00000000000010000000000000000000;
                    break;
                case 'p':
                    temp |= 0b00000000001000000000000000000000;
                    break;
                case 'r':
                    temp |= 0b00000000010000000000000000000000;
                    break;
                case 's':
                    temp |= 0b00000000100000000000000000000000;
                    break;
                case 't':
                    temp |= 0b00000010000000000000000000000000;
                    break;
                case 'u':
                    temp |= 0b00000100000000000000000000000000;
                    break;
                case 'w':
                    temp |= 0b00001000000000000000000000000000;
                    break;
                case 'y':
                    temp |= 0b00010000000000000000000000000000;
                    break;
                case 'z':
                    temp |= 0b00100000000000000000000000000000;
                    break;
            }
        }
    }

    return temp;
}

unsigned int hamming_weight(unsigned int x) {  
    return __builtin_popcount(x);  
} 

int main(){
    auto begin = std::chrono::high_resolution_clock::now();

    std::vector<std::string> primary_list;
    std::fstream plik = open("lista_slow.txt");

    std::vector<std::string> word_list;

    uint32_t binary_sum=0b00000000000000000000000000000000;
    uint32_t temp=      0b00000000000000000000000000000000;
    uint32_t temp_sum=  0b00000000000000000000000000000000;

    std::string line;

    //kopiuje wszytsko do kontenera
    while(getline(plik, line)){
        primary_list.push_back(line);
    }

    plik.close();
    std::ofstream endlist("word_result.txt");

    for(size_t i =0; i<primary_list.size(); i++){

        for(size_t j =0; j<primary_list.size();j++){
            temp = binary_representation(primary_list[j]);
            temp_sum = binary_sum | temp;
            //std::cout<<hamming_weight(temp)<<std::endl;

            if(hamming_weight(temp_sum) == WORDLEN* (word_list.size()+1)){
                word_list.push_back(primary_list[j]);
                binary_sum = temp_sum;
            }
        }
        
        for(size_t i =0; i<word_list.size(); i++){
            //std::cout<<word_list[i]<<std::endl;
            endlist << word_list[i]<<std::endl;
        }

        word_list.clear();
        primary_list.erase(primary_list.begin());
    }


    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
    std::cout<<"Czas wykonywania "<< elapsed.count()<<"µs"<<std::endl;
    endlist.close();
    return 0;
}