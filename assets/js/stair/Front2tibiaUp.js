function frontToCoxa() {
  isExecuting = true;
  currentStep = 0;
  // updateMissionStepsList();
  console.log("frontToCoxa ...");

  let missionData = {
    servo2: 150, // Leg1coxa 180 -> servo go  front | 0 -> servo go  back
    servo1: 155, //  Leg1Femur 180 ->  servo go up   | 0 ->  servo go down
    servo0: 180, //  Leg1Tibia 180 ->   servo go down | 0 ->   servo go up

    servo13: 30, // Leg2coxa | 180 - back or 0 -> front
    servo14: 20, // Leg2Femur |  0 - up or 180 -down
    servo15: 0, // Leg2Tibia |  0 - down

    servo5: 80, //  Leg3coxa || 180 ->  front and 0 -> back
    servo4: 155, //  Leg3Femur || 180 ->  up and 0 -> down
    servo3: 180, // Leg3Tibia || 180 ->  down and 0 -> up

    servo10: 100, // Leg4coxa |  180 - back or 0 - front
    servo11: 20, // Leg4Femur |  0 - up or 180 -down
    servo12: 0, // Leg4Tibia |  0 - down  or 180 up

    servo29: 70, //  Leg5coxa  | 180 - front | 0 -> back
    servo30: 160, //  Leg5Femur |  180 ->  up | 0 -> down
    // servo31: 90, //   Leg5Tibia |  0 -> up | 180 -> down
    servo27: 180,

    servo18: 150, // Leg6coxa  | 180 -> back and 0->
    servo17: 20, // Leg6Femur |  0 -  up and 180 -> down
    servo16: 5, // Leg6Tibia |  0 -> down  and 180 -> up

    servo6: 90,
    servo7: 90,
    servo8: 90,
    servo9: 90,

    servo19: 90,
    servo20: 90,
    servo21: 90,

    servo22: 90,
    servo23: 90,
    servo24: 90,

    servo25: 90,
    servo26: 90,

    servo28: 90,
  };

  let jsondData = JSON.stringify(missionData);

  // console.log(jsondData);
  // console.log(typeof (jsondData));
  connection.send(jsondData);
  // connection.send("sit")
}

function front2TibiaUp() {
  isExecuting = true;
  currentStep = 0;
  // updateMissionStepsList();
  console.log("front2TibiaUp ...");

  let missionData = {
    servo2: 150, // Leg1coxa 180 -> servo go  front | 0 -> servo go  back
    servo1: 155, //  Leg1Femur 180 ->  servo go up   | 0 ->  servo go down
    servo0: 0, //  Leg1Tibia 180 ->   servo go down | 0 ->   servo go up

    servo13: 30, // Leg2coxa | 180 - back or 0 -> front
    servo14: 20, // Leg2Femur |  0 - up or 180 -down
    servo15: 180, // Leg2Tibia |  0 - down

    servo5: 80, //  Leg3coxa || 180 ->  front and 0 -> back
    servo4: 155, //  Leg3Femur || 180 ->  up and 0 -> down
    servo3: 180, // Leg3Tibia || 180 ->  down and 0 -> up

    servo10: 100, // Leg4coxa |  180 - back or 0 - front
    servo11: 20, // Leg4Femur |  0 - up or 180 -down
    servo12: 0, // Leg4Tibia |  0 - down  or 180 up

    servo29: 70, //  Leg5coxa  | 180 - front | 0 -> back
    servo30: 160, //  Leg5Femur |  180 ->  up | 0 -> down
    // servo31: 90, //   Leg5Tibia |  0 -> up | 180 -> down
    servo27: 180,

    servo18: 150, // Leg6coxa  | 180 -> back and 0->
    servo17: 20, // Leg6Femur |  0 -  up and 180 -> down
    servo16: 5, // Leg6Tibia |  0 -> down  and 180 -> up

    servo6: 90,
    servo7: 90,
    servo8: 90,
    servo9: 90,

    servo19: 90,
    servo20: 90,
    servo21: 90,

    servo22: 90,
    servo23: 90,
    servo24: 90,

    servo25: 90,
    servo26: 90,

    servo28: 90,
  };

  let jsondData = JSON.stringify(missionData);

  // console.log(jsondData);
  // console.log(typeof (jsondData));
  connection.send(jsondData);
  // connection.send("sit")
}

function applyForceFrontTibia() {
  isExecuting = true;
  currentStep = 0;
  // updateMissionStepsList();
  console.log("applyForceFrontTibia ...");

  let missionData = {
    servo2: 150, // Leg1coxa 180 -> servo go  front | 0 -> servo go  back
    servo1: 155, //  Leg1Femur 180 ->  servo go up   | 0 ->  servo go down
    servo0: 180, //  Leg1Tibia 180 ->   servo go down | 0 ->   servo go up

    servo13: 30, // Leg2coxa | 180 - back or 0 -> front
    servo14: 20, // Leg2Femur |  0 - up or 180 -down
    servo15: 0, // Leg2Tibia |  0 - down

    servo5: 80, //  Leg3coxa || 180 ->  front and 0 -> back
    servo4: 155, //  Leg3Femur || 180 ->  up and 0 -> down
    servo3: 180, // Leg3Tibia || 180 ->  down and 0 -> up

    servo10: 100, // Leg4coxa |  180 - back or 0 - front
    servo11: 20, // Leg4Femur |  0 - up or 180 -down
    servo12: 0, // Leg4Tibia |  0 - down  or 180 up

    servo29: 70, //  Leg5coxa  | 180 - front | 0 -> back
    servo30: 160, //  Leg5Femur |  180 ->  up | 0 -> down
    // servo31: 90, //   Leg5Tibia |  0 -> up | 180 -> down
    servo27: 180,

    servo18: 150, // Leg6coxa  | 180 -> back and 0->
    servo17: 20, // Leg6Femur |  0 -  up and 180 -> down
    servo16: 5, // Leg6Tibia |  0 -> down  and 180 -> up

    servo6: 90,
    servo7: 90,
    servo8: 90,
    servo9: 90,

    servo19: 90,
    servo20: 90,
    servo21: 90,

    servo22: 90,
    servo23: 90,
    servo24: 90,

    servo25: 90,
    servo26: 90,

    servo28: 90,
  };

  let jsondData = JSON.stringify(missionData);

  // console.log(jsondData);
  // console.log(typeof (jsondData));
  connection.send(jsondData);
  // connection.send("sit")
}









function ExpandFourLegs() {
  isExecuting = true;
  currentStep = 0;
  // updateMissionStepsList();
  console.log("applyForceFrontTibia ...");

  let missionData = {
    servo2: 150, // Leg1coxa 180 -> servo go  front | 0 -> servo go  back
    servo1: 155, //  Leg1Femur 180 ->  servo go up   | 0 ->  servo go down
    servo0: 0, //  Leg1Tibia 180 ->   servo go down | 0 ->   servo go up

    servo13: 30, // Leg2coxa | 180 - back or 0 -> front
    servo14: 20, // Leg2Femur |  0 - up or 180 -down
    servo15: 180, // Leg2Tibia |  0 - down

    servo5: 80, //  Leg3coxa || 180 ->  front and 0 -> back
    servo4: 155, //  Leg3Femur || 180 ->  up and 0 -> down
    servo3: 180, // Leg3Tibia || 180 ->  down and 0 -> up

    servo10: 100, // Leg4coxa |  180 - back or 0 - front
    servo11: 20, // Leg4Femur |  0 - up or 180 -down
    servo12: 0, // Leg4Tibia |  0 - down  or 180 up

    servo29: 70, //  Leg5coxa  | 180 - front | 0 -> back
    servo30: 160, //  Leg5Femur |  180 ->  up | 0 -> down
    // servo31: 90, //   Leg5Tibia |  0 -> up | 180 -> down
    servo27: 180,

    servo18: 150, // Leg6coxa  | 180 -> back and 0->
    servo17: 20, // Leg6Femur |  0 -  up and 180 -> down
    servo16: 5, // Leg6Tibia |  0 -> down  and 180 -> up

    servo6: 90,
    servo7: 90,
    servo8: 90,
    servo9: 90,

    servo19: 90,
    servo20: 90,
    servo21: 90,

    servo22: 90,
    servo23: 90,
    servo24: 90,

    servo25: 90,
    servo26: 90,

    servo28: 90,
  };

  let jsondData = JSON.stringify(missionData);

  // console.log(jsondData);
  // console.log(typeof (jsondData));
  connection.send(jsondData);
  // connection.send("sit")
}









