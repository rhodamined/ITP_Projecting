let sensorCharacteristic;
let modeCharacteristic;

window.BLE = new p5ble();

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
    // console.log("Mode: " + value);
    document.getElementById("mode_val").innerHTML = value;

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
    document.getElementById("mode_detail").innerHTML = modeDescriptions[value];
    document.getElementById("mode_timestamp").innerHTML = getTimestamp();
}

// LIGHT SENSOR READING
function handleNewBLESensorValue(value) {
    // console.log("Sensor: " + value);
    document.getElementById("sensor_val").innerHTML = value;

    // detail: is this LIGHT or DARK?
    let state = value > 30 ? "LIGHT" : "DARK";
    document.getElementById("sensor_detail").innerHTML = state;

    document.getElementById("sensor_timestamp").innerHTML = getTimestamp();
}

// send values back
async function sendVal() {
    if (!modeCharacteristic) return;
    let newMode = document.getElementById("send_value").value;
    console.log(newMode);
    newMode = parseInt(newMode);
    console.log(newMode);
    if (newMode >= 0 && newMode <= 8) {
        await BLE.write(modeCharacteristic, newMode);
        document.getElementById("send_value").value = ""; // clear field
    }
}

function getTimestamp() {
    let date = new Date();
    return date.toLocaleTimeString();
}