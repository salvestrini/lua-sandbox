//
// Copyright (C) 2015 Francesco Salvestrini
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
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

        lua_vm::lua_vm(const std::string & code)
        {
                pimpl_ = TCAST_LUAS(lua_newstate(l_alloc, NULL));
                if (!pimpl_)
                        throw std::bad_alloc();

                luaL_loadstring(TCAST_LUAS(pimpl_), code.c_str());
                luaL_openlibs(TCAST_LUAS(pimpl_));
                lua_pcall(TCAST_LUAS(pimpl_), 0, LUA_MULTRET, 0);
        }

        lua_vm::~lua_vm()
        { lua_close(TCAST_LUAS(pimpl_)); }

        bool lua_vm::execute(const std::string & fname)
        {
                if (fname.empty())
                        return false;

                lua_getglobal(TCAST_LUAS(pimpl_), fname.c_str());
                if (lua_pcall(TCAST_LUAS(pimpl_), 0, 1, 0))
                        return false;

                return true;
        }

}
