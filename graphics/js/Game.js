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

function onDocumentMouseDown( event ) {
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

  console.log("intersects: " + intersects.length);
  for (var i = 0; i < intersects.length; i++) {
    console.log(intersects[i].point);
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
	text4.innerHTML = "intersects: " + intersects.length;
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
// Game code ends