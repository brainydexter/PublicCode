// Game code begins
var game = function()
{
	console.log('game instance created');
}

game.prototype.init = function(){
	this.keyboard = new KeyboardState();

	Constants.updateConsts(window.innerWidth, window.innerHeight);

	this.scene = new THREE.Scene();

	this.camera = new THREE.OrthographicCamera( 0, Constants.WIDTH, 0, Constants.HEIGHT, -10, 1000 );
	this.camera.position.set(0, 0, 100);
	this.camera.lookAt(new THREE.Vector3( 0, 0, 0 ));
	this.scene.add(this.camera);

	this.renderer = new THREE.WebGLRenderer();
	this.renderer.setSize( Constants.WIDTH, Constants.HEIGHT );
	document.body.appendChild( this.renderer.domElement );

	// var NxN = 5;
	// var geometry = new THREE.BoxGeometry( Constants.BLOCK_WIDTH, Constants.BLOCK_WIDTH, 4 );
	// var material = new THREE.MeshBasicMaterial( { color: 0x00ff00 } );
	
	// var cube2 = new THREE.Mesh( geometry, new THREE.MeshBasicMaterial( { color: 0xFF0000} ));
	// cube2.position.set(650, 300, 0);
	// this.scene.add(cube2);

	// this.cube = new THREE.Mesh( geometry, material );
	// this.cube.position.set(WIDTH/2, HEIGHT/2, 1);
	// this.scene.add( this.cube );
	this.boardMgr = new BoardMgr(this.scene);

	this.wordMgr = new WordMgr();
	this.wordMgr.init();

	this.scoreMgr = new ScoreMgr();
	this.scoreMgr.init();

	// when the mouse moves, call the given function
	document.addEventListener( 'click', onDocumentMouseDown, false );

	window.addEventListener('resize', function () {
		Constants.updateConsts(window.innerWidth, window.innerHeight);

		game.camera.left = 0;
		game.camera.right = Constants.WIDTH;
		game.camera.top = 0;
		game.camera.bottom = Constants.HEIGHT;
		game.camera.updateProjectionMatrix();

	    game.renderer.setSize(Constants.WIDTH, Constants.HEIGHT);
	});

};

function onDocumentMouseDown( event ) {
	/*
	- click
	 - if intersects with block:
	  - if active block:
	  	- fall down
	  	- clear word
	  - else select block:
	   - if same block is selected twice, ignore it
	   - if block is adjacent to top of the block, add block to current word
	 - else (does not intersect with block)
	  - clear word
	  - click relative to block ?
	  - move left, right, fall down
	 */
	
	/*
	Testing criterion:
	- same block cannot be selected twice
	- only adjacent blocks can be added
	- 1 block can only be used once in the word 
	 */
  console.log("Click");

	var mouse = new THREE.Vector2();
	mouse.x = ( (event.clientX - game.renderer.domElement.offsetLeft) / game.renderer.domElement.width ) * 2 - 1;
	mouse.y = -( (event.clientY - game.renderer.domElement.offsetTop) / game.renderer.domElement.height ) * 2 + 1;

	//mouse.x = (event.clientX / window.innerWidth) * 2 - 1;
	//mouse.y = -(event.clientY / window.innerHeight) * 2 + 1;

  var raycaster = new THREE.Raycaster();
  // update the picking ray with the camera and mouse position	
  raycaster.setFromCamera(mouse, game.camera);

  // calculate objects intersecting the picking ray
  var intersects = raycaster.intersectObjects(game.scene.children);

  if(intersects.length > 0) {
  	var block = intersects[0].object;
  	if(block != game.boardMgr.activeBlock)
  	{
  		var addWord = true;
  		if(game.wordMgr.activeWord.length > 0) {
  			// do not add if the new selected block is the same as the block that is at top of the word
  			// or it has been used before in the word
  			
  			addWord = !(game.wordMgr.activeWordContains(block));
  			
  			// do not add if the new selected block is not adjacent to the top of the word
  			var topBlockPosition = new THREE.Vector3( game.wordMgr.activeWord[game.wordMgr.activeWord.length - 1].boardPosition.x, game.wordMgr.activeWord[game.wordMgr.activeWord.length - 1].boardPosition.y, 0 );
  			topBlockPosition.sub(block.boardPosition);
  			topBlockPosition.z = 0; //ignoring z
  			if(topBlockPosition.lengthSq() > 2){
  				addWord = false;
  			}
  		}

  		if(addWord) game.wordMgr.addBlock(block);
  	}
  	else // selected block is active block
  	{
  		// make the active block fall down
  		// // clear word
  		game.wordMgr.clearActiveWord();
  	}
  }
  else { // nothing intersected with the block
  	// clear the word
  	game.wordMgr.clearActiveWord();

  	// move the falling block w.r.t click
  	// find if the activeBlock is right or left wrt click
  	// Three.js is right handed coordinate system
  	// ray cast into screen is along -z (0, 0, -1)
  	// we can figure out vector direction of the falling block: activeBlock.position - ray.origin
  	// crossProduct(rayDirection, vectorDirection) will yield a normal vector in up or down direction
  	// if up, block is to the left of ray
  	// down => block is to right of ray
  	var blockDirection = new THREE.Vector3();
  	blockDirection.subVectors(game.boardMgr.activeBlock.position, raycaster.ray.origin);
  	var normal = new THREE.Vector3();
  	normal.crossVectors(raycaster.ray.direction, blockDirection);

  	if(normal.y > 0) { // block is left of ray => click is right to box => move block right
  		game.boardMgr.move(game.boardMgr.activeBlock, DIRECTION.RIGHT);
  	}
  	else {
  		game.boardMgr.move(game.boardMgr.activeBlock, DIRECTION.LEFT);
  	}
  }

  console.log("intersects: " + intersects.length);
  for (var i = 0; i < intersects.length; i++) {
    console.log(intersects[i].object.letter.value);
  }
}

game.prototype.update = function(dt){
	// console.log('Time elapsed: ' + dt);
	// console.log('next letter: ' + this.letterGen.getNextLetter());

	this.keyboard.update();
	
	this.boardMgr.update(dt);
	this.scoreMgr.update(dt);
};

var lag = 0;
var factor  = 1;
var sign = 1;
game.prototype.render = function(){
	var now = new Date().getTime();
	var dt = now - (time || now);
	lag += dt;

	if(lag > 300/factor)
	{
		this.update(dt);
		lag = 0;

		// if increasing and crossed threshold
		if(sign == 1 && factor > 2){
			sign = -1; // decrease
		}else if(sign == -1 && factor < 1.1){ // if decreasing and fell below threshold
			sign = 1; // increase
		}

		factor += (sign * 0.003);
	}

	this.boardMgr.render(dt);
	this.wordMgr.render(dt);
	this.scoreMgr.render(dt);
	this.renderer.render(this.scene, this.camera);

	time = now;
	var thisObj = this;

	requestAnimationFrame( function() {thisObj.render();} );
};

game.prototype.destroy = function() {
	this.keyboard.destroy();
};
// Game code ends