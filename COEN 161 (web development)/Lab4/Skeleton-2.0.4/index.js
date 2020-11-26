
const PrevButton = document.getElementById('PrevButton');
//console.log(PrevButton);
const RandButton = document.getElementById('RandomButton');
//console.log(RandButton);
const NextButton = document.getElementById('NextButton');





function SpecificComic(ComicNum){
    //console.log("WELCOME TO SPECIFCI COMIC FUNCTION");
    //console.log(typeof ComicNum);

    const SampString ="Sample";
    if(typeof ComicNum != typeof SampString)
        ComicNum = ComicNum.toString();
    
    let JsonString = "https://xkcd.now.sh/?comic="; //https://xkcd.com/614/info.0.json ,,, https://xkcd.now.sh/614
    //new fetch URl
    JsonString += ComicNum;
    //JsonString += "/info.0.json";
    //console.log(JsonString);

    fetch(JsonString)
        .then(response => {
            //console.log("WE FETCH");
            return response.ok ? response.json() : Promise.reject()
        })

        .then( data => { 
            //console.log(data); //you can see the info in the console
            let header = document.querySelector('h1');
            document.getElementById('comicImage').src = data.img; //dunno why the img aint changing
            header.innerText = data.title;
            var urlParams = new URLSearchParams(window.location.search);
            urlParams.set('issue', data.num);
        });
    //urlParams.set(‘comic', num); 
    //do a fetch
    //change the img and stuff like in fetch latest
}

function PrevButtonClicked(){
    //console.log("holy fucking shit please read this");
    //use query param to get the num comic
    //number it
    let ComicNum = GetQueryNum();
    ComicNum = parseInt(ComicNum, 10);
    //make sure its not the first comic
    if(ComicNum === 1)
        return;
    // decrease it by 1
    ComicNum -= 1;
    SpecificComic(ComicNum);
}

function NextButtonClicked(){
    //console.log("holy fucking shit please read this");
    //use query param to get the num comic
    let ComicNum = GetQueryNum();
    ComicNum = parseInt(ComicNum, 10);
    //make sure its not last comic
    if(ComicNum === 2000)
        return;
    //increase by 1
    ComicNum += 1;
    SpecificComic(ComicNum);
}

function RandButtonClicked(){
    //console.log("holy fucking shit please read this");
    let RandComic = Math.floor(Math.random()*2000)+1;
    SpecificComic(RandComic);
}

function GetQueryNum(){
    //console.log("Query param true");
    var urlParams = new URLSearchParams(window.location.search);
    let ParamString = urlParams.toString();
    //console.log(ParamString);
    let ComicNum = ParamString.substring(6,10);
    if(ParamString === '')
        return "2000"; //the code works under the assumption that the latest is 2000
    //console.log(ComicNum);
    return ComicNum;
}

window.onload = function() {
    //if query parameter
    PrevButton.addEventListener('click', () => { PrevButtonClicked() } );
    RandButton.addEventListener("click", RandButtonClicked);
    NextButton.addEventListener('click', () => { NextButtonClicked() } );
    var urlParams = new URLSearchParams(window.location.search);
    ////console.log(urlParams.toString());
    if(urlParams.has("issue")){
        SpecificComic(GetQueryNum());
    }
    else{
    fetch('https://xkcd.now.sh?comic=latest')
        .then(response => {
            return response.ok ? response.json() : Promise.reject()
        })

        .then( data => { 
            //console.log(data); //you can see the info in the console
            let header = document.querySelector('h1');
            //let imageSrc = 
            //console.log(typeof data.img);
            document.getElementById('comicImage').src = data.img; //dunno why the img aint changing
            ////console.log(imageSrc);
            header.innerText = data.title;
        });
    }
};

