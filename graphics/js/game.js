// Letter Generator code begins ******************
var letterGenerator = function() 
{
	console.log('letter Generator instance created');
};

letterGenerator.prototype.getNextLetter = function(){
	return 'a';
};
// letter Generator code ends ******************

// Game code begins
var game = function()
{
	console.log('game instance created');
}

game.prototype.init = function(){
	  this.letterGen = new letterGenerator();
};

game.prototype.update = function(){
	console.log('next letter: ' + this.letterGen.getNextLetter());
};

game.prototype.render = function(){
};
// Game code ends