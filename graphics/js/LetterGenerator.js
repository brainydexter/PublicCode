// Letter Generator code begins ******************
var LetterGenerator = function() 
{
	console.log('letter Generator instance created');

	this.N = 25;
};

// recreates the letters
LetterGenerator.prototype.generate = function() {
	var letterFrequency = [12, 1, 5, 6, 19, 4, 3, 5, 11, 1, 1, 5, 4, 11, 11, 4, 1, 12, 9, 13, 4, 1, 2, 1, 3, 1];

	var expandedLetters = [];
	var j = 0;

	for (var i = 0; i < letterFrequency.length; i++) { // i represents alphabet
		for (var letterCount = 0; letterCount < letterFrequency[i]; letterCount++) {
			// letterCount represents the frequency of aplhabet
			expandedLetters[j++] = String.fromCharCode(65 + i);
		};
	};

	shuffle(expandedLetters);

	this.letters = new Array(this.N);

	// pick 25 letters out of the shuffled lot
	for (var i = 0; i < this.N; i++) {
		this.letters[i] = expandedLetters[i];
	}

	this.lettersExtracted = 0; // every time letter is extracted, increment to 1
};

LetterGenerator.prototype.getNextLetter = function(){
	if(this.lettersExtracted == this.N - 1) { // all letters have been extracted. Regenerate
		this.generate();
	}

	return this.letters[this.lettersExtracted++];
};
// letter Generator code ends ******************

// http://stackoverflow.com/questions/2450954/how-to-randomize-shuffle-a-javascript-array
function shuffle(array) {
var currentIndex = array.length
  , temporaryValue
  , randomIndex
  ;

// While there remain elements to shuffle...
while (0 !== currentIndex) {

  // Pick a remaining element...
  randomIndex = Math.floor(Math.random() * currentIndex);
  currentIndex -= 1;

  // And swap it with the current element.
  temporaryValue = array[currentIndex];
  array[currentIndex] = array[randomIndex];
  array[randomIndex] = temporaryValue;
}

return array;
}