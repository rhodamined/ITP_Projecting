async function getDog() {
    let endpoint = `/dog`;
    const res = await fetch(endpoint, {
        method: 'POST',
        headers: {
          'Content-Type': 'application/json',
        }
    });
    // console.log('dog');
    console.log(res);
}


async function oscA() {
    // console.log('A')

    let endpoint = `/a`;
    const res = await fetch(endpoint, {
        method: 'POST',
        headers: {
          'Content-Type': 'application/json',
        }
    });
    console.log(res);
}

async function oscB() {
    // console.log('B')

    let endpoint = `/a`;
    const res = await fetch(endpoint, {
        method: 'POST',
        headers: {
          'Content-Type': 'application/json',
        }
    });
    console.log(res);
}

async function oscC() {
    // console.log('C')

    let endpoint = `/a`;
    const res = await fetch(endpoint, {
        method: 'POST',
        headers: {
          'Content-Type': 'application/json',
        }
    });
    console.log(res);
}
  