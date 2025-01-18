document.getElementById("legForm").addEventListener("submit", function (event) {
  event.preventDefault();

  // Define the mapping of parts to servo numbers
  const servoMapping = {
    "leg1-tibia": 31,
    "leg1-femur": 30,
    "leg1-coxa": 29,
    "leg3-tibia": 28,
    "leg3-femur": 27,
    "leg3-coxa": 26,
    "leg5-tibia": 25,
    "leg5-femur": 24,
    "leg5-coxa": 23,
    "leg2-tibia": 1,
    "leg2-femur": 14,
    "leg2-coxa": 13,
    "leg4-tibia": 12,
    "leg4-femur": 11,
    "leg4-coxa": 10,
    "leg6-tibia": 9,
    "leg6-femur": 8,
    "leg6-coxa": 7,
  };

  // Initialize missionData with default values (90) for all servos
  const missionData = {};

  for (let i = 0; i < 32; i++) {
    missionData[`servo${i}`] = 90; // Set default value of 90
  }

  const inputs = document.querySelectorAll("#legForm .input");

  // Map input values to their corresponding servo numbers
  inputs.forEach((input) => {
    const partName = input.name;
    const servoNumber = servoMapping[partName];

    if (servoNumber !== undefined) {
      // Update only the specified servos with user input
      missionData[`servo${servoNumber}`] = parseInt(input.value, 10);
    }
  });

  console.log("missionData : ");
  console.log(missionData);

  let jsondData = JSON.stringify(missionData);

  // Send the data through the connection
  connection.send(jsondData);
});

function moveLeg() {
  console.log("move leg");
    // connection.send("moveleg1");
  // connection.send("moveleg2");
  connection.send("moveleg3");
  connection.send("moveleg4");
  // connection.send("moveleg5");
  // connection.send("moveleg6");
  // connection.send("moveFrontTwo");
  //   connection.send("moveMiddleTwo");
  //   connection.send("moveLastTwo");
  // connection.send("frontLegHook");
  // connection.send("expandMiddle");
  // connection.send("moveMidleAndLastLegPairForward");
}
function moveLeg12() {
  connection.send("moveleg1");
  connection.send("moveleg2");
}
function moveLeg56() {
  connection.send("moveleg5");
  connection.send("moveleg6");
}



function FrontLegHookandExpandMiddleLast() {
  connection.send("FrontLegHookandExpandMiddleLast");
}

function moveMidleAndLastLegPairForward() {
  connection.send("moveMidleAndLastLegPairForward");
}

function moveMidleAndLastLegPairForward2() {
  connection.send("moveMidleAndLastLegPairForward2");
}

function liftFrontTwo() {
  connection.send("liftFrontTwo");
}

function moveLastLegPairForward() {
  connection.send("moveLastLegPairForward");
}
function moveLastLegPairForwardAndHook() {
  connection.send("moveLastLegPairForwardAndHook");
}

function middleLegsHook() {
  connection.send("middleLegsHook");
}
function lastLegsHook() {
  connection.send("lastLegsHook");
}
function moveFrontForward() {
  connection.send("moveFrontForward");
}

function moveFrontLay() {
  connection.send("moveFrontLay");
}
function moveMiddleLay() {
  connection.send("moveMiddleLay");
}

function moveFrontRow() {
  connection.send("moveFrontRow");
}


function moveFistAndMiddleLay() {
  connection.send("moveFistAndMiddleLay");
}



function moveFrontStraight() {
  connection.send("moveFrontStraight");
}

function moveMiddleStraight() {
  connection.send("moveMiddleStraight");
}
function moveLasttraight() {
  connection.send("moveLasttraight");
}

function moveFront4pairForward() {
  connection.send("moveFront4pairForward");
}

function liftLastTwoLeg() {
  connection.send("liftLastTwoLeg");
}

function moveMidleAndLastLegPairForwardwithOutHook() {
  connection.send("moveMidleAndLastLegPairForwardwithOutHook");
}
