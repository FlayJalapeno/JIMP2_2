//
// Created by Kornel on 20.03.2018.
//

#include "TinyUrl.h"
#include <utility>
#include <string>
#include <array>
#include <memory>

std::unique_ptr<tinyurl::TinyUrlCodec> tinyurl::Init() {
    std::unique_ptr<tinyurl::TinyUrlCodec> newPtr = std::make_unique<tinyurl::TinyUrlCodec>();
    return newPtr;
}

void tinyurl::NextHash(std::array<char, 6> *state) {
    int i = 5;
    bool done = false;

    while(!done) {
        int currentValue = (int)(*state)[i];
        if(currentValue == 122) {
            (*state)[i] = '0';
            i--;
        }
        if(currentValue < 122)
        {
            if(currentValue+1 > 90 && currentValue+1<97 )
                (*state)[i] = char(currentValue+7);
            else if(currentValue+1 > 57 && currentValue+1<65)
                (*state)[i] = char(currentValue+8);
            else
                (*state)[i] = char(currentValue + 1);
            done = true;
        }

    }
}

std::string tinyurl::Encode(const std::string &url, std::unique_ptr<TinyUrlCodec> *codec) {
    string encodedUrl =string("");
    (*codec)->fullUrl = url;
    NextHash( &((*codec)->state));
    for(int i=0; i<6; i++)
        encodedUrl += (*codec)->state[i];

    return encodedUrl;
}

std::string tinyurl::Decode(const std::unique_ptr<TinyUrlCodec> &codec, const std::string &hash) {
    return codec->fullUrl;
}