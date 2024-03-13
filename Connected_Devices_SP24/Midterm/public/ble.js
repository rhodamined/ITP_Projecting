let sensorCharacteristic;
let modeCharacteristic;

let currMode = 0;
let previousMode = 0;

// window.BLE = new p5ble();

// serviceUUID defined in config.js
function BLEConnect() {BLE.connect(serviceUUID, handleBLEConnected)}

function handleBLEConnected(err, characteristics) {
    // console.log(characteristics);
    modeCharacteristic = characteristics[0];
    sensorCharacteristic = characteristics[1];
    BLE.startNotifications(sensorCharacteristic, handleNewBLESensorValue);
    BLE.startNotifications(modeCharacteristic, handleNewBLEModeValue);
}

// MODE
function handleNewBLEModeValue(value) {
    console.log("Mode: " + value);

    let modeDescriptions = [
        "still",
        "Eraser only",
        "Pencil only",
        "Pencil Scribble short",
        "Pencil Scribble long",
        "lurchy quickstep",
        "Two step",
        "Two step v2",
        "Flipping out"
    ]
    
    
    // if (value != previousMode){
        changeMode(value);
        document.getElementById("mode_timestamp").innerHTML = getTimestamp();
        document.getElementById("mode_source").innerHTML = "Arduino";
        document.getElementById("mode_val").innerHTML = value;
        document.getElementById("mode_detail").innerHTML = modeDescriptions[value];
    // }

}

// LIGHT SENSOR READING
function handleNewBLESensorValue(value) {
    // console.log("Sensor: " + value);
    document.getElementById("sensor_timestamp").innerHTML = getTimestamp();
    document.getElementById("sensor_source").innerHTML = "Arduino";
    document.getElementById("sensor_val").innerHTML = value;
    
    // detail: is this LIGHT or DARK?
    let state = value > 30 ? "LIGHT" : "DARK";
    document.getElementById("sensor_detail").innerHTML = state;
}

// send values back
async function sendTxtVal() {
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

// send values back
async function sendVal(newMode) {
    if (!modeCharacteristic) return;
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

function getTimestamp() {
    let date = new Date();
    return date.toLocaleTimeString();
}

function changeMode(newMode) {
    previousMode = currMode;
    currMode = newMode;
}