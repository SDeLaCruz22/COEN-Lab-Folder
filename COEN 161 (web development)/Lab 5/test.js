const fetch = require('node-fetch');
const data = {link: 'https://media.giphy.com/media/13k4VSc3ngLPUY/giphy.gif'};
//object literal - defines an object
//to define property, key: value

fetch("http://localhost:3000/gif/happy", {
    method: 'POST', //chagne to delete
    headers: {
        'Content-Type': 'application/json',
    },
    body: JSON.stringify(data),
})
.then(response => console.log(response.status))

