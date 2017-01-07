"use strict";

var addon2 = require('/usr/lib/node_modules/addon2');

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

printTree(addon2, "addon2");

/*
awc.setVisible(surface_id, 1);
awc.setOpacity(surface_id, 0.5);
awc.setFocus(surface_id);
awc.setPosition(surface_id, 500,100);
awc.setScale(surface_id, 0.5, 0.5);
awc.setSize(surface_id, 600, 600);
awc.animateOpacity(surface_id, 1.0, "COMPOSITOR_LAYOUT_EASING_LINEAR", 4000);
awc.animatePosition(surface_id, 300, 300, "COMPOSITOR_LAYOUT_EASING_LINEAR", 4000);
awc.animateScale(surface_id, 1.0, 1.0, "COMPOSITOR_LAYOUT_EASING_LINEAR", 4000);
awc.setZorder(surface_id, order);
awc.setFocus(surface_id);
*/

