var ScoreMgr = function(){
	console.log('ScoreMgr instance created');
}

ScoreMgr.prototype.init = function(){
	this.letterScore = [12, 1, 5, 6, 19, 4, 3, 5, 11, 1, 1, 5, 4, 11, 11, 4, 1, 12, 9, 13, 4, 1, 2, 1, 3, 1];
	for (var i = 0; i < this.letterScore.length; i++) {
		this.letterScore[i] = Math.floor((this.letterScore[i] * 100)/150);
		
		// inverting the score since it is based on frequency
		// reward for using less frequency letter
		this.letterScore[i] = 12 - this.letterScore[i];

		if(this.letterScore[i] == 0)
			this.letterScore[i] = 1;
	}

	this.totalScore = 0;

	this.divText = document.createElement('div');
	this.divText.style.position = 'absolute';
	this.divText.style.font = 'helvetica';
	// this.divText.style.backgroundColor = "white";
	this.divText.style.color = "green";
	this.divText.style.textAlign ="center";
	this.divText.style.verticalAlign = "middle";
	this.divText.style.fontWeight="bold";
	this.divText.style.fontSize="large";
	this.divText.style.top = 50 + 'px';
	this.divText.style.left = 10 + 'px';
	document.body.appendChild(this.divText);
};

ScoreMgr.prototype.destroy = function() {
	document.body.removeChild(this.divText); this.divText = null;
};

ScoreMgr.prototype.getLetterScore = function(alphabet){
	var index = alphabet.charCodeAt(0) - 65;

	if(index > 25){
		throw Error(alphabet + " not recognized");
	}

	return this.letterScore[index];
}

ScoreMgr.prototype.getScoreMultiplier = function(len){
	if(len <= 3) return 1;
	if(len <= 5) return 2;
	return 3;
};

ScoreMgr.prototype.addWord = function(word){
	 var score = 0;

	 for (var i = 0; i < word.length; i++) {
	 	score += this.getLetterScore(word[i]);
	 }

	 score *= this.getScoreMultiplier(word.length);

	 this.totalScore += score;

	 return score;
};

ScoreMgr.prototype.update = function(dt){
};

ScoreMgr.prototype.render = function(dt){
	this.divText.innerHTML = "SCORE: " + this.totalScore;
};