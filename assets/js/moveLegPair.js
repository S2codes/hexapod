function moveFrontLegPair() {
  connection.send("moveFrontTwo");
}
function moveMiddleLegPair() {
  connection.send("moveMiddleTwo");
}
function moveLastLegPair() {
  connection.send("moveLastTwo");
}

function moveLeg() {
  console.log("move leg");

  // connection.send("moveleg1");
  // connection.send("moveleg2");
  // connection.send("moveleg3");
  // connection.send("moveleg4");
  // connection.send("moveleg5");
  // connection.send("moveleg6");
  // connection.send("moveFrontTwo");
//   connection.send("moveMiddleTwo");
//   connection.send("moveLastTwo");
  connection.send("frontLegHook");
}
