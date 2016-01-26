function Utility () {}

Utility.getRandomInt = function(min, max){
	return Math.floor(Math.random() * (max - min)) + min;
}