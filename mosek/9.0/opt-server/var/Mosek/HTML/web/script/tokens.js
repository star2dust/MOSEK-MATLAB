function fmtTimeCasual(Tms) {
    var secs_year = 60*60*24*365;
    var secs_day  = 60*60*24;
    var secs_hr   = 60*60;
    var secs_min  = 60;

    var T = Tms < 0 ? -Tms/1000 : Tms/1000;
    var res = [];

    if (T < secs_min)
        return "now";
    
    if (T > secs_year) {
        var r = Math.floor(T/secs_year);
        res[res.length] = r+(r > 1 ? " years" : " year")
        T = T % secs_year;
    }
    if (T > secs_day) {
        var r = Math.floor(T/secs_day);
        res[res.length] = r+(r > 1 ? " days" : " day")
        T = T % secs_day;
    }
    if (T > secs_hr) {
        var r = Math.floor(T/secs_hr);
        res[res.length] = r+(r > 1 ? " hours" : " hour")
        T = T % secs_hr;
    }
    if (T > secs_min) {
        var r = Math.floor(T/secs_min);
        res[res.length] = r+(r > 1 ? " mins" : " min")
        T = T % secs_min;
    }

    if (res.length == 1) return res[0]+(Tms < 0 ? " ago" : "");
    else return res[0] + ", " + res[1] +(Tms < 0 ? " ago" : "");
}

function token_deleteByRow(tr) {    
    if (tr.nodeName == "TR")
        api_deleteToken(tr.getAttribute("data-serial"),
                        function(ok) { if (ok) tr.remove(); })
}

function token_requestCreate(expiry,perms,userid,desc,addrow_func) {
    if (!isNaN(expiry) && userid.length != 0) {
        var data = { "Owner"       : userid,
                     "Expires"     : Math.round(expiry),
                     "Permissions" : perms,
                     "Description" : desc };
        api_createToken(data,function(r) {
            console.log("REPLY: "+r);
            
            if (r) {
                console.log("CREATED TOKEN, expiry="+r.Expires+", user : "+userid+", r = "+r);
                var resfield = document.getElementById("output-token");
                resfield.value = r.Name;
                
                addrow_func(r)
            }
        });
    }
}
