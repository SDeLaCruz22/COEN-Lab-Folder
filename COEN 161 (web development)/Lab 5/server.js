//cd '.\TempCoenFolder\C161\C161 Lab\Lab5\Lab5-Template\5-gif-saver\'  
//
// TASK 1A: What does the require function do?
const express = require('express') //we need the core module "express"
const fs = require('fs/promises') //we need
//require function is just loading modules

//
function getRanInt(min, max){
  return Math.floor(Math.random()*(max - min));
}

// TASK 1B: What are these two parameters and how do they work with express?
const getAllMoods = (req, res) => { //req(uest) has info about HTTP request that raissed this event, res(ponse) to send back HTTP response
  const allMoods = Object.keys(res.app.locals.reactions); //returns an array in whcih each index is the propery name of the object
  // TASK 1C: What does the res.status() function do? What allows this to be chained?
  res.status(200).send(allMoods);
  //it set the HTTP status for the response (like status 200, 404 etc), chainable alias of NOde's response.statusCode
};

const getAllGifs = (req, res) => { //retreive all gifs of every mood, return as an object. 
  //apply a suitable status code for the 3 situations: (can return a gif, mood not found, mood found but no content
  //When a user sends a GET request to /gifs, the server returns the entireres.app.locals.reactions object to the user as the following JSON object
  //When user send GET request to /gif/:mood, server returns link to random gif from array stored in res.app.locals.reactions[mood]
    //figure out how to express in terms of express.js
    //json obj should look like ("gif": "link1")
  const allGifs = res.app.locals.reactions; //res.app.locals.reactions is the object inside gifs.json, the entire file
  res.status(200).send(allGifs);
};

const getMoodGif = (req, res) =>{ //retreives a gif from a specific mood. You might want to use a console. log here
  //server returns the link to a random gif from array stored under res.app.locals.reactions[mood]
  //should look like ('gif': "link1")
  //the curl request will be /gif/happy
  //console.log(req.params); //this will show what mood the user has put in
  let mood = req.params.mood; //req.params will give us (mood: typedmoood), we jsut want the typed in mood from the curl request, .mood is the property
  ///console.log(mood);
  let moodArray = res.app.locals.reactions[mood];
  let RandLink = moodArray[getRanInt(0, 3)];
  //console.log(RandLink);
  res.status(200).send(RandLink);
}

const postMood = (req, res) => { //adds a new mood thingy
  console.log("hello");
  let mood = req.params.mood;
  console.log(mood);
  let gifsObject = res.app.locals.reactions;

  if(gifsObject[mood]) return res.sendStatus(400); //invalid since the mood is already there
  
  //to add a property into an object, give it a value
  gifsObject[mood] = []; //give the mood an array
  console.log(gifsObject[mood]);
  return res.sendStatus(201);
}

const postMoodGif = (req, res) => { //adds a new gif to a specific mood
  console.log("hello");
  let mood = req.params.mood;
  let gifsObject = res.app.locals.reactions;
  let link = req.body.link;

  if(!gifsObject[mood]) return res.sendStatus(404); //mood doesnt exist
  if(!link) return res.sendStatus(400); //no link provided

  gifsObject[mood].push(link); //push the link into the mood array
  console.log(gifsObject[mood]);
  return res.sendStatus(201); //look for specific status, not 200
}

/*
to test post here
curl -Method Post -Header @{'content-type'= 'application/json'} -Body @{link = 'https://media.giphy.com/media/13k4VSc3ngLPUY/giphy.gif'} -Uri http://localhost:3000/gif/happy

$body = @{
    link = “giphy-link”
}
Invoke-RestMethod -Method 'Post' -Uri $uri  -ContentType 'application/json' -Body ($body | ConvertTo-Json);

*/

const deleteMood = (req, res) => { //deletes a mood
  let gifsObject = res.app.locals.reactions;
  let mood = req.params.mood;
  let moodArray = gifsObject[mood];

  if(!moodArray) return res.sendStatus(400);

  //delete moodArray; <-- will only delte teh object
  delete res.app.locals.reactions[req.params.mood];

  console.log(gifsObject);
  res.sendStatus(204);
}

const deleteMoodGif = (req, res) => { //deletes the link if found
  let mood = req.params.mood; 
  let gifsObject = res.app.locals.reactions;
  let moodArray = gifsObject[mood];

  console.log(req.body);
  console.log(req.body.link);
  console.log(moodArray);
  
  if(!req.body.link) return res.sendStatus(400);
  if(!moodArray) return res.sendStatus(404);

  let deleteLink = moodArray.filter(link => link !== req.body.link);
  res.app.locals.reactions[req.params.mood] = deleteLink; //see line 90

  console.log(gifsObject);
  res.sendStatus(204);
}

/* curl -H "content-type: application/json" -X DELETE --data '{"link": "https://media.giphy.com/media/9Y6n9TR7U07ew/giphy.gif" }' localhost:3000/gif/happy */
//should delete the middle line of happy

/*
for delete

*/

const main = () => {
  const app = express();
  const port = 3000;

  // TASK 1D: What does this line do?
  app.use(express.json()); //something about binding middleware (this json)

  // TASK 1E: What does this line do?
  app.get("/moods", getAllMoods); //routes the HTTP GET requests to /moods with getAllMoods 
  app.get("/gif", getAllGifs);
  app.get("/gif/:mood", getMoodGif);

  app.post("/mood", postMood);
  app.post("/gif/:mood", postMoodGif);

  app.delete("/mood", deleteMood);
  app.delete("/gif/:mood", deleteMoodGif);

  fs.readFile("./gifs.json", "utf-8") //what is this
    .then((fileContents) => JSON.parse(fileContents))
    .then((data) => {
      // TASK 1F: What is the locals property in on the app object?
      app.locals.reactions = data; //locals is an object that has properties that are local variables of app

      // TASK 1G: What does this do?
      app.listen(port, () => { //listens for a port of 3000 to do something
        console.log(`Reaction gifs started on http://localhost:${port}`);
      });
    });
};

main();
