// config data is in config.js -- not pushed to repo
const endpoint = "testpage";
const socketURL = `${config.protocol}://${config.domain}:${(config.port).toString()}/${endpoint}`

const socket = new WebSocket(socketURL);

// socket.addEventListener("open", handleSocketOpen);

// function handleSocketOpen() {
//     document.body.style.backgroundColor = "green";
// }

socket.addEventListener("message", handleSocketMessage);


const sensorMin = 30;
const sensorMax = 450;

function handleSocketMessage(event) {
    

    let data = event.data.split(',');

    console.log(data);

    let num = parseInt(data[0]);
    let buttonState = parseInt(data[1]);

    let y = 0;
    
    let elem = document.getElementById("socket-data");
    let body = document.body;

    // let scale = elem.style.transform;
    // console.log(scale);

    // elem.style.transform = "scale(0.2)";

    // handle button
    if (buttonState == 0) {
        body.style.backgroundColor = "white";
    } else {
        body.style.backgroundColor = "black";
    }

    // handle ToF measurement
    if (num < 3000) { // 9999 is out of range
        elem.style.backgroundColor = "blue";
        if (num >= sensorMin && num < sensorMax) {
            y = map_range(num, sensorMin, sensorMax, 0, 200);
        } else if (num < sensorMin) {
            y = 0;
        } 
        elem.style.height = y+"px";

    } else if (num >= 3000){
        console.log(9999)
        elem.style.backgroundColor = "red";

    }
    // console.log(y);

    let label = num <= 3000 ? num : "OOR";

    elem.innerHTML = label;
}




// always too lazy to write it myself
// https://stackoverflow.com/questions/5649803/remap-or-map-function-in-javascript
function map_range(value, low1, high1, low2, high2) {
    return low2 + (high2 - low2) * (value - low1) / (high1 - low1);
}
