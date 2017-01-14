"use strict";

var addon3 = require('/usr/lib/node_modules/addon3');

/* print API */
function printTree(item, name) {
  for(var i in item) {
    console.log(name+"."+i, typeof item[i]);
    for(var b in item[i]) {
      console.log(name+"."+i+"."+b, typeof item[i][b]);
      for(var c in item[i][b]) {
        console.log(name+"."+i+"."+b+"."+c, typeof item[i][b][c]);
      }
    }
  }
}

console.log("----------------------------")
printTree(addon3, "addon3");
console.log("----------------------------")

var surface_id = 3;

console.log("setVisible");
var r = addon3.setVisible(surface_id, 1);
console.log("r=" + r);

console.log("setFocus");
var r = addon3.setFocus(surface_id);
console.log("r=" + r)

console.log("setOpacity");
var r = addon3.setOpacity(surface_id, 128);
console.log("r=" + r);

console.log("getWindowsInfo");
var r = addon3.getWindowsInfo();
console.log("r=" + r);


addon3.onWindowChange = function(surface, reason, pid) {
  log.Add("EVENT onWindowChange surface:" + surface + " reason:" + reason + " pid:" + pid);
  if (main_surface_id == -1) {
    main_surface_id = surface;
    log.Add("Main window opened");
  } else if (pid == bg_app_pid) {
    log.Add("bg_app window opened - change zorder");
    addon3.setZorder(surface, 1);
    addon3.setZorder(main_surface_id, 0);
    addon3.setFocus(main_surface_id);
    addon3.setPosition(surface, 500, 350);
    addon3.setScale(surface, 0.3, 0.3);
  }
  else {
    if (!reason) {
      log.Add("Client window opened");
      var test = { surface_id : surface, cnt : 0 };
      setTimeout(function(){ callNext(test); }, TEST_PERIOD);
    } else {
      log.Add("Client window closed");
    }
  }
};

awc.onRunDone = function(req_id, reason, pid) {
  log.Add("EVENT onRunDone req_id:"+ req_id + " reason:" + reason + " pid:" + pid + " kill in:" + (tests.length * TEST_PERIOD));
  if (req_id == bg_app_idd) {
    bg_app_pid = pid;
    log.Add("bg_app PID FOUND: " + bg_app_pid);

  } else {
    if (reason == 0) {
      setTimeout(function(){
        log.Add("KILL (" + pid + ")");
        awc.kill(pid);
        runBrowser();
      }, (tests.length * TEST_PERIOD));
    } else {
      log.Add("RUN FAILED");
    }
  }
}
