////////////////////////////////////////////////////////////
//
// Search and filter jobs
//
////////////////////////////////////////////////////////////

function element_setClass(e, cls, onoff) {
    var s = e.getAttribute("class");
    if (!s) s = "";
    if (s.length == 0) {
        if (onoff) e.setAttribute("class",cls);
        else       e.setAttribute("class","");
    } else {
        var classes = s.split(/\s+/);
        var hascls = false;
        var rcls = [];
        for (var i in classes) {
            if (cls == classes[i]) { hascls = true }
            else { rcls[rcls.length] = classes[i]; }
        }

        if (onoff) { rcls[rcls.length] = cls }

        e.setAttribute("class",rcls.join(" "));
    }
}

function element_hasClass(e, cls) {
    var s = e.getAttribute("class");
    if (!s || s.length == 0) return false;
    else {
        var classes = s.split(/\s+/);
        for (var i in classes)
            if (cls == classes[i]) return true;
        return false;
    }
}

function element_toggleClass(e, cls) {
    var s = e.getAttribute("class");
    if (!s) s = "";
    if (s.length == 0) {
        e.setAttribute("class",cls);
    } else {
        var classes = s.split(/\s+/);
        var hascls = false;
        var rcls = [];
        for (var i in classes) {
            if (cls == classes[i]) {
                hascls = true
            } else {
                rcls[rcls.length] = classes[i];
            }
        }


        if (! hascls) { rcls[rcls.length] = cls }
        e.setAttribute("class",rcls.join(" "));
    }
}

function matchAny(s,items) {
    for (var i = 0; i < items.length; ++i)
        if (items[i].search(s) >= 0)
            return true;
    return false;
}

function substrMatchAny(substrs,items) {
    for (var i = 0; i < substrs.length; ++i)
        if (! matchAny(substrs[i],items))
            return false;
    return true;
}

var unit_mul_table = {
    "s" : 1, "sec" : 1 , "secs" : 1,  "second" : 1,  "seconds" : 1,
    "m" : 60, "min" : 60, "mins" : 60, "minute" : 60, "minutes" : 60,
    "h" : 3600, "hr" : 3600  , "hrs" : 3600  , "hour" : 3600   , "hours" : 3600,
    "d" : 3600*24, "day" : 3600*24, "days" : 3600*24,
    "M" : 3600*24*30, "month" : 3600*24*30, "months" : 3600*24*30,
    "y" : 3600*24*265, "year" : 3600*24*365, "years" : 3600*24*365
}
function search_buildExp(s) {
    str = s.trim();
    var regex = /(?:(older|newer)\s*than\s*([0-9]+)\s*([a-zA-Z]+)|(!\s*|not\s+)?(?:"([^"]*)"|'([^']*)'|([^\s]+)))(.*)/;
    //              1                    2          3           4                   5         6        7         8
    var exprs = [];
    var nexprs = [];
    var texpr  = [null,null];
    while (str.length > 0) {
        m = str.match(regex);
        if (m === null) {
            return null;
        } else {
            var neg = m[4] != null;
            var matchstr = m[5] != null ? m[5] : (m[6] != null ? m[6] : m[7]);
            if      (matchstr) { if (!neg) exprs[exprs.length] = matchstr; else nexprs[nexprs.length] = matchstr; }
            else if (m[1] != null) {
                var secs = parseInt(m[2]);
                var unit = m[3];
                if (unit in unit_mul_table) {
                    secs *= unit_mul_table[unit];
                } else {
		    return null;
		}

                if      (m[1] == 'older') { if (texpr[1] === null || texpr[1] > secs) texpr[1] = secs; }
                else if (m[1] == 'newer') { if (texpr[0] === null || texpr[0] < secs) texpr[0] = secs; }
            }
            str = m[8].trim();
	
        }
    }
    return [exprs,nexprs,texpr];
}

// e = [expr,nexpr,texpr]
// expr: substring match any of these produces a match
// nexpr: substring match any of these produces a reject
// texpr: time branket: outside of this rejects
//
// For an expression like "newerthan:4 days !x !y z w"
// Means that the age bracket is [now-4 days; now]
// And the logical test is: !(match x || match y) && (match z || match w)
function exprMatch(e,strs,age) {
    var expr = e[0];
    var nexpr = e[1];
    var texpr = e[2];

    // test age brancket
    if (age !== NaN) {
        if (( texpr[0] !== null && age > texpr[0] ) ||
            ( texpr[1] !== null && age < texpr[1] ))
            return false;
    }

    if (nexpr.length > 0) {
        // test string neg-matches
        for (var j = 0; j < strs.length; ++j) {
	    for (var i = 0; i < nexpr.length ; ++i) {
                if (strs[j].search(nexpr[i]) >= 0) {
                    return false;
                }
	    }
        }
    }

    if (expr.length == 0)
        return true;
    else {
        // test string matches
        for (var j = 0; j < strs.length; ++j) {
	    for (var i = 0; i < expr.length ; ++i) {
                if (strs[j].search(expr[i]) >= 0) {
                    return true;
                }
	    }
        }
    }


    return false;
}

function exprMatchRow(tr,expr,now) {
    var jobid  = tr.childNodes[1].firstChild.data;
    var desc   = tr.childNodes[2].firstChild ? tr.childNodes[2].firstChild.data : "";
    var owner  = tr.childNodes[3].firstChild.data;
    var date   = Date.parse(tr.childNodes[5].firstChild.data);
    var age;
    if (date === NaN) age = NaN;
    else age = (now-date)/1000;

    return exprMatch(expr,[jobid,desc,owner],age);
}

var cur_input_delay = null;
function jobs_initializeSearchBox() {
    var text  = document.getElementById('inp-search-text');
    var date  = document.getElementById('inp-search-date');
    var tbody = document.getElementById('jobs-table-body');
    var table = document.getElementById('jobs-table');

    document.getElementById("btn-clear-filter").onclick = function() { text.value = ""; text.focus(); };
    document.getElementById("btn-stop-selected").onclick   = function() { table_forallSelected(table,job_stopJobByRow); };
    document.getElementById("btn-delete-selected").onclick = function() { table_forallSelected(table,job_deleteJobByRow); };
    
    text.oninput = function(ev) {
        if (cur_input_delay != null) clearTimeout(cur_input_delay);
        cur_input_delay = window.setTimeout(function() {
            var str = ev.target.value.trim();
            if (str.length == 0) {
                for (var e = tbody.firstChild; e ; e = e.nextSibling) {
                    element_setClass(e,"hidden",false);
                }
            } else {
	        var expr = search_buildExp(str);
	        var now = Date.now();
                for (var tr = tbody.firstChild; tr ; tr = tr.nextSibling) {
		    var visible = exprMatchRow(tr,expr,now);
                    element_setClass(tr,"hidden",!visible);
                }
            }
        }, 500);
    };
}

function roundN(f,n) {
    var m = (""+f).match("(-?[0-9]*)(?:\.([0-9]*))?(.*)");
    return m[1]+(! m[2] ? "" : ("." +( m[2].length > n ? m[2].substring(0,n) : m[2])))+m[3]
}
function fmtSize(sz) {
    if      (sz < 1024)
        return sz + " B";
    else if (sz < 1024*1024)
        return roundN(sz/1024,2) + " KB";
    else if (sz < 1024*1024*1024)
        return roundN(sz/(1024*1024),2) + " MB";
    else
        return roundN(sz/1024*1024*1024,2) + " GB";
}

function fmtTime(secs) {
    Y = floor(secs/(60*60*24*365))
    val = secs - Y*60*60*24*365;

    M = floor(secs/(60*60*24*30))
    val = secs - M*60*60*24*30;

    d = floor(secs/(60*60*24))
    val = secs - d*60*60*24;

    h = floor(secs/(60*60))
    val = secs - h*60*60;

    m = floor(secs/60)
    val = secs - m*60;

    s = val;

    if (Y > 0 || M > 0 || d > 0)
        return ""+Y+"-"+M+"-"+d+" "+h+":"+m+":"+roundN(s,2);
    else
        return ""+h+":"+m+":"+roundN(s,2);
}

function fmtHrs(secs) {
    h = Math.floor(secs/(60*60))
    val = secs - h*60*60;

    m = Math.floor(val/60)
    val = secs - m*60;

    secs = val

    return ""+h+":"+m+":"+roundN(secs,2)
}

function job_startJobByRow(statuscell,tr) {
    var token = tr.getAttribute("data-token");
    api_startSolve(token,function(ok) {
	if (ok && statuscell !== undefined)
	    tr.childNodes[statuscell].innerHTML = "Running";
    });
}
function job_stopJobByRow(statuscell,tr) {
    var token = tr.getAttribute("data-token");
    api_stopJob(token,function(ok) {
	if (ok && statuscell !== undefined)
	    tr.childNodes[statuscell].innerHTML = "Completed";
    });
}
function job_showDetails(tr) {
    var token = tr.getAttribute("data-token");
    gui_activateOverlay(
        function(div) {
            div.appendChild(elm_h2("Information"));
            var info = elm_div("Loading...");
            div.appendChild(info);
            div.appendChild(elm_h2("Solver log"));
            var log = elm_pre("Loading...");
            div.appendChild(log);
            div.appendChild(elm_h2("Solution"));
            var sol = elm_pre("Loading...");
            div.appendChild(sol);

            api_jobInfo(token, function(data) {
                console.log(data);
		info.innerHTML = "";
                if (data) {
		    var t = document.createElement("table");
		    var tbody = document.createElement("tbody");
		    t.appendChild(tbody);

		    var tr = document.createElement("tr");
		    tr.appendChild(element_makeTD("Desc:")); 
		    tr.appendChild(element_makeTD(data["Desc"])); 
		    tbody.appendChild(tr);

		    var tr = document.createElement("tr");
		    tr.appendChild(element_makeTD("Owner:")); 
		    tr.appendChild(element_makeTD(data["Ownerid"])); 
		    tbody.appendChild(tr);

		    var tr = document.createElement("tr");
		    tr.appendChild(element_makeTD("Origin Address:")); 
		    tr.appendChild(element_makeTD(data["Submitaddr"])); 
		    tbody.appendChild(tr);

		    var tr = document.createElement("tr");
		    tr.appendChild(element_makeTD("Res:")); 
		    tr.appendChild(element_makeTD(data["Rescode"])); 
		    tbody.appendChild(tr);

		    var tr = document.createElement("tr");
		    tr.appendChild(element_makeTD("Trm:")); 
		    tr.appendChild(element_makeTD(data["Trmcode"])); 
		    tbody.appendChild(tr);

		    if (data['Message']) {
			var tr = document.createElement("tr");
			tr.appendChild(element_makeTD("Error message:")); 
			tr.appendChild(element_makeTD(data["Message"])); 
			tbody.appendChild(tr);
		    }
		    
		    info.appendChild(t);
		}
            });
            api_log(token,      function(data) { log.innerHTML = data ? data : "&lt;empty log&gt;"; });
            api_solution(token, function(data) { sol.innerHTML = data ? data : "&lt;no solution&gt;"; }, { "accept" : "text/plain" });
        });
}

function job_deleteJobByRow(tr) {
    var token = tr.getAttribute("data-token");
    api_deleteJob(token,function(ok) {
	if (ok) tr.remove();
    });
}



function jobs_submitFromFile(file,tbody,cells) {
    var reader = new FileReader();
    reader.onload = function(f) {
        api_submitJob(
            file.name,
            f.target.result,
            function(token) {
                if (token !== undefined) {
                    api_jobInfo(token,function(data) {
                        jobs_addRow(tbody,cells,data);
                    });
                }
            },
            { "jobname" : file.name });
    }
    reader.readAsBinaryString(file);
}

function jobs_initializeSubmitBox(tbody,cells) {
    var inpfiles = document.getElementById("inp-problem-file");
    var btnsubmit = document.getElementById("btn-submit-tasks");
    if (inpfiles && btnsubmit) {
        btnsubmit.onclick = function(ev) {
            var files = inpfiles.files;
            if (files.length > 0) {
                for (var i = 0; i < files.length; ++i) {
                    jobs_submitFromFile(files[i],tbody,cells);
                }
                inpfiles.value = "";
            }
        };
    }
}




