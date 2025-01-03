function turnRightMission() {
    isExecuting = true;
    currentStep = 0;
    // updateMissionStepsList();
    console.log("Turn left ... ");
    let missionData = {
     //! Leg 1 
     //? go forward 10 deg
      servo2: 110, // default - 100 Leg1coxa 180 -> servo go  front | 0 -> servo go  back
      servo1: 120, //  Leg1Femur 180 ->  servo go up   | 0 ->  servo go down
      servo0: 180, //  Leg1Tibia 180 ->   servo go down | 0 ->   servo go up

     //! Leg 2
     //* go backword 10 deg
      servo13: 80, // default - 70  Leg2coxa | 180 - back or 0 -> front
      servo14: 45, // Leg2Femur |  0 - up or 180 -down
      servo15: 0, // Leg2Tibia |  0 - down
  
     //! Leg 3
     //? go forward 10 deg
      servo5: 90, // default - 80  Leg3coxa || 180 ->  front and 0 -> back
      servo4: 145, //  Leg3Femur || 180 ->  up and 0 -> down
      servo3: 185, // Leg3Tibia || 180 ->  down and 0 -> up
        
     //! Leg 4
     //* go backword 10 deg

      servo10: 90, // Leg4coxa |  180 - back or 0 - front
      servo11: 52, // Leg4Femur |  0 - up or 180 -down
      servo12: 0, // Leg4Tibia |  0 - down  or 180 up
  
     //! Leg 5
     //? go forward 10 deg
      servo29: 90, //default - 80  Leg5coxa  | 180 - front | 0 -> back
      servo30: 145, //  Leg5Femur |  180 ->  up | 0 -> down
      servo27: 180, //   Leg5Tibia |  0 -> up | 180 -> down
  
     //! Leg 6
     //* go backword 10 deg

      servo18: 150, // default - 140 Leg6coxa  | 180 -> back and 0->
      servo17: 45, // Leg6Femur |  0 -  up and 180 -> down
      servo16: 10, // Leg6Tibia |  0 -> down  and 180 -> up
  
      
      servo28: 0,
      servo31: 70,
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
      
  
    };
  
    let jsondData = JSON.stringify(missionData);
    // console.log(jsondData);
    // console.log(typeof jsondData);
    // connection.send("stand ");
    // connection.send(jsondData);
    connection.send("left")
    // connection.send("right")
  }