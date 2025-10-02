#include "env.h"

symbols::Env::Env(shared_ptr<Env> prev) : prev(prev)
{
}

symbols::Env::~Env()
{
}

void symbols::Env::put(const std::string& s, shared_ptr<Symbol> symbol)
{
    symbols[s] = symbol;
}

shared_ptr<symbols::Symbol> symbols::Env::get(const std::string& s)
{
    for (auto e = this; e != nullptr; e = e->prev.get())
    {
        auto it = e->symbols.find(s);
        if (it != e->symbols.end())
        {
            return it->second;
        }
    }
    return nullptr;
}