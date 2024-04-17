let spdCharacteristic;
let dirCharacteristic;

let currMode = 0;
let previousMode = 0;

window.BLE = new p5ble();

// serviceUUID defined in config.js
function BLEConnect() {BLE.connect(serviceUUID, handleBLEConnected)}

function handleBLEConnected(err, characteristics) {
    // console.log(characteristics);
    spdCharacteristic = characteristics[0];
    dirCharacteristic = characteristics[1];
    BLE.startNotifications(spdCharacteristic, handleNewSpd);
    BLE.startNotifications(dirCharacteristic, handleNewDir);
}


// ----------------------
// RECEIVE FROM ARDUINO
// ----------------------

// receive new spd value from arduino
function handleNewSpd(value) {
    console.log("handle spd: " + value);
    // change DOM speed val + slider
}

// receive new direction value from arduino
function handleNewDir(value) {
    console.log("handle dir: " + value);

    // change DOM dir: CW or CCW

}


// ------------------
// SEND TO ARDUINO
// ------------------

// Speed
async function sendSpd(value) {

    console.log("Send spd: " + value); 

    if (!spdCharacteristic) {
        window.alert("Characteristic not found");
        return;
    }

    let spd = parseInt(value);

    // TO DO: check if within bounds OR remap

    // await BLE.write(spdCharacteristic, spd);

    // some sort of feedback that it sent?
}

// Direction CW, CCW
async function sendDir(value) {

    console.log("Send dir: " + value); 

    if (!dirCharacteristic) {
        window.alert("Characteristic not found");
        return;
    }
    // if CW, send 1, if CCW, send 0
    // let dir = parseInt(value); 
    
    // await BLE.write(dirCharacteristic, dir);

    // some sort of feedback that it sent?
}



// old

async function sendTxtVal() {
    // do not engage if no characteristic
    if (!modeCharacteristic) return;

    let newMode = document.getElementById("send_value").value;
    console.log(newMode);
    newMode = parseInt(newMode);
    console.log(newMode);
    if (newMode >= 0 && newMode <= 8 && newMode != currMode) {
        console.log("inside the if");
        await BLE.write(modeCharacteristic, newMode);
        document.getElementById("send_value").value = ""; // clear field

        // this is janky, need to recall it from the characteristic instead
        document.getElementById("mode_source").innerHTML = "Textfield";
    }
}


async function sendVal(newMode) {
    if (!spdCharacteristic) return;
    // console.log(newMode);
    newMode = parseInt(newMode);
    // console.log(newMode);
    if (newMode >= 0 && newMode <= 8 && newMode != currMode) {
        console.log("newmode2");
        await BLE.write(modeCharacteristic, newMode);
        document.getElementById("send_value").value = ""; // clear field

        // this is janky, need to recall it from the characteristic instead
        document.getElementById("mode_source").innerHTML = "Autodetect";
    }
}

