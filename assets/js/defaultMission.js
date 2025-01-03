function defaultMission() {
  isExecuting = true;
  currentStep = 180;
  // updateMissionStepsList();
  console.log("default ...");

  let angle = 90; // Example value to map
  console.log(" angle");
  console.log(angle);

  let missionData = {
    servo1: angle, 
    servo0: angle, 
    servo2: angle, 

    servo3: angle, 
    servo4: angle, 
    servo5: angle, 

    servo6: angle,
    servo7: angle, 
    servo8: angle, 
    servo9: angle, 

    servo10: angle, 
    servo11: angle, 
    servo12: angle, 

    servo13: angle, 
    servo14: angle, 
    servo15: angle, 

    servo16: angle, 
    servo17: angle, 
    servo18: angle, 

    servo19: angle,
    servo20: angle,
    servo21: angle,

    servo22: angle,
    servo23: angle,
    servo24: angle,
    servo25: angle, 
    servo26: angle, 
    servo27: angle, 

    servo28: angle, 

    servo29: angle,
    servo30: angle,
    servo31: angle,
  };

  let jsondData = JSON.stringify(missionData);

  // console.log(jsondData);
  // console.log(typeof (jsondData));
  connection.send(jsondData);
}
