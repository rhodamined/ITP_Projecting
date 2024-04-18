const osc = new OSC({ plugin: new OSC.WebsocketServerPlugin() })
osc.open({ port: 9912 })




async function getDog() {
  console.log('DOG!!!');
  const message = new OSC.Message('/test/path', 521.25, 'teststring', 665);
  osc.send(message);
}


async function oscA() {
  console.log('A')
}

async function oscB() {
  console.log('B')
}

async function oscC() {
  console.log('C')
}
