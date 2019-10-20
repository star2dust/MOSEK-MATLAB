// namespace users {

// Call to initialize the Users View page, populate lists etc.
function users_initialize() {
    users_updateUserList();
}


// Clear New User form
function users_clearForm() {
    document.getElementById('new-user-login').value = "";
    document.getElementById('new-user-name').value  = "";
    document.getElementById('new-user-email').value = "";
    document.getElementById('new-user-pwd1').value  = "";
    document.getElementById('new-user-pwd2').value  = "";
    document.getElementById("new-user-perm-login"        ).checked = false;
    document.getElementById("new-user-perm-submit"       ).checked = false;
    document.getElementById("new-user-perm-use-api"      ).checked = false;
    document.getElementById("new-user-perm-use-tokens"   ).checked = false;
    document.getElementById("new-user-perm-create-tokens").checked = false;
    document.getElementById("new-user-perm-admin"        ).checked = false;
}

// Defines the currently active bubble
var users_current_bubble = null;

// Remove bubble
function users_clearBubble() {
    if (users_current_bubble) {
        users_current_bubble.remove();
        users_current_bubble = null
    }
}


// Create bubble for editing Yes/No field
function users_editYesNo(node, onselect) {
    var curtext = node.firstChild.data;
    var bubble = document.createElement("div");
    bubble.setAttribute("class","bubble");
    var opt_yes = document.createElement("a");
    opt_yes.appendChild(document.createTextNode("YES"));
    bubble.appendChild(opt_yes);
    bubble.appendChild(document.createTextNode("|"));
    var opt_no = document.createElement("a");
    opt_no.appendChild(document.createTextNode("NO"));
    bubble.appendChild(opt_no);

    opt_yes.onclick = function() { users_clearBubble(); if (onselect) { onselect("yes"); } };
    opt_no.onclick  = function() { users_clearBubble(); if (onselect) { onselect("no"); } };

    users_clearBubble();
    node.appendChild(bubble);
    users_current_bubble = bubble;
    opt_yes.focus();
}

// Create bubble for editing one-line text field
function users_editLine(node, text,onselect) {
    var curtext = node.firstChild.data;
    var bubble = document.createElement("div");
    bubble.setAttribute("class","bubble");
    var ed = document.createElement("input");
    ed.setAttribute("type", "text");
    ed.value = text;
    ed.onkeypress = function(ev) {
	if (ev.key == 'Enter') {
	    users_clearBubble();
	    if (onselect) onselect(ed.value);
	}
    };
    bubble.onkeydown = function(ev) { if (ev.key == 'Escape') { users_clearBubble(); } };

    bubble.appendChild(ed);
    users_clearBubble();
    node.appendChild(bubble);
    users_current_bubble = bubble;
    ed.focus();
}

// Create bubble for editing one-line text field
function users_editPassword(node, onselect) {
    var curtext = node.firstChild.data;
    var bubble = document.createElement("div");
    bubble.setAttribute("class","bubble");

    var div1 = document.createElement("div");
    div1.appendChild(document.createTextNode("New password:"))
    bubble.appendChild(div1);

    var ed1 = document.createElement("input");
    ed1.setAttribute("type", "password");
    bubble.appendChild(ed1);

    var div2 = document.createElement("div");
    div2.appendChild(document.createTextNode("Write password again:"))
    bubble.appendChild(div2);

    var ed2 = document.createElement("input");
    ed2.setAttribute("type", "password");
    bubble.appendChild(ed2);

    ed2.onkeypress = function(ev) {
	if (ev.key == 'Enter') {
	    if (ed1.value != ed2.value) {
                ed1.value = "";
                ed2.value = "";
                div1.setAttribute("style","color : red;")
                div2.setAttribute("style","color : red;")
            } else {
	        users_clearBubble();
	        if (onselect) onselect(ed1.value);
            }
	}
    };
    bubble.onkeydown = function(ev) { if (ev.key == 'Escape') { users_clearBubble(); } };
    users_clearBubble();
    node.appendChild(bubble);
    users_current_bubble = bubble;
    ed1.focus();
}

function users_editPermission(userid,permname,permstate) {
    var span = document.createElement("span");
    var input = document.createElement("input");
    input.type = "checkbox";
    input.checked = permstate;
    input.onchange = function(ev) {
        api_updateUser({"Userid"      : userid,
                        "Permissions" : [ [ permname, ev.target.checked ] ]},
                       function (user) {
                           var newstate = user.Permissions[permname];
                           if (newstate !== undefined)
                               ev.target.checked = newstate
                       });
    };
    span.appendChild(input);
    var label = document.createElement("label");
    span.appendChild(label);
    return span;
}

function users_editEntry(ev) {
    var td = ev.target;
    if (td.nodeName == "TD" && hasClass(td,"editable")) {
        var tr = td.parentNode;
        var userid = tr.firstElementChild.firstChild.data;
        var which = td.getAttribute('data-target');
	var current_value = td.firstChild ? td.firstChild.data : "";
        if (which == "Name") {
	    users_editLine(td,current_value, function(r) {
		api_updateUser({"Userid" : userid,
                                "Name"   : r},
				 function(ok) {
				     if (ok) { td.innerHTML = r }
				 });
	    });
        } else if (which == "Email") {
	    users_editLine(td,current_value, function(r) {
		api_updateUser({"Userid" : userid, "Email" : r},
				 function(ok) { if (ok) { td.innerHTML = r } });
	    });
        } else if (which == "Password") {
	    users_editPassword(td, function(r) {
		api_updateUser({"Userid" : userid, "Password" : r});
	    });
        } else {
                console.log("WTF?? '"+which+"'")
        }
    }
}


var users_active_edit_cell = null;

function users_deleteUser(tr) {
    var userid = tr.getAttribute("data-userid");
    if (userid) {
        api_deleteUser(userid, function(ok) { if (ok) tr.remove(); });
    }
}


function users_createUser() {
    var login = document.getElementById('new-user-login').value;
    var name  = document.getElementById('new-user-name').value;
    var email = document.getElementById('new-user-email').value;
    var npwd1  = document.getElementById('new-user-pwd1').value;
    var npwd2  = document.getElementById('new-user-pwd2').value;

    var perms = [];
    if (document.getElementById("new-user-perm-login"        ).checked)    perms[perms.length] = 'login'        ;
    if (document.getElementById("new-user-perm-submit"       ).checked)    perms[perms.length] = "submit"       ;
    if (document.getElementById("new-user-perm-use-api"      ).checked)    perms[perms.length] = "use-api"      ;
    if (document.getElementById("new-user-perm-use-tokens"   ).checked)    perms[perms.length] = "use-tokens"   ;
    if (document.getElementById("new-user-perm-create-tokens").checked)    perms[perms.length] = "create-tokens";
    if (document.getElementById("new-user-perm-admin"        ).checked)    perms[perms.length] = "admin"        ;

    if (npwd1.length > 0 && npwd2.length > 0 && npwd1 != npwd2) {
	gui_displayError("New password 1 and 2 are not identical - please try again");
        document.getElementById("new-user-pwd1").value = "";
        document.getElementById("new-user-pwd2").value = "";
        document.getElementById("new-user-pwd1").focus();
        return;
    }

    var data = { "Userid"      : login,
		 "Name"        : name,
		 "Email"       : email,
		 "Password"    : npwd1,
                 "Permissions" : perms }

    api_createUser(data,function(newuser) {
	if (newuser) {
	    users_clearForm();
            users_updateUserList();
	} else {
	    gui_displayError("Failed to create user")
	}
    });
}
// } // namespace users
