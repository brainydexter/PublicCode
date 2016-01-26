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
	// var BLOCK_WIDTH = WIDTH/(NxN * 4);
	// var geometry = new THREE.BoxGeometry( BLOCK_WIDTH, BLOCK_WIDTH, 4 );
	// var material = new THREE.MeshBasicMaterial( { color: 0x00ff00 } );
	
	// var cube2 = new THREE.Mesh( geometry, new THREE.MeshBasicMaterial( { color: 0xFF0000} ));
	// cube2.position.set(400, 300, 0);
	// this.scene.add(cube2);

	// this.cube = new THREE.Mesh( geometry, material );
	// this.cube.position.set(WIDTH/2, HEIGHT/2, 1);
	// this.scene.add( this.cube );
	this.boardMgr = new BoardMgr(this.scene);
};

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