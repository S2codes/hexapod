function expandFront() {
    isExecuting = true;
    currentStep = 0;
    // updateMissionStepsList();
    console.log("expand front 1 ...");
    let missionData = {
        servo2: 100, // Leg1coxa 180 -> servo go  front | 0 -> servo go  back
        servo1: 155, //  Leg1Femur 180 ->  servo go up   | 0 ->  servo go down
        servo0: 0, //  Leg1Tibia 180 ->   servo go down | 0 ->   servo go up

        servo13: 70, // Leg2coxa | 180 - back or 0 -> front
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
        servo27: 180,
        servo31: 180, //   Leg5Tibia |  0 -> up | 180 -> down

        servo18: 130, // Leg6coxa  | 180 -> back and 0->
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
    connection.send(jsondData);

    setTimeout(() => {


        missionData = {
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
            servo27: 180,
            servo31: 180, //   Leg5Tibia |  0 -> up | 180 -> down

            servo18: 130, // Leg6coxa  | 180 -> back and 0->
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

        jsondData = JSON.stringify(missionData);
        connection.send(jsondData);

    }, 2000);



    setTimeout(() => {


        missionData = {
            servo2: 150, // Leg1coxa 180 -> servo go  front | 0 -> servo go  back
            servo1: 155, //  Leg1Femur 180 ->  servo go up   | 0 ->  servo go down
            servo0: 90, //  Leg1Tibia 180 ->   servo go down | 0 ->   servo go up

            servo13: 30, // Leg2coxa | 180 - back or 0 -> front
            servo14: 20, // Leg2Femur |  0 - up or 180 -down
            servo15: 90, // Leg2Tibia |  0 - down

            servo5: 80, //  Leg3coxa || 180 ->  front and 0 -> back
            servo4: 155, //  Leg3Femur || 180 ->  up and 0 -> down
            servo3: 180, // Leg3Tibia || 180 ->  down and 0 -> up

            servo10: 100, // Leg4coxa |  180 - back or 0 - front
            servo11: 20, // Leg4Femur |  0 - up or 180 -down
            servo12: 0, // Leg4Tibia |  0 - down  or 180 up

            servo29: 70, //  Leg5coxa  | 180 - front | 0 -> back
            servo30: 160, //  Leg5Femur |  180 ->  up | 0 -> down
            servo27: 180,
            servo31: 180, //   Leg5Tibia |  0 -> up | 180 -> down

            servo18: 130, // Leg6coxa  | 180 -> back and 0->
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

        jsondData = JSON.stringify(missionData);
        connection.send(jsondData);

    }, 2000);


    setTimeout(() => {

        missionData = {
            servo2: 150, // Leg1coxa 180 -> servo go  front | 0 -> servo go  back
            servo1: 155, //  Leg1Femur 180 ->  servo go up   | 0 ->  servo go down
            servo0: 90, //  Leg1Tibia 180 ->   servo go down | 0 ->   servo go up

            servo13: 30, // Leg2coxa | 180 - back or 0 -> front
            servo14: 20, // Leg2Femur |  0 - up or 180 -down
            servo15: 90, // Leg2Tibia |  0 - down

            servo5: 120, //  Leg3coxa || 180 ->  front and 0 -> back
            servo4: 145, //  Leg3Femur || 180 ->  up and 0 -> down
            servo3: 185, // Leg3Tibia || 180 ->  down and 0 -> up

            servo10: 60, // Leg4coxa |  180 - back or 0 - front
            servo11: 52, // Leg4Femur |  0 - up or 180 -down
            servo12: 0, // Leg4Tibia |  0 - down  or 180 up

            servo29: 50, //  Leg5coxa  | 180 - front | 0 -> back
            servo30: 145, //  Leg5Femur |  180 ->  up | 0 -> down
            servo27: 185,

            // servo31: 185, //   Leg5Tibia |  0 -> up | 180 -> down

            servo18: 130, // Leg6coxa  | 180 -> back and 0->
            servo17: 45, // Leg6Femur |  0 -  up and 180 -> down
            servo16: 10, // Leg6Tibia |  0 -> down  and 180 -> up

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

            servo28: 90,
        };

        jsondData = JSON.stringify(missionData);
        connection.send(jsondData);


    }, 2000);

    // console.log(jsondData);
    // console.log(typeof (jsondData));
    // connection.send("sit")
}

