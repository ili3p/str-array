#include <stdio.h>

#include <lua.h>
#include <lauxlib.h>

typedef struct StrArray{
    int size;
    char values[1];
} StrArray;

static int newstrarry(lua_State *L)
{
    int i, n;
    size_t nbytes;
    StrArray *array;
    
    n = luaL_checkint(L, 1);

    nbytes = sizeof(StrArray) + (n-1)*sizeof(char);

    array = (StrArray *) lua_newuserdata(L, nbytes);

    array->size = n;

    for(i=0; i < n; ++i) {
        array->values[i] = 0;
    }

    return 1;
}


static const struct luaL_Reg strarraylib[] = {
    { "new", newstrarry},
    {NULL, NULL}
};

int luaopen_libstrarray(lua_State *L)
{

    luaL_register(L, NULL, strarraylib); 

    return 1;
}


