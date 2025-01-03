function moveForwardMiddleLegs() {
    isExecuting = true;
    currentStep = 0;
    // updateMissionStepsList();
    console.log("frontToCoxa ...");
  connection.send("moveForwardMiddleLegs")

}