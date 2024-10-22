// Pause the robot

function pauseMission() {
  console.log("Pause ...");

  isExecuting = false;
  // updateMissionStepsList();
  // In a real application, you would pause the robot's movement here

  isExecuting = true;
  currentStep = 0;
  // updateMissionStepsList();
  console.log("SwingPhase ... ");

  let missionData = {
    servo2: 90, // 135, // int -135 -> 150  Leg1coxa 180 -> servo go  front | 0 -> servo go  back
    servo1: 90, // 130, // int-130 -> 150  Leg1Femur 180 ->  servo go up   | 0 ->  servo go down
    servo0: 90, // 180, //  Leg1Tibia 180 ->   servo go down | 0 ->   servo go up

    servo13: 90, //60, // Leg2coxa | 180 - back or 0 -> front
    servo14: 90, //45, // Leg2Femur |  0 - up or 180 -down
    servo15: 90, //10, // Leg2Tibia |  0 - down

    servo5: 90, // 90,  //  Leg3coxa || 180 ->  front and 0 -> back
    servo4: 90, // 140,  //  Leg3Femur || 180 ->  up and 0 -> down
    servo3: 90, // 160,  // Leg3Tibia || 180 ->  down and 0 -> up

    servo10: 90, //90,  // Leg4coxa |  180 - back or 0 - front
    servo11: 90, //52,  // Leg4Femur |  0 - up or 180 -down
    servo12: 90, //20,  // Leg4Tibia |  0 - down  or 180 up

    servo29: 90, // 65,   //  Leg5coxa  | 180 - front | 0 -> back
    servo30: 90, // 150,  //  Leg5Femur |  180 ->  up | 0 -> down
    servo31: 90, // 180, //   Leg5Tibia |  0 -> up | 180 -> down

    servo18: 90, // 165, // Leg6coxa  | 180 -> back and 0->
    servo17: 90, // 45,  // Leg6Femur |  0 -  up and 180 -> down
    servo16: 90, // 30,  // Leg6Tibia |  0 -> down  and 180 -> up

    servo19: 90,
    servo20: 90,
    servo21: 90,

    servo6: 90,
    servo7: 90,
    servo8: 90,
    servo9: 90,

    servo22: 90,
    servo23: 90,
    servo24: 90,

    servo25: 90,
    servo26: 90,
    servo27: 90,

    servo28: 90,
  };

  let jsondData = JSON.stringify(missionData);
  console.log(jsondData);
  console.log(typeof jsondData);
  connection.send(jsondData);
}
