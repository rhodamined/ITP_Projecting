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
    // console.log("socketMessageEvent");
    
    let num = parseInt(event.data);
    console.log(num);

    let y = 0;

    let elem = document.getElementById("socket-data");

    if (num >= sensorMin && num < sensorMax) {
        y = map_range(num, sensorMin, sensorMax, 0, 200);
    } else if (num < sensorMin) {
        y = 0;
    } else if (num > sensorMax) {
        // y = -window.innerHeight;
    }
    console.log(y);

    elem.innerHTML = event.data;
    elem.style.height = y+"px";
}

// always too lazy to write it myself
// https://stackoverflow.com/questions/5649803/remap-or-map-function-in-javascript
function map_range(value, low1, high1, low2, high2) {
    return low2 + (high2 - low2) * (value - low1) / (high1 - low1);
}
