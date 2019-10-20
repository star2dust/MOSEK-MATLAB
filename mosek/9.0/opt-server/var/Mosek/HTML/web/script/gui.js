//////////////////////////////////////////////////////////////////////
//
// NODE UTILS
//
//////////////////////////////////////////////////////////////////////
function util_clearNode(n) {
    if (n) {
	while (n.firstChild) n.firstChild.remove(); 
    }
}

function elm_h1(text) {
    var e = document.createElement("h2");
    if (text) e.appendChild(document.createTextNode(text));
    return e;
}

function elm_h2(text) {
    var e = document.createElement("h2");
    if (text) e.appendChild(document.createTextNode(text));
    return e;
}

function elm_pre(text,clss) {
    var e = document.createElement("pre");    
    if (text) e.appendChild(document.createTextNode(text));
    if (clss) e.setAttribute("class",clss)
    return e;
}

function elm_div(text,clss) {
    var e = document.createElement("div");    
    if (text) e.appendChild(document.createTextNode(text));
    if (clss) e.setAttribute("class",clss)
    return e;
}


function hasClass(n,name) {
    var cls = n.getAttribute("class");
    if (! cls || cls.length == 0)
        return false;
    else {
        var clss = cls.split(/\s+/);
        for (var i in clss) {
            if (clss[i] == name)
                return true;
        }
    }
    return false;
}

function toggleClass(n,name) {
    var cls = n.getAttribute("class");
    if (! cls || cls.length == 0) {
        n.setAttribute("class",name);
    } else {
        var r = []
        var has = false
        var clss = cls.split(/\s+/);
        for (var i in clss) {
            if (clss[i] == name)
                has = true;
            else
                r[r.length] = clss[i];
        }
        if (! has)
            r[r.length] = name;
        n.setAttribute("class",r.join(" "));
    }
}

function setClass(n,name,val) {
    var cls = n.getAttribute("class");
    if (! cls || cls.length == 0) {
        n.setAttribute("class",name);
    } else {
        var r = []
        var has = false
        var clss = cls.split(/\s+/);
        for (var i in clss) {
            if (clss[i] == name)
                has = true;
            else
                r[r.length] = clss[i];
        }
        if (val)
            r[r.length] = name;
        n.setAttribute("class",r.join(" "));
    }
}

//////////////////////////////////////////////////////////////////////
//
// TABLE POPULATING FUNCTIONS
//
//////////////////////////////////////////////////////////////////////

function jobs_addRow(tbody,cells,r) {
    var tr = document.createElement("tr");
    tr.tabindex = tbody.lastElementChild ? tbody.lastElementChild.tabindex+1 : 1;
    tr.setAttribute("data-token",r.Taskid);
    if (r.Expired)
        setClass(tr,"expired",true);

    var statuscell = undefined;
    for (var j = 0; j < cells.length; ++j) if (cells[j] == 'status') statuscell = j;
    for (var j = 0; j < cells.length; ++j) {
        var td  = document.createElement("td");
        if      (cells[j] == "id")
            td.appendChild(document.createTextNode(r.Taskid));
        else if (cells[j] == "desc")
            td.appendChild(document.createTextNode(r.Desc));
        else if (cells[j] == "status")
            td.appendChild(document.createTextNode(r.Status));
        else if (cells[j] == "owner")
            td.appendChild(document.createTextNode(r.Ownerid));
        else if (cells[j] == "time")
            td.appendChild(document.createTextNode(r.Submittime));
        else if (cells[j] == "duration")
            td.appendChild(document.createTextNode(r.Duration && r.Duration > 0 ? fmtHrs(r.Duration*1e-9) : ""));
        else if (cells[j] == "size")
            td.appendChild(document.createTextNode(r.Filesize > 0 ? fmtSize(r.Filesize) : undefined, r.Filesize));
        else if (cells[j] == "ops") {
            td.appendChild(
                iconbar_make([
                    icon_make("@info", "Show info", function(ev) { job_showDetails(tr) }),
                    icon_make("@play", "Start job", function(ev) { job_startJobByRow(statuscell,tr) }),
                    icon_make("@stop", "Stop job",  function(ev) { job_stopJobByRow(statuscell,tr) }),
                    icon_make("@remove", "Delete job",function(ev) { job_deleteJobByRow(tr) })
                ]));
        }
        tr.appendChild(td);
    }
    tbody.appendChild(tr);
}

function initialize_jobsTable(user) {
    var table = document.getElementById("jobs-table");
    if (table) {
	jobs_initializeSearchBox();
	table_makeActive(table);
        var global = hasClass(table,"global");
	var tbody = null;
	var theadrow = null;
	var thead = null;
	for (var n = table.firstElementChild; n; n = n.nextElementSibling) 
            if (n.nodeName == "THEAD") {
		thead = n;
		if (thead.firstElementChild.nodeName == "TR")
                    theadrow = n.firstElementChild
            } else if (n.nodeName == "TBODY")
		tbody = n;

	
	var cells = [];
	var statuscell = undefined;
	if (theadrow)
            for (var n = theadrow.firstElementChild; n ; n = n.nextElementSibling)
		if (n.nodeName == 'TH') {
                    var item = n.getAttribute("data-item")
                    if (item == 'status')
			statuscell = cells.length;
                    cells[cells.length] = item;
		}

	jobs_initializeSubmitBox(tbody,cells);
	
	if (cells.length > 0 && tbody) {
            api_listJobs(
		function(resp) {
                    table_makeActive(tbody.parentElement);

                    while (tbody.firstChild)
			tbody.firstChild.remove();

                    for (var i = 0; i < resp.length; ++i) {
			var r = resp[i];
			jobs_addRow(tbody,cells,r);
                    }
		},
                global ? undefined : user);
	}
    }
}

function token_addRow(tbody,cells,r) {
    var tr = document.createElement("tr");
    tr.setAttribute("data-serial",r.Serial);
    if (r.Expired)
        tr.setAttribute('class','expired');

    for (var j = 0; j < cells.length; ++j) {
        var td  = document.createElement("td");
	if      (cells[j] == "desc") 
	    td.appendChild(document.createTextNode(r.Description));
	else if (cells[j] == "owner")
	    td.appendChild(document.createTextNode(r.Owner));
	else if (cells[j] == "expiry") 
	    td.appendChild(document.createTextNode(fmtTimeCasual(r.Expires*1000-Date.now()), r.Expires));
	else if (cells[j] == "perm-submit")
	    td.appendChild(document.createTextNode(r.Permissions['submit'] ? "yes" : "no"));
	else if (cells[j] == "perm-admin")
	    td.appendChild(document.createTextNode(r.Permissions['admin'] ? "yes" : "no"));
	else if (cells[j] == "ops")            
            td.appendChild(
                iconbar_make([
                    icon_make("@remove","Delete Token",function(ev) { token_deleteByRow(tr); } )
                ]));
	tr.appendChild(td);
    }
    // functions

    tbody.appendChild(tr);
}

function initialize_tokensTable(user) {
    var table = document.getElementById("tokens-table");
    if (table) {
        var global = hasClass(table,"global");
        
	var tbody    = null;
	var theadrow = null;
	var thead = null;
	for (var n = table.firstElementChild; n; n = n.nextElementSibling) 
            if (n.nodeName == "THEAD") {
		thead = n;
		if (thead.firstElementChild.nodeName == "TR")
                    theadrow = n.firstElementChild
            } else if (n.nodeName == "TBODY")
		tbody = n;

	
	var cells = [];
	var statuscell = undefined;
	if (theadrow)
            for (var n = theadrow.firstElementChild; n ; n = n.nextElementSibling)
		if (n.nodeName == 'TH') {
                    var item = n.getAttribute("data-item")
                    if (item == 'status')
			statuscell = cells.length;
                    cells[cells.length] = item;
		}        

        var addrowfunc = function(r) { return token_addRow(tbody,cells,r); }
        
	document.getElementById("btn-create-token").onclick = function() {
            var expirydate = document.getElementById("input-expiry");
            var expirydays = document.getElementById("input-expiry-days");

            var expirysecs = undefined;
            if (expirydays) {
                var expiry = parseInt(expirydays.value);
                if (isNaN(expiry))
                    expirysecs = undefined;
                else
                    expirysecs = expiry * 60*60*24;
            } else if (expirydate) {
                expirysecs = Date.parse(expirydata.value);
                if (isNaN(expiry))
                    expirysecs = undefined;
                else
                    expirysecs = Math.round((expiry - Date.now()) / 1000);
            }
            
            if (expirysecs !== undefined) {
		var desc   = document.getElementById("inp-desc").value;
		var userid = user.Userid;
		var perms = []
		if (document.getElementById("inp-perm-admin").checked) perms[perms.length]  = "admin";
		if (document.getElementById("inp-perm-submit").checked) perms[perms.length] = "submit";
		token_requestCreate(expirysecs,perms,userid,desc,addrowfunc);
            } else {
            }
	}
	api_listTokens(
            function(ok,data) {
                console.log("Populate tokens, ok? "+ok+", data = ",data);
		if (ok) {
		    while (tbody.firstChild)
			tbody.firstChild.remove();        
		    console.log(cells);
		    for (var i = 0; i < data.length; ++i)
                        addrowfunc(data[i]);
		}
            },
            global ? undefined : user.Userid
	)
	
	var l = document.getElementsByClassName("active-rows");
	for (var i = 0; i < l.length; ++i) {
            if (l[i].nodeName == "TABLE") 
		table_makeActive(l[i]);
	}

	document.getElementById("btn-delete-selected").onclick = function() {
            table_forallSelected(t,token_deleteByRow);
	};

    }
}



function user_addRow(tbody,cells,r) {
    var tr = document.createElement("tr");
    tr.setAttribute("data-userid",r.Userid);
    for (var j = 0; j < cells.length; ++j) {        
        var td = document.createElement("td"); tr.appendChild(td);
        if      (cells[j] == "userid")
            td.appendChild(document.createTextNode(r.Userid));
        else if (cells[j] == "name") {
            td.appendChild(document.createTextNode(r.Name));
            td.setAttribute("data-target","Name")
            td.setAttribute("data-type","str")
            td.setAttribute("class","editable")
        }
        else if (cells[j] == "email") {
            td.appendChild(document.createTextNode(r.Email));
            td.setAttribute("data-target","Email")
            td.setAttribute("data-type","str")
            td.setAttribute("class","editable")
        }
        else if (cells[j] == "password") {
            td.appendChild(document.createTextNode("****"));
            td.setAttribute("data-target","Password")
            td.setAttribute("data-type","pwd")
            td.setAttribute("class","editable")
        }
        else if (cells[j] == "perm-login")
            td.appendChild(users_editPermission(r.Userid, "login", r.Permissions["login"]))
        else if (cells[j] == "perm-submit")
            td.appendChild(users_editPermission(r.Userid, "submit", r.Permissions["submit"]))
        else if (cells[j] == "perm-use-token")
            td.appendChild(users_editPermission(r.Userid, "use-tokens", r.Permissions["use-tokens"]))
        else if (cells[j] == "perm-create-token")
            td.appendChild(users_editPermission(r.Userid, "create-tokens", r.Permissions["create-tokens"]))
        else if (cells[j] == "perm-use-api")
            td.appendChild(users_editPermission(r.Userid, "use-api", r.Permissions["use-api"]))
        else if (cells[j] == "perm-admin")
            td.appendChild(users_editPermission(r.Userid, "admin", r.Permissions["admin"]))
        else if (cells[j] == "ops") {
            td.appendChild(
                iconbar_make([
                    icon_make("@remove","Delete User",function(ev) { users_deleteUser(tr); })
                ]));
        }

        tr.append(td);
        tbody.append(tr);
    }
}

function initialize_usersTable() {
    console.log("init users table");
    api_listUsers(function(resp) {
	if (resp) {
            var table = document.getElementById("users-table");
            var thead = null;
            var tbody = null;
            var tfoot = null;

            for (var n = table.firstElementChild; n; n = n.nextElementSibling)
                if (n.nodeName == 'THEAD')
                    thead = n;
                else if (n.nodeName == 'TBODY')
                    tbody = n;
                else if (n.nodeName == 'TFOOT')
                    tfoot = n;
            if (thead && tbody) {
                var cells = [];
                if (thead.firstElementChild.nodeName == 'TR')
                    for (var n = thead.firstElementChild.firstElementChild; n; n = n.nextElementSibling) {
                        if (n.hasAttribute("data-item"))
                            cells[cells.length] = n.getAttribute("data-item");
                        else
                            cells[cells.length] = false;
                    }
                while (tbody.firstChild) {
                    tbody.firstChild.remove();
                }

                for (var i in resp)
		    user_addRow(tbody,cells,resp[i]);

                tbody.onclick = users_editEntry;
            }
	}
    });
}




//////////////////////////////////////////////////////////////////////
//
// DYNAMIC GUI FUNCTIONS
//
//////////////////////////////////////////////////////////////////////

function gui_displayError(msg) { document.getElementById("error-msg").innerHTML  = msg; }
function gui_clearError() { document.getElementById("error-msg").innerHTML  = ""; }

function gui_displayMessage(msg) { document.getElementById("status-msg").innerHTML  = msg; }
function gui_clearMessage() { document.getElementById("status-msg").innerHTML  = ""; }

function gui_getuser(onreply) {
    var req = new XMLHttpRequest();
    req.onreadystatechange = function() {
        if (req.readyState == 4) {
            if (onreply != null) {
                if (req.status == 200) {
                    var user = JSON.parse(req.responseText);
                    onreply(user)
                } else {
                    onreply(null);
                }
            }
        }
    };

    req.open("GET", "/users/api/whoami", true);
    req.send()
}

function gui_logout() { api_logout(function() { window.location = "/static/login.html?origin="+window.location.pathname; }); }

var identity = null;

function nav_makeEntry(name,href) {
    var li = document.createElement('li');    
    var a  = document.createElement('a');
    a.appendChild(document.createTextNode(name))
    a.setAttribute("href",href);
    
    li.appendChild(a);
    return li;    
}

function menu_makeEntry(name,href) {
    var li = document.createElement('li');
    var a  = document.createElement('a');
    a.appendChild(document.createTextNode(name))
    a.setAttribute("href",href);
    li.appendChild(a);
    return li;    
}

function initialize_gui(onready) {
    gui_getuser(function(user) {
        if (user === null) {
            window.location = "/static/login.html?origin="+window.location.pathname;
        } else {
            identity = user;
            
            var e = document.getElementById('user-id'); if (e) e.innerHTML = identity.Userid;
            var nav = document.getElementById('nav-items');
            var usermenu = document.getElementById('user-items');
	    if (nav) 
		if (user.Permissions["admin"]) {
                    nav.insertBefore(menu_makeEntry("Jobs","alljobs.html"),nav.firstChild);
                    nav.insertBefore(menu_makeEntry("Access Tokens","alltokens.html"),nav.firstChild);
                    nav.insertBefore(menu_makeEntry("Users","userlist.html"),nav.firstChild);
		}
	    
            if (onready != null) {
                onready(user);
            }

            var main = document.getElementById("main");
            if (main) {
                var overlay = document.createElement("div");
                overlay.setAttribute("id","overlay");
                overlay.setAttribute("class","hidden");
                
                var content = document.createElement("div");
                content.setAttribute("class","overlay-content");
                overlay.appendChild(content);
                
                main.parentElement.appendChild(overlay);
            }

	    if (document.getElementById("tokens-table"))
		initialize_tokensTable(user);
	    if (document.getElementById("users-table"))
		initialize_usersTable(user);
	    if (document.getElementById("jobs-table"))
		initialize_jobsTable(user);
	    if (document.getElementById("user-form"))
		profile_fillInDetails(user);
        }
    });
}

function gui_activateOverlay(populate,onoverlayclose) {
    var overlay = document.getElementById("overlay");
    setClass(overlay,"hidden",false);
    if (overlay) {
        var content = overlay.firstElementChild;
        while (content.firstElementChild) content.firstElementChild.remove();
	var div = document.createElement("div");
	div.setAttribute("class","button button-close");
	div.setAttribute("style","float : right;")
	content.appendChild(div);
        overlay.onclick = function() {
            setClass(overlay,"hidden",true);
            if (onoverlayclose)
                onoverlayclose();
        };
        populate(content);
    }
}


// namespace profile {
function profile_fillInDetails(user) {
    document.getElementById('field-user-id').value        = identity.Userid;
    document.getElementById('field-user-name').value      = identity.Name;
    document.getElementById('field-user-email').value     = identity.Email;
    document.getElementById('field-user-submitter').checked = identity.Permissions['submit'] 
    document.getElementById('field-user-accesstoken').checked = identity.Permissions['use-tokens'] || identity.Permissions['create-tokens'];
    document.getElementById('field-user-admin').checked     = identity.Permissions['admin'];
}

function profile_submitUserChanges(onreply) {
    var name  = document.getElementById("field-user-name").value;
    var email = document.getElementById("field-user-email").value;
    var pwd   = document.getElementById("field-user-password").value;
    var npwd1 = document.getElementById("field-user-new-pwd1").value;
    var npwd2 = document.getElementById("field-user-new-pwd2").value;

    if (npwd1.length > 0 && npwd2.length > 0 && npwd1 != npwd2) {
	gui_displayError("New password 1 and 2 are not identical - please try again");
        document.getElementById("field-new-pwd").value  = "";
        document.getElementById("field-new-pwd2").value = "";
        document.getElementById("field-new-pwd").focus();
        return;
    }

    var perms = [];
    if (document.getElementById('field-user-submitter').checked)
        perms[perms.length] = 'submit';
    if (document.getElementById('field-user-accesstoken').checked) {
        perms[perms.length] = 'use-tokens';
        perms[perms.length] = 'create-tokens';
    }
    if (document.getElementById('field-user-admin').checked)
        perms[perms.length] = 'admin';
    
    
    var data = { "Userid" : identity.Userid,
                 "Name"   : name,
                 "Email"  : email,
                 'Permissions' : perms };
    if (npwd1.length > 0)
    {
        data["Password"]     = pwd;
        data["Newpassword1"] = npwd1;
        data["Newpassword2"] = npwd2;
    }
    
    var req = new XMLHttpRequest();
    req.onreadystatechange = function() {
        if (req.readyState == 4) {
            if (req.status == 200 || req.status == 204) {
                gui_displayMessage("User information was updated");
            } else {
		gui_displayError("Failed to update user information")
            }
	    document.getElementById("field-user-password").value = "";
	    document.getElementById("field-user-new-pwd1").value = "";
	    document.getElementById("field-user-new-pwd2").value = "";
        }
    };
    req.open("POST", "/users/api/user/create", true);
    req.send(JSON.stringify({"reqstr" : "update-users", "reqdata" : data }));
}
// } // namespace profile

function table_makeActive(tnode) {
    var thead = null;
    var tbody = null;
    for (var n = tnode.firstElementChild; n ; n = n.nextElementSibling) {
        if      (n.nodeName == "THEAD") thead = n;
        else if (n.nodeName == "TBODY") tbody = n;
    }

    if (thead && tbody) {
        var cn = thead.firstElementChild;
        if (cn && cn.nodeName == 'TR') {
            cn = cn.firstElementChild;
            if (cn && cn.nodeName == 'TH') {
                cn = cn.firstElementChild;
                if (cn && cn.nodeName == 'INPUT') {
                    cn.onchange = function(ev) {
                        var check = ev.target.checked;
                        for (var tr = tbody.firstElementChild; tr ; tr = tr.nextElementSibling) {
                            if (tr.nodeName == "TR" && ! hasClass(tr,"hidden"))
                                setClass(tr,"selected",check);
                        }
                    };
                }
            }
        }
        
        tbody.onclick = function(ev) {
            var n = ev.target;
            if (n.nodeName == "TD") n = n.parentElement;
            if (n.nodeName == "TR") toggleClass(n,"selected")
        }
    }
}

function table_forallVisible(tnode,f) {
    var tbody = null;
    for (var n = tnode.firstElementChild; n ; n = n.nextElementSibling) {
        if (n.nodeName == "TBODY") tbody = n;
    }

    if (tbody) {
        for (var n = tbody.firstElementChild; n; n = n.nextElementSibling)
            if (n.nodeName == "TR" && ! hasClass(n,"hidden"))
                f(n)
    }    
}

function table_forallSelected(tnode,f) {
    var tbody = null;
    for (var n = tnode.firstElementChild; n ; n = n.nextElementSibling) {
        if (n.nodeName == "TBODY") tbody = n;
    }

    if (tbody) {
        for (var n = tbody.firstElementChild; n; n = n.nextElementSibling)
            if (n.nodeName == "TR" && hasClass(n,"selected"))
                f(n)
    }    
}

function table_populate(t,data,addrow_func) {
    var tbody = t.firstElementChild;
    while (tbody && tbody.nodeName != "TBODY") tbody = tbody.nextElementSibling;
    
    if (tbody.nodeName == 'TBODY') {
        while (tbody.firstChild)
            tbody.firstChild.remove();        
        for (var i = 0; i < data.length; ++i)
            addrow_func(tbody,data[i])
    }
}

function iconbar_make(icons,orientation) {
    var ul = document.createElement("ul"); ul.setAttribute("class","icons")
    if (orientation == "vertical")
        strClass(ul,"vertical",true);
    else if (orientation == "horizontal")
        strClass(ul,"horizontal",true);
    for (var i = 0; i < icons.length; ++i)
        ul.appendChild(icons[i]);
    return ul;
}

function icon_make(name,label,onclick) {
    var li = document.createElement("li");
    var a  = document.createElement("a"); li.appendChild(a);
    a.setAttribute("href","#");
    a.onclick = onclick;
    setClass(a,"icon",true);    
    if (name.startsWith("@"))
	setClass(a,"fa-"+name.substring(1),true);
    else 
        setClass(a,name,true);

    var span = document.createElement("span"); a.appendChild(span);
    span.setAttribute("class","label");
    span.appendChild(document.createTextNode(label));
    
    return li;
}

function button_make(label,onclick) {
    var btn = document.createElement("div");
    if (label && label.length > 0 && label[0] != '@')
        btn.appendChild(document.createTextNode(label));

    setClass(btn,"button",true);
    if (label && label.length > 0 && label[0] == '@')
        setClass(btn,"button-"+label.substring(1),true);
    btn.onclick = onclick;
    return btn;
}


function element_makeTD(text,data) {
    var td = document.createElement("td");
    if (data !== undefined) 
        td.setAttribute("data",data);
    if (text !== undefined)
        td.appendChild(document.createTextNode(text));
    return td;
}
