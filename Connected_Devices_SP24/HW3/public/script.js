// config data is in config.js -- not pushed to repo
const endpoint = "testpage";
const socketURL = `${config.protocol}://${config.domain}:${(config.port).toString()}/${endpoint}`

const socket = new WebSocket(socketURL);

socket.addEventListener("open", handleSocketOpen);

function handleSocketOpen() {
    document.body.style.backgroundColor = "green";
}

socket.addEventListener("message", handleSocketMessage);

function handleSocketMessage(event) {
    console.log("socket");
    document.getElementById("socket-data").innerHTML = event.data;
}
