local _M = {}

function _M.greet(name)
	ngx.say("Hello from ", name)
end

return _M
