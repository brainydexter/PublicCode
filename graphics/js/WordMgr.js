var WordMgr = function(){
	console.log('WordMgr instance created');
}

WordMgr.prototype.init = function(){
	this.activeWord = []; // word being formed actively

	this.dictionary = new Typo("en_us");
	// var found = dictionary.check("Hello");
	
	var submitWordDiv = document.createElement('div');
	submitWordDiv.style.position = 'absolute';
	submitWordDiv.style.width = 100;
	submitWordDiv.style.height = 100;
	submitWordDiv.style.top = 200 + 'px';
	submitWordDiv.style.left = 700 + 'px';
	document.body.appendChild(submitWordDiv);

	var submitWordButton = document.createElement("input");
	submitWordButton.type = "button";
	submitWordButton.value = "submit word";

	var thisObj = this;
	submitWordButton.onclick = function(){
		thisObj.handleWordSubmit();
	};

	submitWordDiv.appendChild(submitWordButton);

	this.divText = document.createElement('div');
	this.divText.style.position = 'absolute';
	this.divText.style.width = 100;
	this.divText.style.height = 100;
	this.divText.style.backgroundColor = "white";
	this.divText.style.color = "orange";
	this.divText.style.textAlign ="center";
	this.divText.style.verticalAlign = "middle";
	this.divText.style.fontWeight="bold";
	this.divText.style.fontSize="large";
	this.divText.style.top = 500 + 'px';
	this.divText.style.left = 700 + 'px';
	document.body.appendChild(this.divText);  
	
};

WordMgr.prototype.destroy = function(){
	this.clearActiveWord();
};

WordMgr.prototype.handleWordSubmit = function() {
	console.log('handle submit word click');

	event.stopPropagation(); // this event should be handled here itself and not affect anything else

	// find word from this.activeWord
	// check if the word.len > 3 && exists in dictionary
	// if true: 
	// 	- add to list of words made
	// 	- update score
	// 	- update boardMgr by removing these words from board
	// 	- clear activeWord
	// else
	//  - signal word does not exist in dictionary
	// clear this.activeWord
	if(this.activeWord.length >= 3 &&  this.dictionary.check(this.activeWordStr())){
		console.log('This is a good word')
		// add to list of words made
		// update score
		// update BoardMgr
		game.boardMgr.handleWordSubmit(this.activeWord);
	}
	else{
		// word does not exist in dictionary
	}
	this.clearActiveWord(); 
}

// returns true if the activeWord already contains the input block
WordMgr.prototype.activeWordContains = function(block){
	 
	 for (var i = 0; i < this.activeWord.length; i++) {
			if (this.activeWord[i] == block){ // block has been repeated earlier
				return true;
		}
	};

	 return false;
};

// add block to active word
WordMgr.prototype.addBlock = function(block){
	if(!block)
		console.log('trying to add a null block');
	this.activeWord.push(block);
}

WordMgr.prototype.clearActiveWord = function(){
	this.activeWord = [];
}

WordMgr.prototype.activeWordStr = function(){
	var chars = ""

	for (var i = 0; i < this.activeWord.length; i++) {
		if(!this.activeWord[i])
			console.log('dereferenced null block');
		chars += this.activeWord[i].letter.value;
	};

	return chars;
}

WordMgr.prototype.render = function(dt){
	this.divText.innerHTML =  this.activeWordStr();
};