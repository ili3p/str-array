#include <stdio.h>

#include <lua.h>
#include <lauxlib.h>

typedef struct StrArray{
    int size;
    char values[1];
} StrArray;
                                                           
static int new_array(lua_State *L)
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

    luaL_getmetatable(L, "Torch.strarray");
    lua_setmetatable(L, -2);

    return 1;
}

static int print_array(lua_State *L)
{
    StrArray *array = (StrArray *) lua_touserdata(L, 1);
    lua_pushfstring(L, "strarray(%d)", array->size);

    return 1;
}

static int get_val(lua_State *L)
{
    StrArray *array = (StrArray *) lua_touserdata(L, 1);
    int index = lua_tointeger(L, 2);

    printf("index is %d", index);

    lua_pushfstring(L, "%c", array->values[index]);

    return 1;
}

static const struct luaL_Reg libstrarray[] = {
    { "new", new_array},
    {NULL, NULL}
};

static const struct luaL_Reg libstrarray_m [] = {
    {"__tostring", print_array},
    {"__index", get_val},
    {NULL, NULL}
};

int luaopen_libstrarray(lua_State *L)
{
    luaL_newmetatable(L, "Torch.strarray");

    lua_pushvalue(L, -1);
    lua_setfield(L, -2, "__index");
    luaL_register(L, NULL, libstrarray_m);

    lua_newtable(L);
    luaL_register(L, NULL, libstrarray); 

    return 1;
}


