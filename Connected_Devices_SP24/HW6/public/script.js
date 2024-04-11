//can be found in config.js
//assemble URL (or just manually type it here)
// const urlPost = `http://${serverIP}:${port}${endpointPOST}`;
// const urlGet = `http://${serverIP}:${port}${endpointGET}`;


async function postData() {
    const deviceID = document.getElementById("id_input").value;
    const res = await fetch(`http://${serverIP}:${port}/textData?deviceID=${deviceID}`, {
        method: "POST", 
        body: document.getElementById("msg_input").value
    });
    const body = await res.text();
    window.alert(`server responded with: ${body}`);
}

//declare an async function if you're making HTTP requests inside it
async function getData() {
    const deviceID = document.getElementById("get_id_input").value;
    const res = await fetch(`http://${serverIP}:${port}/textData?deviceID=${deviceID}`); //make the request
    //const body = await res.text() //if expecting a plain text response
    const body = await res.json();
    
    parseData(body);
}

function parseData(json) {
    document.getElementById("table_body").innerHTML = "";

    // read json into array
    let arr = [];
    for (const dataPoint of json) {
        arr.push(dataPoint);
    }

    // display most recent first
    for (let i = arr.length-1; i >= 0; i--) {
        let dataPoint = arr[i];
        const newRow = document.createElement("tr"); //create a new table row
        
        const dataCell = document.createElement("td"); //create a new table cell
        dataCell.innerHTML = dataPoint.data;
    
        const timeCell = document.createElement("td");
        timeCell.innerHTML = new Date(dataPoint.timeSent).toString();
    
        newRow.appendChild(dataCell);
        newRow.appendChild(timeCell);
    
        document.getElementById("table_body").appendChild(newRow);
    }
}

//declare an async function if you're making HTTP requests inside it
async function getIDs() {
    const res = await fetch(`http://${serverIP}:${port}/deviceID`); //make the request
    //const body = await res.text() //if expecting a plain text response
    const body = await res.json();
    parseData(body);
}
