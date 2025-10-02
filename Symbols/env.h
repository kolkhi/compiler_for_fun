#pragma once

#include <map>
#include <memory>
#include <string>
#include "symbol.h"

using namespace std;

namespace symbols
{
    class Env
    {
    public:
        Env(shared_ptr<Env> prev);
        ~Env();

        void put(const std::string& s, shared_ptr<Symbol> symbol);
        shared_ptr<Symbol> get(const std::string& s);

    protected:
        shared_ptr<Env> prev;
        
    private:
        std::map<std::string, shared_ptr<Symbol>> symbols;
    };
} // namespace symbols