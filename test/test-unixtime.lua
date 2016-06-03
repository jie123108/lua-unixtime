require('unixtime')
local unix_timestamp = unixtime.unix_timestamp
local from_unixtime = unixtime.from_unixtime

-- unix_timestamp('Tue, 21 Feb 2012 01:02:03 GMT+04','%a, %d %b %Y %H:%M:%S %z')
local ut, err = unix_timestamp('Fri, 03 Jun 2016 11:13:57 +0800','%a, %d %b %Y %H:%M:%S')
print("ut:", ut,  "err:", err)
assert(ut == 1464923637)
assert(err == nil)

local u = unix_timestamp("2016-06-03 13:13:14", "%Y-%m-%d %H:%M:%S")
assert(u== 1464930794)
local t = from_unixtime(u, "%Y/%m/%d %H%M%S")
assert(t == "2016/06/03 131314")
