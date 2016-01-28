// Game code begins
var game = function()
{
	console.log('game instance created');
}

game.prototype.init = function(){
	this.keyboard = new KeyboardState();

	var WIDTH = 800;
	var HEIGHT = 600;

	this.scene = new THREE.Scene();

	this.camera = new THREE.OrthographicCamera( 0, WIDTH, 0, HEIGHT, -10, 1000 );
	this.camera.position.set(0, 0, 100);
	this.camera.lookAt(new THREE.Vector3( 0, 0, 0 ));
	this.scene.add(this.camera);

	this.renderer = new THREE.WebGLRenderer();
	this.renderer.setSize( WIDTH, HEIGHT );
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

	// when the mouse moves, call the given function
	document.addEventListener( 'mousedown', onDocumentMouseDown, false );
};

var word = []
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
  		if(word.length > 0) {
  			// do not add if the new selected block is the same as the block that is at top of the word
  			// or it has been used before in the word
  			for (var i = 0; i < word.length; i++) {
  				if (word[i] == block){ // block has been repeated earlier
  					addWord = false;
  			}
  			};

  			// do not add if the new selected block is not adjacent to the top of the word
  			var topBlockPosition = new THREE.Vector3( word[word.length - 1].boardPosition.x, word[word.length - 1].boardPosition.y, 0 );
  			topBlockPosition.sub(block.boardPosition);
  			topBlockPosition.z = 0; //ignoring z
  			if(topBlockPosition.lengthSq() > 2){
  				addWord = false;
  			}
  		}

  		if(addWord) word.push(block);
  	}
  	else // selected block is active block
  	{
  		// make the active block fall down
  		// // clear word
  		word = [];
  	}
  }
  else { // nothing intersected with the block
  	// clear the word
  	word = [];

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

  var text4 = document.createElement('div');
	text4.style.position = 'absolute';
	text4.style.width = 100;
	text4.style.height = 100;
	text4.style.backgroundColor = "white";
	text4.style.color = "orange";
	text4.style.textAlign ="center";
	text4.style.verticalAlign = "middle";
	text4.style.fontWeight="bold";
	text4.style.fontSize="large"
	// text4.innerHTML = "screenX: " + event.screenX + " screenY: " + event.screenY ;
	// var k = "intersects: " + intersects.length;
	// if(intersects.length > 0)
	// 	k += " " + intersects[0].object.letter.value;
	text4.innerHTML =  toStr(word); 
	text4.style.top = 500 + 'px';
	text4.style.left = 700 + 'px';
	document.body.appendChild(text4);
}

game.prototype.update = function(dt){
	// console.log('Time elapsed: ' + dt);
	// console.log('next letter: ' + this.letterGen.getNextLetter());

	this.keyboard.update();

	// if(this.keyboard.down("left"))
	// {
	// 	console.log("eft clicked");
	// 	this.cube.position.x -= 40;
	// }
	// if(this.keyboard.down("right"))
		// this.cube.position.x += 40;
	
	this.boardMgr.update(dt);

};

var lag = 0;
game.prototype.render = function(){
	var now = new Date().getTime();
	var dt = now - (time || now);
	lag += dt;

	if(lag > 300)
	{
		this.update(dt);
		lag = 0;
	}

	this.boardMgr.render(dt);
	this.renderer.render(this.scene, this.camera);

	time = now;
	var thisObj = this;

	requestAnimationFrame( function() {thisObj.render();} );
};

game.prototype.destroy = function() {
	this.keyboard.destroy();
};

toStr = function(wordArr){
	var chars = ""

	for (var i = 0; i < wordArr.length; i++) {
		chars += wordArr[i].letter.value;
	};

	return chars;
}
// Game code ends