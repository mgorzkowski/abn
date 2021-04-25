//
// Copyright (c) 2018 Maciej Gorzkowski
//
// This file is licensed under the MIT License.
// Full license text is available in 'LICENSE'.
//

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#include <abn.h>
#include <nonportable/fileoperations.h>

static int wrapped_abn_create(lua_State* L)
{
    // abn_t* abn_create(unsigned int volume);
    printf("abn_create");
    return 0;
}

static int wrapped_abn_free(lua_State* L)
{
    // void abn_free(abn_t* arg);
    printf("abn_free");
    return 0;
}

static int wrapped_abn_to_string(lua_State* L)
{
    // char* abn_to_string(abn_t* arg);
    printf("abn_to_string");
    return 0;
}

static int wrapped_abn_inc(lua_State* L)
{
    // void abn_inc(abn_t* arg);
    printf("abn_inc");
    return 0;
}

static const struct luaL_Reg abn2lua [] = {
    {"abn_create", wrapped_abn_create},
    {"abn_free", wrapped_abn_free},
    {"abn_to_string", wrapped_abn_to_string},
    {"abn_inc", wrapped_abn_inc},
    {NULL, NULL}
};


int luaopen_abn2lua(lua_State *L)
{
    luaL_newlib(L, abn2lua);
    return 1;
}
