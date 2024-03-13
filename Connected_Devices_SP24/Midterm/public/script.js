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
}

// LIGHT SENSOR READING
function handleNewBLESensorValue(value) {
    // console.log("Sensor: " + value);
    document.getElementById("sensor_val").innerHTML = value;

    // detail: is this LIGHT or DARK?
    let state = value > 30 ? "LIGHT" : "DARK";
    document.getElementById("sensor_detail").innerHTML = state;
}

// send values back
function sendVal() {
    if (!myCharacteristic) return;
    BLE.write(myCharacteristic, (document.getElementById("send_value").value));
    document.getElementById("send_value").value = "";
}