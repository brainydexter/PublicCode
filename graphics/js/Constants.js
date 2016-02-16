function Constants (){
}

Constants.BLOCK_WIDTH = 40;
Constants.NUM_ROWS = 15;
Constants.NUM_COLUMNS = 5;
Constants.X_OFFSET = 260;

Constants.HEIGHT = 600;
Constants.WIDTH  = 800;

Constants.updateConsts = function(width, height){
	if(width >= 800){
		Constants.WIDTH = width;
	}

	if (height >= 600) {
		Constants.HEIGHT = height;
	}

	Constants.X_OFFSET = Math.floor(Constants.WIDTH/3);
} 