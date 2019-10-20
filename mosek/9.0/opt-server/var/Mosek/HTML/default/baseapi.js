// filename    : string
// filedata    : string or blob that can be written
// onrepy      : optional function(jobtoken:string)
// data        : optional dictionary
//    The dictionary defines additional options
//    - "access-token" is an access token to use
function api_submitJob(filename,filedata,onreply,data) {
    var contentType = "application/binary";
    var ext_start   = filename.lastIndexOf('.');
    var ext_start2  = -1;
    var ext = ext_start >= 0 ? filename.substring(ext_start) : "";
    var ext2 = "";
    if (ext == "bz2" || ext == "gz" || ext == "zst") {
        ext2 = ext;
        ext_start2 = ext_start;        
        ext_start = filename.lastIndexIf('.',ext_start2-1);
        ext = ext_start >= 0 ? filename.substring(ext_start,ext_start2) : "";
    }

    console.log("ext1 = "+ext+", ext2 = "+ext2);
    
    if (ext == ".lp"    ||
        ext == ".mps"   ||
        ext == ".fmps"  ||
        ext == ".opf"   ||
        ext == ".cbf"   ||
        ext == ".ptf"   ||
        ext == ".task"  ||
        ext == ".jtask") {
        contentType = "application/x-mosek-"+ext.substring(1);
    } else {
        contentType = "application/x-mosek-auto";
    }


    
    if      (ext2 == ".bz2") contentType += "+bzip2";
    else if (ext2 == ".gz")  contentType += "+gzip";
    else if (ext2 == ".zst") contentType += "+zstd";


    
    var req = new XMLHttpRequest();
    req.onreadystatechange = function() {
	if (req.readyState == 4) {
            if (onreply) {
                switch (req.status) {
                case 200: onreply(req.responseText); break;
                default:  onreply(); break;
                }
            }
        }
    };

    var url = "/api/submit"; 
    var frag = [];    
    if (data && data["jobname"])
        frag[frag.length] = "jobname="+encodeURIComponent(data["jobname"]);    
    if (frag.length > 0)
        url += "?" + frag.join('&');
    
    req.open("POST", url, true);
    req.setRequestHeader("Content-Type",contentType);
    if (data && data["access-token"])
        req.setRequestHeader("X-Mosek-Access-Token",data["access-token"])
    
    req.send(filedata);
}

// jobtoken : string
// onreply  : optional function(ok : bool)
// data        : optional dictionary
//    The dictionary defines additional options
//    - "access-token" is an access token to use
function api_startSolve(jobtoken,onreply,data) {    
    var req = new XMLHttpRequest();
    req.onreadystatechange = function() {
	if (req.readyState == 4) {
            if (onreply) {
                switch (req.status) {
                case 200: onreply(true); break;
                case 204: onreply(true); break;
                default:  onreply(false); break;
                }
            }
        }
    };

    var url = "/api/solve-background";
    var frag = ["token="+jobtoken];
    if (frag.length > 0)
        url += "?" + frag.join('&');
    
    req.open("GET", url, true);
    if (data && data["access-token"])
        req.setRequestHeader("X-Mosek-Access-Token",data["access-token"])
    req.send();
}

// jobtoken : string
// onreply  : optional function(solution  : optional string,
//                              solformat : optional string,
//                              res       : optional string,
//                              trm       : optional string,
//                              msg       : optional string)
//    Where:
//       - solution is the solution file as a string.
//       - solformat is the MIME type if the solution
//       - res is the solver response code
//       - trm is the solver termination code
//       - msg is the error message of res!=MSK_RES_OK
//    If the solver fails completely, solution and solformat are
//    undefined, and res,trm and msg may or may not be defined,
//    otherwise solution and solformat are defined.
// data        : optional dictionary
//    The dictionary defines additional options
//    - "access-token" is an access token to use
//    - "accept" Requested MIME Type of result, "application/x-mosek-task",
//      "application/x-mosek-jtask" or "text/plain"
function api_solveJobAndWait(jobtoken,onreply,data) {
    var req = new XMLHttpRequest();
    req.onreadystatechange = function() {
	if (req.readyState == 4) {
            if (onreply) {
                switch (req.status) {
                case 200:
                    var res = req.getResponseHeader("X-Mosek-Res-Code") ? req.getResponseHeader("X-Mosek-Res-Code") : undefined;
                    var trm = req.getResponseHeader("X-Mosek-Trm-Code") ? req.getResponseHeader("X-Mosek-Trm-Code") : undefined;
                    var msg = undefined;
                    var sol = undefined;
                    var solfmt = req.getResponseHeader("ContentType") ? req.getResponseHeader("ContentType") : "application/binary";
                    if (res == "MSK_RES_OK")
                        sol = req.responseText;
                    else
                        msg = req.responseText;
                    onreply(sol,solfmt,res,trm,msg);
                    break;
                case 204: onreply(true);
                    var res = req.getResponseHeader("X-Mosek-Res-Code") ? req.getResponseHeader("X-Mosek-Res-Code") : undefined;
                    var trm = req.getResponseHeader("X-Mosek-Trm-Code") ? req.getResponseHeader("X-Mosek-Trm-Code") : undefined;
                    onreply(undefined,undefined,res,trm,msg);
                    break;
                default:  onreply(); break
                }
            }
        }
    };

    
    var frag = ["token="+jobtoken];    
    var url = "/api/solve?" + frag.join('&');
    req.open("GET", url, true);

    if (data && data["accept"])
        req.setRequestHeader("Accept",data["accept"]);
    if (data && data["access-token"])
        req.setRequestHeader("X-Mosek-Access-Token",data["access-token"]);
    req.send();
}

// jobtoken : string
// onreply  : optional function(solution  : optional string,
//                              solformat : optional string,
//                              res       : optional string,
//                              trm       : optional string,
//                              msg       : optional string)
//    Where:
//       - solution is the solution file as a string.
//       - solformat is the MIME type if the solution
//       - res is the solver response code
//       - trm is the solver termination code
//       - msg is the error message of res!=MSK_RES_OK
//    If the solver fails completely, solution and solformat are
//    undefined, and res,trm and msg may or may not be defined,
//    otherwise solution and solformat are defined.
// data        : optional dictionary
//    The dictionary defines additional options
//    - "access-token" is an access token to use
//    - "accept" Requested MIME Type of result, "application/x-mosek-task",
//      "application/x-mosek-jtask" or "text/plain"
function api_solution(jobtoken,onreply,data) {
    var req = new XMLHttpRequest();
    req.onreadystatechange = function() {
	if (req.readyState == 4) {
            if (onreply) {
                switch (req.status) {
                case 200:
                    var res = req.getResponseHeader("X-Mosek-Res-Code") ? req.getResponseHeader("X-Mosek-Res-Code") : undefined;
                    var trm = req.getResponseHeader("X-Mosek-Trm-Code") ? req.getResponseHeader("X-Mosek-Trm-Code") : undefined;
                    var msg = undefined;
                    var sol = undefined;
                    var solfmt = req.getResponseHeader("ContentType") ? req.getResponseHeader("ContentType") : "application/binary";
                    if (res == "MSK_RES_OK")
                        sol = req.responseText;
                    else
                        msg = req.responseText;
                    onreply(sol,solfmt,res,trm,msg);
                    break;
                case 204: onreply(true);
                    var res = req.getResponseHeader("X-Mosek-Res-Code") ? req.getResponseHeader("X-Mosek-Res-Code") : undefined;
                    var trm = req.getResponseHeader("X-Mosek-Trm-Code") ? req.getResponseHeader("X-Mosek-Trm-Code") : undefined;
                    onreply(undefined,undefined,res,trm,msg);
                    break;
                default:  onreply(); break
                }
            }
        }
    };

    var url = "/api/solution"
    var frag = ["token="+jobtoken];    

    if (frag.length > 0)
        url += "?" + frag.join('&');
    req.open("GET", url, true);

    if (data && data["accept"])
        req.setRequestHeader("Accept",data["accept"]); 
    if (data && data["access-token"])
        req.setRequestHeader("X-Mosek-Access-Token",data["access-token"])
    req.send();
}


// jobtoken : string
// onreply  : optional function(res       : optional string,
//                              trm       : optional string,
//                              msg       : optional string)
//    Where:
//       - res is the solver response code
//       - trm is the solver termination code
//       - msg is the error message of res!=MSK_RES_OK
//    Res,trm and msg may or may not be defined, depending on the
//    state of the solver.
// data        : optional dictionary
//    The dictionary defines additional options
//    - "access-token" is an access token to use
//      "application/x-mosek-jtask" or "text/plain"
function api_checkSolution(jobtoken,onreply,data) {
    var req = new XMLHttpRequest();
    req.onreadystatechange = function() {
	if (req.readyState == 4) {
            if (onreply) {
                switch (req.status) {
                case 204: onreply(true);
                    var res = req.getResponseHeader("X-Mosek-Res-Code") ? req.getResponseHeader("X-Mosek-Res-Code") : undefined;
                    var trm = req.getResponseHeader("X-Mosek-Trm-Code") ? req.getResponseHeader("X-Mosek-Trm-Code") : undefined;
                    onreply(res,trm,msg);
                    break;
                default:  onreply(); break
                }
            }
        }
    };

    var frag = ["token="+jobtoken];    
    var url = "/api/solution?" + frag.join('&');
    req.open("HEAD", url, true);
    if (data && data["access-token"])
        req.setRequestHeader("X-Mosek-Access-Token",data["access-token"])
    req.send();
}


// jobtoken : string
// onreply  : optional function(log : string)
// data        : optional dictionary
//    The dictionary defines additional options
//    - "access-token" is an access token to use
//    - "accept" Requested MIME Type of result, "application/x-mosek-task",
//      "application/x-mosek-jtask" or "text/plain"
//    - "offset" defines the offset to get log from
function api_log(jobtoken,onreply,data) {
    var req = new XMLHttpRequest();
    req.onreadystatechange = function() {
	if (req.readyState == 4) {
            if (onreply) {
                switch (req.status) {
                case 200: onreply(req.responseText); break
                case 204: onreply(""); break;
                default:  onreply(); break
                }
            }
        }
    };


    var frag = ["token="+jobtoken];    
    var url = "/api/solverlog?" + frag.join('&');
    req.open("GET", url, true);
    if (data && data["access-token"])
        req.setRequestHeader("X-Mosek-Access-Token",data["access-token"]);
    req.send();

/*
    var frag = ["token="+jobtoken];    
    if (data) {
        if ("accept" in data)
            req.setRequestHeader("Accept",data["accept"]);
        if ("offset" in data)
            frag[frag.length] = "offset="+data["offset"];
    }
    var url = "/api/log?" + frag.join('&'); 
    req.open("GET", url, true);
    console.log("GET",url)
    if (data && data["access-token"])
        req.setRequestHeader("X-Mosek-Access-Token",data["access-token"])
    req.send();
*/
}

// jobtoken : string
// onreply  : optional function(ok : bool)
// data        : optional dictionary
//    The dictionary defines additional options
//    - "access-token" is an access token to use
function api_break(jobtoken,onreply,data) {
    var req = new XMLHttpRequest();
    req.onreadystatechange = function() {
	if (req.readyState == 4) {
            if (onreply) {
                switch (req.status) {
                case 200: onreply(true); break
                case 204: onreply(true); break
                default:  onreply(false); break
                }
            }
        }
    };

    var frag = ["token="+jobtoken];    
    var url = "/api/break?" + frag.join('&'); 
    req.open("GET", url, true);
    if (data && data["access-token"])
        req.setRequestHeader("X-Mosek-Access-Token",data["access-token"])
    req.send();
}

// jobtoken : string
// onreply  : optional function(ok : bool)
// data        : optional dictionary
//    The dictionary defines additional options
//    - "access-token" is an access token to use
function api_deleteJob(jobtoken,onreply,data) {
    var req = new XMLHttpRequest();
    req.onreadystatechange = function() {
	if (req.readyState == 4) {
            if (onreply) {
                switch (req.status) {
                case 200: onreply(true); break
                case 204: onreply(true); break
                default:  onreply(false); break
                }
            }
        }
    };

    var frag = ["token="+jobtoken];    
    var url = "/api/delete?" + frag.join('&'); 
    req.open("GET", url, true);
    if (data && data["access-token"])
        req.setRequestHeader("X-Mosek-Access-Token",data["access-token"])
    req.send();
}

