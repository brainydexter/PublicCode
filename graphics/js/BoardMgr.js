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
}

BoardMgr.prototype.update = function(dt) {
	if(this.activeBlock == null){
		this.activeBlock = this.getNextBlock();
	}

	// update active block as per keyboard input
	// left/right/falldown
	// else
	{
		this.move(this.activeBlock, DIRECTION.DOWN);
	}
};

BoardMgr.prototype.render = function(dt) {
	
};

BoardMgr.prototype.move = function(block, direction) {
	if(block.position.y < 320){
		block.position.y += 10;
	}else
	{
		this.activeBlock = null;
	}
	
};

BoardMgr.prototype.updateBoard = function() {
	
};

BoardMgr.prototype.getNextBlock = function(){
	var block = this.blocks[this.activeBlockIndex];
	this.activeBlockIndex = (this.activeBlockIndex + 1)% 25;
	block.visible = true;
	i = Math.floor((Math.random() * 10)) % 5;
	console.log("create block in " + i);
	block.position.x = (this.BLOCK_WIDTH/2) + ( (i) * this.BLOCK_WIDTH);
	block.position.y = (this.BLOCK_WIDTH/2);
	return block;
}