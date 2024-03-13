let myCharacteristic;
window.BLE = new p5ble();

// serviceUUID defined in config.js
function BLEConnect() {BLE.connect(serviceUUID, handleBLEConnected)}

function handleBLEConnected(err, characteristics) {
    myCharacteristic = characteristics[0];
    console.log(characteristics[0]);
    BLE.startNotifications(myCharacteristic, handleNewBLEValue);
}

function handleNewBLEValue(value) {
    console.log(value);
    document.body.style.backgroundColor = `rgb(${value/4}, 0, 0`;
}

// send values back
function sendVal() {
    if (!myCharacteristic) return;
    BLE.write(myCharacteristic, (document.getElementById("send_value").value));
}