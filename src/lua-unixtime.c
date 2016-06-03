/*
* lua-unixtime.c: bindings for unixtime() function
*/

#define LUAUNIXTIME_VERSION     "lua-unixtime 0.1"
#define LUAUNIXTIME_COPYRIGHT   "Copyright (C) 2016, lua-unixtime authors"
#define LUAUNIXTIME_DESCRIPTION "Implements from_unixtime, unix_timestamp function"

#if defined (__cplusplus)
extern "C" {
#endif

#include <lua.h>
#include <lauxlib.h>
#include <stdint.h>
#include <string.h> /* memset */
#include <time.h> /* strptime */

#if defined (__cplusplus)
}
#endif

/* From lua5.1.4 loslib.c */
static void setfield (lua_State *L, const char *key, int value) {
  lua_pushinteger(L, value);
  lua_setfield(L, -2, key);
}

/* From lua5.1.4 loslib.c */
static void setboolfield (lua_State *L, const char *key, int value) {
  if (value < 0)  /* undefined? */
    return;  /* does not set field */
  lua_pushboolean(L, value);
  lua_setfield(L, -2, key);
}

#define FORMAT "%Y-%m-%d %H:%M:%S"
/*
* unix_timestamp(date : string, format : string)
* format like: strptime format， default format is '%Y-%m-%d %H:%M:%S'
*   : unixtime / nil, error_message
*/
static int l_unix_timestamp(lua_State * L)
{
  const char * date = luaL_checkstring(L, 1);
  size_t len = sizeof(FORMAT)-1;
  const char* format = luaL_optlstring(L, 2, FORMAT, &len);

  struct tm tm;

  memset(&tm, 0, sizeof(tm));

  if (!strptime(date, format, &tm))
  {
    lua_pushnil(L);
    lua_pushliteral(L, "failed to parse date");
    return 2;
  }

  uint32_t unixtime =  (uint32_t)mktime(&tm);

  lua_pushnumber(L, unixtime);

  return 1;
}

static int l_from_unixtime(lua_State * L)
{
  time_t unixtime = (time_t)luaL_checknumber(L, 1);
  size_t len = sizeof(FORMAT)-1;
  const char* format = luaL_optlstring(L, 2, FORMAT, &len);

  struct tm tm;

  memset(&tm, 0, sizeof(tm));
  localtime_r(&unixtime, &tm);
  char buf[128];
  memset(buf, 0, sizeof(buf));

  len = strftime(buf, sizeof(buf), format, &tm);
  if (len == 0)
  {
    lua_pushnil(L);
    lua_pushliteral(L, "failed to format date");
    return 2;
  }

  lua_pushlstring(L, buf, len);

  return 1;
}

/* Lua module API */
static const struct luaL_reg R[] =
{
  { "unix_timestamp", l_unix_timestamp },
  { "from_unixtime", l_from_unixtime },
  { NULL, NULL }
};

#ifdef __cplusplus
extern "C" {
#endif

LUALIB_API int luaopen_unixtime(lua_State * L)
{
  /*
  * Register module
  */
  luaL_register(L, "unixtime", R);

  /*
  * Register module information
  */
  lua_pushliteral(L, LUAUNIXTIME_VERSION);
  lua_setfield(L, -2, "_VERSION");

  lua_pushliteral(L, LUAUNIXTIME_COPYRIGHT);
  lua_setfield(L, -2, "_COPYRIGHT");

  lua_pushliteral(L, LUAUNIXTIME_DESCRIPTION);
  lua_setfield(L, -2, "_DESCRIPTION");

  return 1;
}

#ifdef __cplusplus
}
#endif
