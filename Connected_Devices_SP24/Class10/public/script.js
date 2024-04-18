//can be found in config.js
//assemble URL (or just manually type it here)
const urlroot = `http://${serverIP}:${port}`;

let counter = 0;

async function postData() {
    console.log("postData");
    
    //if posting JSON:
    let contentType = 'application/json';
    let reqBody = JSON.stringify({msg: document.getElementById("post-data-input").value})
    console.log(reqBody);

    let url = urlroot + "/data";

    await fetch (url, {
        headers: {'Content-Type': contentType},
        method: 'POST', //or use "PUT"
        'body': reqBody
    })
    .then(res => {console.log(res.status)});

    document.getElementById("post-data-input").value = "";
}

// constantly run postTimestamp on 2 second intervals
(async function () {
	setInterval(async function () {
        postTimestamp();
	}, 2000);
})();

async function postTimestamp() {
    
    const currentDate = new Date(); 
    const ts = currentDate.getTime();

    //if posting JSON:
    let contentType = 'application/json';
    // let reqBody = JSON.stringify({msg: ts});
    let reqBody = JSON.stringify({msg: counter});
    console.log(reqBody);

    let endpoint = "/data";
    let deviceID = 1;
    let url = `${urlroot}${endpoint}?deviceID=${deviceID}`;
    console.log(url);

    await fetch (url, {
        headers: {'Content-Type': contentType},
        method: 'POST', //or use "PUT"
        'body': reqBody
    })
    .then(res => {console.log(res.status)});

    counter++;

}
