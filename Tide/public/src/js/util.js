// write custom hide video function
// because not loading p5 sound library
async function hideVideo() {
    console.log("hidevideo");
    let vids = document.getElementsByTagName("video");
    console.log(vids);
    // vids is an HTMLCollection
    for( var i = 0; i < vids.length; i++ ){ 
        console.log( vids.item(i).src );
        vids.item(i).classList.add("hide");
    }
}

// get timestamp in human legible format
function getTimestamp() {
    let date = new Date();
    return date.toLocaleTimeString();
}
