

// Board Manager code begins ******************
var DIRECTION = {"LEFT":1, "RIGHT":2, "DOWN":3}

var BoardMgr = function(scene)
{
	console.log("Board Manager instance created");
	this.activeBlock = null;

	var geometry = new THREE.BoxGeometry( Constants.BLOCK_WIDTH, Constants.BLOCK_WIDTH, 4 );
	var material = new THREE.MeshBasicMaterial( { color: 0xffffff } );

	this.blocks = [];
	this.NUM_BLOCKS = Constants.NUM_ROWS * Constants.NUM_COLUMNS;

	for (var i = 0; i < this.NUM_BLOCKS; i++) {
		cube = new THREE.Mesh( geometry, material );
		cube.visible = false;
		this.blocks[i] = cube;

		scene.add( this.blocks[i] );
	};

	this.activeBlockIndex = 0;

	// creating the board
	this.board = new Array(Constants.NUM_COLUMNS);
	for (var i = 0; i < this.board.length; i++) {
		this.board[i] = new Array(Constants.NUM_ROWS);
	};

	// initializing the board
	for (var r = 0; r < Constants.NUM_COLUMNS; r++) {
		for(var c = 0; c < Constants.NUM_ROWS; c++)
		this.board[r][c] = null;
	};

	this.letterGenerator = new LetterGenerator();
	this.letterGenerator.generate();
}

BoardMgr.prototype.update = function(dt) {
	if(this.activeBlock == null){
		this.activeBlock = this.getNextBlock();
		//console.log("letter: " + this.activeBlock.letter);
	}

	// update active block as per keyboard input
	// left/right/falldown
	// else
	{
		this.move(this.activeBlock, DIRECTION.DOWN);
	}
};

BoardMgr.prototype.render = function(dt) {
	for (var i = 0; i < this.blocks.length; i++) {
		if(this.blocks[i].visible)
		{
			this.blocks[i].position.x = 300 + (Constants.BLOCK_WIDTH/2) + ( this.blocks[i].boardPosition.x * Constants.BLOCK_WIDTH);
			this.blocks[i].position.y = (Constants.BLOCK_WIDTH/2) + ( this.blocks[i].boardPosition.y * Constants.BLOCK_WIDTH);
			this.blocks[i].position.z = 0;

			this.blocks[i].letter.divElem.style.top = this.blocks[i].position.y - (Constants.BLOCK_WIDTH/2);
			this.blocks[i].letter.divElem.style.left = this.blocks[i].position.x - (Constants.BLOCK_WIDTH/2);
		}
	};
};

var convertDirectionToVector = function (DIRECTION) {
	
	switch(DIRECTION)
	{
		case DIRECTION.LEFT: return new THREE.Vector2( -1, 0 );
		case DIRECTION.RIGHT: return new THREE.Vector2( 1, 0 );
		case DIRECTION.DOWN: 
		default: return new THREE.Vector2( 0, 1 );
	}
}

BoardMgr.prototype.move = function(block, DIRECTION) {
	var newPosition = convertDirectionToVector(DIRECTION).add(block.boardPosition);

	var toMove = true;
	if(newPosition.x < 0 || newPosition.x >= Constants.NUM_COLUMNS ) toMove = false;
	if(newPosition.y < 0 || newPosition.y >= Constants.NUM_ROWS ) toMove = false;
	if(this.board[newPosition.x][newPosition.y] != null) toMove = false; // block already exists at the new position

	if(toMove)
	{
		this.board[block.boardPosition.x][block.boardPosition.y] = null; // vacating currect block
		block.boardPosition.copy(newPosition);
		this.board[block.boardPosition.x][block.boardPosition.y] = block; // occupying block at the new position
	}
	else
	{
		this.activeBlock = null; // time to spawn a new block
	}
	
};

BoardMgr.prototype.updateBoard = function() {
	
};

BoardMgr.prototype.getNextBlock = function(){
	var gameOver = false;

	// if any of the blocks reached the top (row 0) => game over
	for (var x = 0; x < Constants.NUM_COLUMNS; x++) {
		if (this.board[x][0] != null) // block found in top row=> y = 0
			gameOver = true;
	};

	if(gameOver)
	{
		var text2 = document.createElement('div');
		text2.style.position = 'absolute';
		//text2.style.zIndex = 1;    // if you still don't see the label, try uncommenting this
		text2.style.width = 100;
		text2.style.height = 50;
		text2.style.backgroundColor = "red";
		text2.style.textAlign ="center"
		text2.style.fontWeight="bold"
		text2.style.fontSize="large"
		text2.innerHTML = "Game Over!";
		text2.style.top = 100 + 'px';
		text2.style.left = 700 + 'px';
		document.body.appendChild(text2);
	}
	else
	{
		var i = Utility.getRandomInt(0, Constants.NUM_COLUMNS);

		console.log("create block in " + i);

		var block = this.blocks[this.activeBlockIndex];
		this.activeBlockIndex = (this.activeBlockIndex + 1) % this.NUM_BLOCKS;
		block.visible = true;
		

		block.boardPosition = new THREE.Vector2( i, 0 );
		block.letter = createLetter(this.letterGenerator.getNextLetter(), Constants.BLOCK_WIDTH);

		this.board[block.boardPosition.x][block.boardPosition.y] = block;
		return block;
	}

	return null;
}

var createLetter = function(alphabet, width){
	
	var text2 = document.createElement('div');
	text2.style.position = 'absolute';
	text2.style.width = width;
	text2.style.height = width;
	// text2.style.backgroundColor = "white";
	text2.style.color = "orange";
	text2.style.textAlign ="center";
	text2.style.verticalAlign = "middle";
	text2.style.fontWeight="bold";
	text2.style.fontSize="large";
	text2.innerHTML = alphabet;
	document.body.appendChild(text2);

	return {
		value: alphabet,
		divElem: text2
	};
}