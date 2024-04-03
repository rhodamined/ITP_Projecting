//can be found in config.js
//assemble URL (or just manually type it here)
const urlPost = `http://${serverIP}:${port}${endpointPOST}`;
const urlGet = `http://${serverIP}:${port}${endpointGET}`;

console.log(urlGet);

//if your endpoint responds with plain text:
// function getColors() {
//     fetch(url)
//         .then(res => res.text())
//         .then(text => {
//             //do stuff with text here                        
//         }
//     );
// }

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