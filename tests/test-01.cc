#include "lua-sandbox/luasb.hh"

int main(int argc, char * argv[])
{
        luasb::lua_vm x;

        x.load("function f = () ; x = 1 ; end");
        x.execute("");

        return 1;
}
