//
// Copyright (C) 2015 Francesco Salvestrini
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#include <malloc.h>

extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

#include <new>

#include "lua-sandbox/luasb.hh"

namespace luasb {

#define TCAST_LUAS(X) static_cast<lua_State *>(X)

        static void * l_alloc(void * ud,
                              void * ptr,
                              size_t osize,
                              size_t nsize)
        {
                (void) ud;
                (void) osize;

                if (nsize == 0) {
                        free(ptr);
                        return NULL;
                }

                void * tmp = realloc(ptr, nsize);
                if (!tmp)
                        throw std::bad_alloc();

                return ptr;
        }

        lua_vm::lua_vm()
        { pimpl_ = 0; }

        void lua_vm::flush()
        {
                if (pimpl_)
                        lua_close(TCAST_LUAS(pimpl_));
        }

        bool lua_vm::load(const std::string & code)
        {
                flush();

                pimpl_ = TCAST_LUAS(lua_newstate(l_alloc, NULL));
                if (!pimpl_)
                        throw std::bad_alloc();

                luaL_loadstring(TCAST_LUAS(pimpl_), code.c_str());
                luaL_openlibs(TCAST_LUAS(pimpl_));
                lua_pcall(TCAST_LUAS(pimpl_), 0, LUA_MULTRET, 0);

                return true;
        }

        lua_vm::~lua_vm()
        {  }

        bool lua_vm::execute(const std::string & fname)
        {
                if (fname.empty())
                        return false;
                if (!pimpl_)
                        return false;

                lua_getglobal(TCAST_LUAS(pimpl_), fname.c_str());
                if (lua_pcall(TCAST_LUAS(pimpl_), 0, 1, 0))
                        return false;

                return true;
        }

}
