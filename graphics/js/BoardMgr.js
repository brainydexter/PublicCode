// Letter Generator code begins ******************
var letterGenerator = function() 
{
	console.log('letter Generator instance created');
};

letterGenerator.prototype.getNextLetter = function(){
	return 'a';
};
// letter Generator code ends ******************

// Board Manager code begins ******************
var DIRECTION = {"LEFT":1, "RIGHT":2, "DOWN":3}

var BoardMgr = function(scene)
{
	console.log("Board Manager instance created");
	this.activeBlock = null;

	this.BLOCK_WIDTH = 40;
	rows = 5;
	columns = 5;

	var geometry = new THREE.BoxGeometry( this.BLOCK_WIDTH, this.BLOCK_WIDTH, 4 );
	var material = new THREE.MeshBasicMaterial( { color: 0x00ff00 } );

	this.blocks = [];

	for (var i = 0; i < rows * columns; i++) {
		cube = new THREE.Mesh( geometry, material );
		cube.visible = false;
		this.blocks[i] = cube;

		scene.add( this.blocks[i] );
	};

	this.activeBlockIndex = 0;

	// creating the board
	this.board = new Array(rows);
	for (var i = 0; i < this.board.length; i++) {
		this.board[i] = new Array(columns);
	};

	// initializing the board
	for (var r = 0; r < rows; r++) {
		for(var c = 0; c < columns; c++)
		this.board[r][c] = null;
	};
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
			this.blocks[i].position.x = (this.BLOCK_WIDTH/2) + ( this.blocks[i].boardPosition.x * this.BLOCK_WIDTH);
			this.blocks[i].position.y = (this.BLOCK_WIDTH/2) + ( this.blocks[i].boardPosition.y * this.BLOCK_WIDTH);
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
	if(newPosition.x < 0 || newPosition.x >= 5 ) toMove = false;
	if(newPosition.y < 0 || newPosition.y >= 5 ) toMove = false;
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
	if(this.activeBlockIndex < 24)
	{
		i = Math.floor((Math.random() * 10)) % 5;
		// check if this.board[i][0] 
		// is empty: put the block there
		// else no more space in this column to put letter: game over
		if(this.board[i][0] != null) // game over
		{
			var text2 = document.createElement('div');
			text2.style.position = 'absolute';
			//text2.style.zIndex = 1;    // if you still don't see the label, try uncommenting this
			text2.style.width = 100;
			text2.style.height = 100;
			text2.style.backgroundColor = "red";
			text2.style.textAlign ="center"
			text2.style.fontWeight="bold"
			text2.style.fontSize="large"
			text2.innerHTML = "Game Over!";
			text2.style.top = 300 + 'px';
			text2.style.left = 400 + 'px';
			document.body.appendChild(text2);
		}

		console.log("create block in " + i);

		var block = this.blocks[this.activeBlockIndex];
		this.activeBlockIndex = (this.activeBlockIndex + 1) % 25;
		block.visible = true;
		

		block.boardPosition = new THREE.Vector2( i, 0 );
		this.board[block.boardPosition.x][block.boardPosition.y] = block;

		block.letter = 'a' + this.activeBlockIndex;
		return block;
	}

	return null;
}