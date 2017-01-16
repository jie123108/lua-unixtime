lua-unixtime — Implement of unix_timestamp, from_unixtime function. lua time format.
=====================================

Usage
-----

```lua
local unixtime = require('unixtime')
local unix_timestamp = unixtime.unix_timestamp
local from_unixtime = unixtime.from_unixtime

-- Format parameter, please refer to the definition of strptime, strftime

-- unix_timestamp('Tue, 21 Feb 2012 01:02:03 GMT+04','%a, %d %b %Y %H:%M:%S %z')
local ut, err = unix_timestamp('Fri, 03 Jun 2016 11:13:57 +0800','%a, %d %b %Y %H:%M:%S')
print("ut:", ut,  "err:", err)
assert(ut == 1464923637)
assert(err == nil)

local u = unix_timestamp("2016-06-03 13:13:14", "%Y-%m-%d %H:%M:%S")
assert(u== 1464930794)
local t = from_unixtime(u, "%Y/%m/%d %H%M%S")
assert(t == "2016/06/03 131314")
```

Installation
------------

* Install from current working copy

```
cd lua-unixtime/
make -j 4 
make install
```

License
-------

See the copyright information in the file named `COPYRIGHT`.
