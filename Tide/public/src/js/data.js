// API calls to get wind data, tide data

let dat = {
    update_ts: "",
    tide_ts: "",
    tide_lvl: "",
    wind_ts: "",
    wind_spd: "",
    wind_dir: ""
}


async function updateData() {

    // get tide data 
    const tide_dat = await getTideData();

    const wind_dat = await getWindData();

    console.log(tide_dat);
    console.log(wind_dat);

    displayData();

}

// NOAA Tidal Data updates every 6 minutes
async function getTideData() {

    // Website: https://tidesandcurrents.noaa.gov/stationhome.html?id=8518750
    // API: https://api.tidesandcurrents.noaa.gov/api/prod/
    const res = await fetch(tide_url); //make the request
    const body = await res.json();
    // console.log(body);

    // update closure var
    dat.update_ts = getTimestamp();
    dat.tide_ts = body.data[0].t;
    dat.tide_lvl = body.data[0].v;

    return body;
}

// OpenWeatherAPI updates every 10 minutes
async function getWindData() {

    const res = await fetch(ow_url); //make the request
    const body = await res.json();
    // console.log(body);

    ts = new Date(body.dt * 1000);
    ts = ts.toLocaleString();
    dat.wind_ts = ts;
    dat.wind_spd = body.wind.speed;
    dat.wind_dir = body.wind.deg;

    return body;
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

    
