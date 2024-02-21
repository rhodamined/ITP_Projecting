// config data is in config.js -- not pushed to repo
const broker = YONE_MQTT_URL;
const mqtt_port = YONE_MQTT_PORT; 
        
const mqtt_user = YONE_MQTT_USER;
const mqtt_pass = YONE_MQTT_PASS;


// client ID
const clientID = "Jasper Client";

// the topic incoming messages should be sent to
const subTopic = "Jasper_TOF";
        
const MQTT = new Paho.MQTT.Client(broker, mqtt_port, clientID);

MQTT.connect({
    onSuccess: mqttConnected, // callback function for successful connection
    userName: mqtt_user, // username
    password: mqtt_pass, // password
    useSSL: true
});

//called on successful connection - enables the MQTT message button
//you should subscribe to topics in here as well
function mqttConnected() {
    MQTT.subscribe(subTopic);
    MQTT.onMessageArrived = handleMQTTMessage; //callback function for incoming messages
    console.log("MQTT connected successfully.");
    document.querySelector("#sendMQTTButton").disabled = false;
}

//send an MQTT message with a defined topic and payload
function sendMQTTMessage(topic, payload) {
    const newMessage = new Paho.MQTT.Message(payload);
    newMessage.destinationName = topic;
    MQTT.send(newMessage);
}

function handleMQTTMessage(msg) {
    console.log(msg.payloadString);

    let txt = msg.payloadString;

    let arr = document.getElementsByClassName("data");
    

    if (txt == "DISCONNECTED") {
        for (let e of arr) {
            e.classList.add("red");
            e.classList.remove("blue")
        }
    } else {
        for (let e of arr) {
            e.classList.add("blue");
            e.classList.remove("red")
        }
    }

    let d = new Date().toISOString(); // timestamp
    document.querySelector("#inTopic").innerHTML = msg.destinationName;
    document.querySelector("#inPayload").innerHTML = msg.payloadString;
    document.querySelector("#inTimestamp").innerHTML = d;
}
