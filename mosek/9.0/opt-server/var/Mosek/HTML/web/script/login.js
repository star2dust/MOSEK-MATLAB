function login_loginAndReload() {
    var username = document.getElementById('inp-username').value;
    var password = document.getElementById('inp-password').value;
    api_login(username,password,function(user) {
        if (user === null) {
            document.getElementById('msg-error').style.display = 'inline';
            var e = document.getElementById('inp-password');
            e.focus();
            e.select();
        } else {
            var href = window.location.href;
            var p = href.indexOf('?');
            if (p < 0) {
                window.location = "/web/index.html";
            } else {
                var fragments = href.substring(p+1,href.length).split('&');
                for (var i in fragments) {
                    if (fragments[i].startsWith("origin=")) {
                        window.location = fragments[i].substring(7);
                        break;
                    }
                }
            }
        }
    });
}

function login_initialize() {
    document.getElementById("btn-submit").onclick = login_loginAndReload;
    document.getElementById("inp-password").onkeypress = function(ev) { if (ev.key == "Enter") login_loginAndReload(); };
    document.getElementById("inp-username").focus();
}
