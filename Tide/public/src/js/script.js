// need to adjust this to GET from arduino what speed is at init
let slider = document.getElementById("motor_spd_slider");
let output = document.getElementById("motor_spd_val");
output.innerHTML = slider.value;

slider.oninput = async function() {
    await sendSpd(this.value);
    output.innerHTML = this.value;
}

async function sendCWVal() {
    // console.log("cw button");
    sendDir(1); 
}

async function sendCCWVal() {
    // console.log("ccw button");
    sendDir(0);
}


// let dat = {
//     update_ts: "",
//     tide_ts: "",
//     tide_level: "",
//     wind_spd: "",
//     wind_dir: ""
// }

async function displayData() {
    document.getElementById("ts_val").innerHTML = dat.update_ts;
    document.getElementById("tide_ts_val").innerHTML = dat.tide_ts;
    document.getElementById("tide_lvl_val").innerHTML = dat.tide_lvl;
    document.getElementById("wind_ts_val").innerHTML = dat.wind_ts;
    document.getElementById("wind_spd_val").innerHTML = dat.wind_spd;
    document.getElementById("wind_dir_val").innerHTML = dat.wind_dir;
}