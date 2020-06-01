// server.js

// BASE SETUP
// =============================================================================

// call the packages we need
var express    = require('express');        // call express
var app        = express();                 // define our app using express
var bodyParser = require('body-parser');

//configuration of influxdb
var Influx = require('influxdb-nodejs');
var client = new Influx('http://127.0.0.1:8086/aTimeSeries');


// configure app to use bodyParser()
// this will let us get the data from a POST
app.use(bodyParser.urlencoded({ extended: true }));
app.use(bodyParser.json());

var port = process.env.PORT || 8080;        // set our port

// ROUTES FOR OUR API
// =============================================================================
var router = express.Router();              // get an instance of the express Router

router.use(function(req, res, next) {
console.log('API request happening from ' + req.ip);

res.header("Access-Control-Allow-Origin", "*");
res.header("Access-Control-Allow-Headers", "Origin, X-Requested-With, Content-Type, Accept, authorization");
next();
});
// test route to make sure everything is working (accessed at GET http://localhost:8080/api)

router.get('/', function(req, res) {
  client.queryRaw('select * from "valeurs" group by * order by desc limit 10')
    .then((data) => {
	time = Date.parse(data.results[0].series[0].values[0][0]);
  	valeur = data.results[0].series[0].values[0][1];
/*
	for(var i = 1; i < 10; i++){
  		time += Date.parse(data.results[0].series[0].values[i][0]);
  		valeur += data.results[0].series[0].values[i][1];

  		console.info("[" + time + "," + valeur + "]");
	}
*/
	console.info("[" + time + "," + valeur + "]");
      var array = new Array(time,valeur);
      res.json(array);
    }).catch(console.error);

});
router.get('/autre', function(req, res) {
  client.queryRaw('select * from "autre" group by * order by desc limit 1')
    .then((data) => {
  		timeAutre = Date.parse(data.results[0].series[0].values[0][0]);
  		valeurAutre = data.results[0].series[0].values[0][1];

  		console.info("[" + timeAutre + "," + valeurAutre + "]");
      var array = new Array(timeAutre,valeurAutre);
      res.json(array);
    }).catch(console.error);

});
// REGISTER OUR ROUTES -------------------------------
// all of our routes will be prefixed with /api
app.use('/api', router);

// START THE SERVER
// =============================================================================
app.listen(port);
console.log('Magic happens on port ' + port);
