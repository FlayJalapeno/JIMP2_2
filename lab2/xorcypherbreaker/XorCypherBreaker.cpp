//
// Created by Kornel on 20.03.2018.
//

#include "XorCypherBreaker.h"

#include <string>
#include <vector>
#include <algorithm>

using std::find;

std::string XorCypherBreaker(const std::vector<char> &cryptogram, int key_length, const std::vector<std::string> &dictionary){
    std::string key_guess, key_match;
    std::vector<std::string> tekst;
    tekst.emplace_back("");
    bool done = false;
    int it = 0, it_t = 0, match = 0, match_max = 0;
    char lit;
    key_guess = "aaa";
    while(!done){
        lit = (char)(cryptogram[it] ^ key_guess[it%3]);
        if((lit >= 'a' && lit <= 'z' ) || (lit >= 'A' && lit <= 'Z')){
            tekst[it_t].push_back(lit);
        }else{
            if(lit == ' '){
                tekst.emplace_back("");
                it_t++;
            }
        }
        it++;
        if(it == cryptogram.size()){
            while(!tekst.empty()){
                if(dictionary.end() != find(dictionary.begin() , dictionary.end() , tekst.back())){
                    match++;
                }
                tekst.pop_back();
            }
            if(match > match_max){
                key_match = key_guess;
                match_max = match;
            }
            match = 0;
            if(key_guess[2] == 'z'){
                if(key_guess[1] == 'z'){
                    if(key_guess[0] == 'z'){
                        done = true;
                    }else{
                        key_guess[0] = (char)((int)key_guess[0] + 1);
                    }
                    key_guess[1] = 'a';
                }else{
                    key_guess[1] = (char)((int)key_guess[1] + 1);
                }
                key_guess[2] = 'a';
            }else{
                key_guess[2] = (char)((int)key_guess[2] + 1);
            }
            it = 0;
            tekst.clear();
            it_t = 0;
            tekst.emplace_back("");
        }
    }
    return key_match;
}