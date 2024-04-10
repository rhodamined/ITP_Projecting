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

    console.log(json);

    for (const e in json) { 
        // console.log(e);

        for (const i in json[e]) {
            console.log(json[e][i]);

            const dataPoint = json[e][i];

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
}

//declare an async function if you're making HTTP requests inside it
async function getIDs() {
    const res = await fetch(`http://${serverIP}:${port}/deviceID`); //make the request
    //const body = await res.text() //if expecting a plain text response
    const body = await res.json();
    parseData(body);
}


// if your endpoint responds with JSON:
async function getColor() {
    console.log("getColor");
    await fetch(urlGet)
        .then(res => res.json())
        .then(json => {
            //do stuff with json here
            let serverColor = json.msg;

            // change color of html body to color received from server
            document.body.style.backgroundColor = serverColor;
        }
    );
}

async function postColor() {
    console.log("postColor");
    //if posting raw text:
    // let contentType = 'text/plain';
    // let reqBody = document.getElementById("input").value;
    
    //if posting JSON:
    let contentType = 'application/json';
    let reqBody = JSON.stringify({msg: document.getElementById("post-color-input").value})
    console.log(reqBody);

    await fetch (urlPost, {
        headers: {'Content-Type': contentType},
        method: 'POST', //or use "PUT"
        'body': reqBody
    })
    .then(res => {console.log(res.status)});

    document.getElementById("post-color-input").value = "";
}