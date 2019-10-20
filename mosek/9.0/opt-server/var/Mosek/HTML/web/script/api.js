////////////////////////////////////////////////////////////
//
// LOGIN / LOGOUT
//
////////////////////////////////////////////////////////////

function api_getUser(onreply) {
    var req = new XMLHttpRequest();
    req.onreadystatechange = function() {
        if (req.readyState == 4) {
            if (req.status == 200) {
                onreply(JSON.parse(req.responseText));
            } else {
                onreply(null);
            }
        }
    };

    req.open("GET", "/users/api/whoami", true);
}

function api_login(username,password,onreply) {
    var req = new XMLHttpRequest();
    req.onreadystatechange = function() {
        if (req.readyState == 4) {
            if (req.status == 200) {
                onreply(JSON.parse(req.responseText));
            } else {
                onreply(null);
            }
        }
    };

    req.open("POST", "/users/api/login", true);
    req.send(JSON.stringify({"Username":username,"Password":password}));
}

function api_logout(onreply) {
    var req = new XMLHttpRequest();
    req.onreadystatechange = function() {
        if (req.readyState == 4) {
            if (req.status == 200) {
                onreply(true);
            } else {
                onreply(false);
            }
        }
    };

    req.open("GET", "/users/api/logout", true);
    req.send();
}

////////////////////////////////////////////////////////////
//
// ACCESS TOKENS
//
////////////////////////////////////////////////////////////

// data: { Userid : string,
//         Permissions : optional list([name : string, onoff : bool]),
//         Description : optional string }
// onreply: function(data : TokenData)
//    TokenData : {
//       Serial      : int
//       Name        : string
//       Owner       : string
//       Expires     : int
//       Description : string
//       Permissions : map( permname : string -> bool )
//    }
function api_createToken(data,onreply) {
    var req = new XMLHttpRequest();    
    req.onreadystatechange = function() {
        if (req.readyState == 4) {
            console.log("status = "+req.status+",RESP = '"+req.responseText+"'");
            switch (req.status) {
            case 200:
                onreply(JSON.parse(req.responseText));
                break;
            default:
                onreply();
                break;
            }
                
        }
    };
    req.open("POST", "/users/api/token/create", true);
    req.send(JSON.stringify(data));
}

// serial : int
// onreply : function(ok : bool)
function api_deleteToken(serial,onreply) {
    var req = new XMLHttpRequest();
    req.onreadystatechange = function() {
        if (req.readyState == 4)
            switch (req.status) {
            case 200: onreply(true); break
            case 204: onreply(true); break;
            default:  onreply(false); break;
	    }
    }
    
    req.open("GET", "/users/api/token/delete?token-serial="+serial, true);
    req.send();
}
    
// onreply: function(ok : bool, data : list(TokenData))
//    TokenData : {
//       Serial       : int,
//       Owner        : string,
//       Expires      : int,
//       Permissions  : map( permname : string -> bool ),
//       Description  : string
//    }
// user : undefined | username
function api_listTokens(onreply,user) {
    var req = new XMLHttpRequest();
    req.onreadystatechange = function() {
        if (req.readyState == 4)
            switch (req.status) {
            case 200: onreply(true,JSON.parse(req.responseText)); break;
            case 204: onreply(true,[]); break;
            default: onreply(false,[]); break;
            }
    }

    req.open("GET", "/users/api/token/list" + (user !== undefined ? "?owner="+user : ""), true);
    req.send();
}

////////////////////////////////////////////////////////////
//
// JOBS
//
////////////////////////////////////////////////////////////

function api_listJobs(onreply,user) {
    var req = new XMLHttpRequest();
    req.onreadystatechange = function() {
        if (req.readyState == 4) {
            if (req.status == 200 || req.status == 204) {                
                var resp = JSON.parse(req.responseText);
                onreply(resp);
            }
        }
    };

    if (user !== undefined) {
        req.open("POST", "/users/api/jobs/list", true);
        req.send(JSON.stringify({"Owner" : user.Userid }));
    } else {
        req.open("GET", "/users/api/jobs/list", true);
        req.send();
    }
}

function api_startJob(token, onreply) {
    var req = new XMLHttpRequest();
    req.onreadystatechange = function() {
        if (req.readyState == 4) {
	    if (onreply)
		switch (req.status) {
		case 200: onreply(true); break;
		case 204: onreply(true); break;
		default:  onreply(false); break;
		}
	    
        }
    };
    req.open("GET", "/api/solve?token="+token, true);
    req.send();
}

function api_jobInfo(token, onreply) {
    var req = new XMLHttpRequest();
    req.onreadystatechange = function() {
        if (req.readyState == 4) {
	    if (onreply)
		switch (req.status) {
		case 200: onreply(JSON.parse(req.responseText)); break;
		default:  onreply(); break;
		}
	    
        }
    };
    req.open("GET", "/users/api/jobs/info?token="+token, true);
    req.send();
}

////////////////////////////////////////////////////////////
//
// USERS
//
////////////////////////////////////////////////////////////

function api_createUser(data,onreply) {
    var req = new XMLHttpRequest();

    req.onreadystatechange = function() {
        if (req.readyState == 4) {
	    if (onreply)
		switch (req.status) {
		case 200: onreply(JSON.parse(req.responseText));  break;
		default:  onreply(false); break;
		}
        }
    };
    req.open("POST", "/users/api/user/create", true);
    req.send(JSON.stringify(data));
}

function api_deleteUser(userid,onreply) {
    var req = new XMLHttpRequest();

    req.onreadystatechange = function() {
        if (req.readyState == 4) {
	    if (onreply)
		switch (req.status) {
		case 200: onreply(true);  break;
		case 204: onreply(true);  break;
		default:  onreply(false); break;
		}
        }
    };    
    req.open("GET", "/users/api/user/delete?userid="+userid, true);
    req.send();
}

function api_updateUser(data,onreply) {
    var req = new XMLHttpRequest();

    req.onreadystatechange = function() {
        if (req.readyState == 4) {
	    if (onreply)
		switch (req.status) {
		case 200: onreply(JSON.parse(req.responseText));  break;
		default:  onreply(); break;
		}
        }
    };
    req.open("POST", "/users/api/user/update", true);
    req.send(JSON.stringify(data));
}

function api_listUsers(onreply) {
    var req = new XMLHttpRequest();
    req.onreadystatechange = function() {
        if (req.readyState == 4) 
	    switch (req.status) {
	    case 200: onreply(JSON.parse(req.responseText));  break;
	    default:  onreply(); break;
	    }
    };
    req.open("GET", "/users/api/user/list", true);
    req.send();
    
}
